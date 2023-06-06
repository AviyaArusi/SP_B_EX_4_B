#include "MagicalContainer.hpp"

using namespace std;
namespace ariel 
{
    bool isPrime(int n) 
    {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i = i + 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    pNode creatNode(int data)
    {
        pNode newNode = (pNode)malloc(NODE_SIZE);
        if(newNode == NULL)
        {
            printf("malloc error!\n");
            exit(1);
        }
        newNode->data = data;
        newNode->is_prime = isPrime(data);
        return newNode;
    }

    MagicalContainer::MagicalContainer() 
    : _lastPrime(MAX_VALUE), _firstPrime(MAX_VALUE) { _elements.clear(); }

    MagicalContainer::MagicalContainer(const MagicalContainer &other) 
    :  _firstPrime(MAX_VALUE)
    {
        this->_firstPrime = MAX_VALUE;
        this->_lastPrime = MAX_VALUE;
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements

        for (auto element : other._elements) { this->addElement(element->data); }

    }

    MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept
        : _elements(other._elements), _firstPrime(other._firstPrime), _lastPrime(other._lastPrime) {}

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
    {
        if(this == &other) return *this;
        this->_firstPrime = MAX_VALUE;
        this->_lastPrime = MAX_VALUE;
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements
        for (auto element : other._elements) { this->addElement(element->data); }
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&other) noexcept
    {
        if(this == &other) return *this;
        this->_firstPrime = MAX_VALUE;
        this->_lastPrime = MAX_VALUE;
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements
        for (auto element : other._elements) { this->addElement(element->data); }
        return *this;
    }

    MagicalContainer::~MagicalContainer()
    {
        for (auto element : _elements)
        {
            free(element);
        }

        _elements.clear();
    }

    size_t MagicalContainer::size() const { return _elements.size(); }

    long MagicalContainer::contains(int elementData)
    {
        auto it = find_if(_elements.begin(), _elements.end(), [elementData](const pNode node) {
        return node->data == elementData;
    });

    if (it != _elements.end()) {
        return distance(_elements.begin(), it);
    }

    return MAX_VALUE;
    }

    void MagicalContainer::insertSorted(pNode newNode) 
    {
        auto it = lower_bound(_elements.begin(), _elements.end(), newNode,
            [](const pNode a, const pNode b) 
            {
                return a->data < b->data;
            }
            );

        _elements.insert(it, newNode);
    }   

    void MagicalContainer::updatePrimeLinkedList()
    {
        for (size_t i = 0; i < _elements.size(); ++i) 
        {
            if (isPrime(_elements[i]->data)) 
            {
                if (_firstPrime == MAX_VALUE) 
                {
                    _firstPrime = i;
                    _lastPrime = i;
                } 
                else 
                {
                    _elements[_lastPrime]->nextPrime = i;
                    _elements[i]->prevPrime = _lastPrime;
                    _elements[i]->nextPrime = MAX_VALUE; // Set next as null
                    _lastPrime = i;
                }
            }
        }
    }


    void MagicalContainer::addElement(int element) 
    {
        if(contains(element) != MAX_VALUE) { return; }

        pNode newNode = creatNode(element);
        insertSorted(newNode);
        updatePrimeLinkedList();
    }

    void MagicalContainer::removeElement(int element) 
    {
        if(_elements.size() == 0){ throw runtime_error("Can't remove from empty Container!\n"); }
        // If the element dont exsist in the vector.
        long index = contains(element);
        if( index == MAX_VALUE) { throw runtime_error("Invalid argumant!\n"); }

        pNode nodeToRemove = _elements.at((size_t)index);
       
        _elements.erase(_elements.begin() + index);

        _firstPrime = MAX_VALUE;
        updatePrimeLinkedList();

        free(nodeToRemove);
    }

    vector<pNode>& MagicalContainer::getElements(){ return _elements; }


    // IteratorBase

    MagicalContainer::IteratorBase::IteratorBase(MagicalContainer& container) 
    : _container(container), _current(0), counter(0) {}

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=(const MagicalContainer::IteratorBase& other) 
    { 
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        // if(&_container != &other._container) { throw runtime_error("Error!\n"); }
        if(this == &other) { return *this; }
        _container = other._container;
        _current = other._current;
        counter = other.counter;
        return *this; 
    }

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=( MagicalContainer::IteratorBase&& other) noexcept 
    {
        if(this == &other) { return *this; }
        _container = other._container;
        _current = other._current;
        counter = other.counter; 
        return *this; 
    }



    // Boolean operators

    bool MagicalContainer::IteratorBase::operator==(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        return _current == other._current;
    }

    bool MagicalContainer::IteratorBase::operator!=(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }
        return !(*this == other);
    }

    bool MagicalContainer::IteratorBase::operator>(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        if(_type == SIDE_ITER){ return counter > other.counter;}
        else { return _current > other._current; }
    }

    bool MagicalContainer::IteratorBase::operator<(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        if(_type == 2){ return counter < other.counter;}
        else { return _current < other._current; }
    }

    int MagicalContainer::IteratorBase::operator*() 
    {
        return _container.getElements().at(_current)->data;
    }

    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator++() 
    {
        if(_current >= _container.size() ) { throw runtime_error("Index out of range!\n"); }
        ++_current;
        return *this;
    }



} // namespace ariel


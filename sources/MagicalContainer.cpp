#include "MagicalContainer.hpp"

using namespace std;
namespace ariel 
{
    /**
     * Get integer and return if it is prime.
    */
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

    /**
     * Get data(int) and creat Node using malloc, 
     * holds if the node is prime or don't.
    */
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

    /**
     * Constructor for MagicalContainer.
     * Set the first and last prime to null(MAX_VALUE) - because size_t is unsigned.
     * Set the _element to 0.
    */
    MagicalContainer::MagicalContainer() 
    : _firstPrime(MAX_VALUE), _lastPrime(MAX_VALUE)
    { 
        _elements.clear(); 
    }

    /**
     * Copy constructor for MagicalContainer.
     * Set the first and last prime to null(MAX_VALUE) - because size_t is unsigned.
     * Remove all the old data.
     * Deep copy all the other data.
    */
    MagicalContainer::MagicalContainer(const MagicalContainer &other) 
    :  _firstPrime(MAX_VALUE), _lastPrime(MAX_VALUE)
    {
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements

        for (auto element : other._elements) { this->addElement(element->data); }

    }

    MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept
        : _elements(other._elements), _firstPrime(other._firstPrime), _lastPrime(other._lastPrime) {}

    /**
     * Move assignment for MagicalContainer.
     * If the other is this, to nothing.
     * Set the first and last prime to null(MAX_VALUE) - because size_t is unsigned.
     * Remove all the old data.
     * Deep copy all the other data.
     * Return this.
    */
    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other)
    {
        if(this == &other) return *this;

        this->_firstPrime = MAX_VALUE;
        this->_lastPrime = MAX_VALUE;
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements
        for (auto element : other._elements) { this->addElement(element->data); }
        return *this;
    }

    /**
     * Move assignment for MagicalContainer.
     * If the other is this, to nothing.
     * Set the first and last prime to null(MAX_VALUE) - because size_t is unsigned.
     * Remove all the old data.
     * Deep copy all the other data.
     * Return this.
    */
    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&other) noexcept
    {
        if(this == &other) return *this;

        this->_firstPrime = MAX_VALUE;
        this->_lastPrime = MAX_VALUE;
        for (auto element : _elements) { removeElement(element->data); }//Remove the old elements
        for (auto element : other._elements) { this->addElement(element->data); }
        return *this;
    }

    /**
     * Destructor for MagicalContainer.
     * Free all the mmalloc element that stay in the _elements vector.
    */
    MagicalContainer::~MagicalContainer()
    {
        for (auto element : _elements)
        {
            free(element);
        }

        _elements.clear();
    }

    /**
     * Return the size of the _elements vector.
    */
    size_t MagicalContainer::size() const { return _elements.size(); }

    /**
     * Chek if element is in the container - using algorithem end lambda function.
     * If it is inside, return the index.
     * Else return MAX_VALUE.
    */
    long MagicalContainer::contains(int elementData) const
    {
        auto it = find_if(_elements.begin(), _elements.end(), [elementData](const pNode node) {
        return node->data == elementData;
    });

    if (it != _elements.end()) {
        return distance(_elements.begin(), it);
    }

    return MAX_VALUE;
    }

    /**
     * Insert node in sorted way to the container.
    */
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

    /**
     * Update the prime LinkedList.
    */
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

    /**
     * Add element to the container.
     * Creat Node.
     * Insert.
     * Update the prime LinkedList.
    */
    void MagicalContainer::addElement(int element) 
    {
        if(contains(element) != MAX_VALUE) { return; }

        pNode newNode = creatNode(element);
        insertSorted(newNode);
        updatePrimeLinkedList();
    }

    /**
     * Remove element frome the container.
     * Check first if the element exsist.
     * Update the prime LinkedList.
    */
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

    /**
     * Return the _elements vector.
    */
    vector<pNode>& MagicalContainer::getElements(){ return _elements; }

} // namespace ariel


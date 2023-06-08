#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{
    /**
     * Constructor for IteratorBase.
    */
    MagicalContainer::IteratorBase::IteratorBase(MagicalContainer& container) 
    : _container(container), _current(0), counter(0) 
    {
        if(container.size() == 0)
        {
            _current = container.size();
        }
    }

    /**
     * Constructor for IteratorBase.
    */
    MagicalContainer::IteratorBase::IteratorBase(MagicalContainer& container, size_t current) 
    : _container(container), _current(current), counter(0) 
    {
        if(container.size() == 0)
        {
            _current = container.size();
        }
    }

    /**
     * Move assignment for IteratorBase.
     * If the type is difference frome this, throw error.
     * If the container is difference frome this, throw error.
     * If other == this, do nothing.
     * copy currrent.
     * copy counter.
     * Return this.
    */
    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=(const MagicalContainer::IteratorBase& other) 
    { 
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }
        if(this == &other) { return *this; }

        _current = other._current;
        counter = other.counter;
        return *this; 
    }

    /**
     * Move assignment for IteratorBase.
     * If other == this, do nothing.
     * copy currrent.
     * copy counter.
     * Return this.
    */
    MagicalContainer::IteratorBase& MagicalContainer::IteratorBase::operator=( MagicalContainer::IteratorBase&& other) noexcept 
    {
        if(this == &other) { return *this; }

        _current = other._current;
        counter = other.counter; 
        return *this; 
    }



    // Boolean operators



    /**
     * Bool operator.
     * If the type is difference frome this, throw error.
     * If the container is difference frome this, throw error.
    */
    bool MagicalContainer::IteratorBase::operator==(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        return _current == other._current;
    }

    /**
     * Bool operator.
     * If the type is difference frome this, throw error.
     * If the container is difference frome this, throw error.
    */
    bool MagicalContainer::IteratorBase::operator!=(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }
        
        return !(*this == other);
    }

    /**
     * Bool operator.
     * If the type is difference frome this, throw error.
     * If the container is difference frome this, throw error.
     * If it is SideCrossIterator check the number of time of use the ++ operator.
    */
    bool MagicalContainer::IteratorBase::operator>(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        if(_type == SIDE_ITER){ return counter > other.counter;}
        else { return _current > other._current; }
    }

    /**
     * Bool operator.
     * If the type is difference frome this, throw error.
     * If the container is difference frome this, throw error.
     * If it is SideCrossIterator check the number of time of use the ++ operator.
    */
    bool MagicalContainer::IteratorBase::operator<(const IteratorBase& other) const 
    {
        if(_type != other._type) { throw runtime_error("Can't use boolean opertor between 2 defference Iterators!\n"); }
        if(&_container != &other._container) { throw runtime_error("Error!\n"); }

        if(_type == 2){ return counter < other.counter;}
        else { return _current < other._current; }
    }
    /**
     * Operator *.
     * return the data from the _current index inside the _elements vector.
    */
    int MagicalContainer::IteratorBase::operator*() 
    {
        return _container.getElements().at(_current)->data;
    }


}// namespace ariel



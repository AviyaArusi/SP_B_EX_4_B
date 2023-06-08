#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{
    /**
     * Constructor for SideCrossIterator.
     * Set the type.
    */
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer& container) 
    : IteratorBase(container), reverse(true), index(0)  
    { 
        _type = SIDE_ITER; 
    }

    /**
     * Constructor for SideCrossIterator for the begin() & end() functions return value.
     * Set the type.
    */
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer& container, size_t current) 
    : IteratorBase(container, current), reverse(true), index(0)  
    { 
        _type = SIDE_ITER; 
    }

    /**
     * Return SideCrossIterator with current of 0.
    */
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
    {
        return SideCrossIterator(_container, 0);
    }

    /**
     * Return SideCrossIterator with current of _container.size().
    */
     MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
    {
        return SideCrossIterator(_container, _container.size());
    }

    /**
     * Move the _current index to the correct index in the SideCross order.
     * If _current is in the end of the container, throw error.
     * If we use ++ more then _container size, throw error.
     * Return this
    */
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        if(counter >= _container.size() || _current == _container.size() ) { throw runtime_error("Out of range!\n"); }
        
        if(counter == _container.size()-1)
        {
            _current = _container.size();
            return *this;
        }

        if (reverse) 
        {
           _current = _container.size() -1 -index++;
           reverse = false;
        }
        else 
        {
             _current = index;   
            reverse = true;
        }
        
        counter++;
        return *this;
    }




} // namespace ariel



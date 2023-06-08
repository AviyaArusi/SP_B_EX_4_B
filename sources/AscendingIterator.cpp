#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{
    /**
     * Constructor for AscendingIterator.
     * Set the type.
    */
    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container) 
    : IteratorBase(container)  
    { 
        _type = ASC_ITER;
    }

    /**
     * Constructor for AscendingIterator for the begin() & end() functions return value.
     * Set the type.
    */
    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container, size_t current) 
    : IteratorBase(container, current)  
    { 
        _type = ASC_ITER;
    }

    /**
     * Return AscendingIterator with current of 0.
    */
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
    {
        return AscendingIterator(_container, 0);
    }

    /**
     * Return AscendingIterator with current of _container.size().
    */
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
    {
        return AscendingIterator(_container, _container.size());
    }

    /**
     * Move the _current index + 1.
     * If _current is in the end of the container, throw error.
     * Return this.
    */
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() 
    {
        if(_current >= _container.size() ) { throw runtime_error("Index out of range!\n"); }
        ++_current;
        return *this;
    }


} // namespace ariel



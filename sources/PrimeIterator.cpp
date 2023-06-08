#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{
    /**
     * Constructor for PrimeIterator.
     * Set the type.
    */
    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer& container) 
    : IteratorBase(container, container._firstPrime) 
    { 
        _type = PRIME_ITER;
        if(container._firstPrime == MAX_VALUE)
        {
            _current = container.size();
        }
    }

    /**
     * Constructor for PrimeIterator for the begin() & end() functions return value.
     * Set the type.
    */
    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer& container, size_t current) 
    : IteratorBase(container, current) 
    { 
        _type = PRIME_ITER;
    }

    /**
     * Return PrimeIterator with current of 0.
    */
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
    {
        return PrimeIterator(_container, 0);
    }

    /**
     * Return PrimeIterator with current of _container.size().
    */
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        return PrimeIterator(_container, _container.size());
    }

    /**
     * Move the _current index to the next prime index.
     * If _current is in the end of the container, throw error.
     * Return this
    */
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if( _current == _container.size() ) { throw runtime_error("Out of range!\n"); }

        if(_container.getElements().at(_current)->nextPrime == MAX_VALUE)
        {
        _current = _container.size();
        }
        else
        {
            _current =  _container.getElements().at(_current)->nextPrime;
        }

        return *this;
    }


} // namespace ariel



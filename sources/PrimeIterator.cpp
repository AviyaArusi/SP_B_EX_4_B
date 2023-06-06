#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{

    // PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer& container) : IteratorBase(container) 
    { 
        _type = 0;
        _current = container._firstPrime;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin() 
    {
        _current = _container._firstPrime;
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() 
    {
        _current = _container.size();
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if(_current > _container._lastPrime) { throw runtime_error("Out of range!\n"); }

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


}



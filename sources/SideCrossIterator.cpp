#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{

    // SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer& container) 
    : IteratorBase(container), reverse(true), index(0)  { _type = SIDE_ITER; }


    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() 
    {
        _current = 0;
        reverse = true;
        return *this;
    }

     MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() 
    {
        _current = _container.size();
        reverse = true;
        return *this;
    }

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




}



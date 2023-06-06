#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{

    // SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer& container) : IteratorBase(container), reverse(true), index(0), counter(0) { _type = 0; }

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
        if(counter > _container.size() ) { throw runtime_error("Out of range!\n"); }
        if(counter == _container.size()-1)
        {
            _current = _container.size();
            return *this;
        }

        if (reverse) 
        {
            // cout << "\nThe index cross ordered:" << index << endl;
           _current = _container.size() -1 -index++;
           reverse = false;
        }
        else 
        {
            // cout << "\nThe index in ordered:" << index << endl;
             _current = index;   
            reverse = true;
        }
        
        counter++;
        // cout << "The counter is:" << counter << endl;
        return *this;
    }




}



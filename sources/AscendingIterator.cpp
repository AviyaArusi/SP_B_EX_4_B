#include "MagicalContainer.hpp"


using namespace std;
namespace ariel 
{

   // AscendingIterator

    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container) : IteratorBase(container)  { _type = 0;}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() 
    {
        _current = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() 
    {
        _current = _container.size();
        return *this;
    }


}



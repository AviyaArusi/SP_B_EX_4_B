#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <iterator>
#include <stdexcept>

#define NODE_SIZE sizeof(Node)
#define MAX_VALUE  std::numeric_limits<long>::max()

namespace ariel 
{
    typedef struct Node
    {
        int data = 0;
        bool is_prime = false;
        size_t prevPrime = MAX_VALUE; // Hold the nextUp index
        size_t nextPrime = MAX_VALUE;// Hold the next prime index
    }Node, *pNode;
    
    pNode creatNode(int data);


    class MagicalContainer 
    {
    private:

        std::vector<pNode> _elements;  // using a dynamic array for internal storage
        size_t _lastPrime;
        size_t _firstPrime;

        void insertSorted(pNode newNode);
        long contains(int element);
        void updatePrimeLinkedList();

    public:

        MagicalContainer();
        MagicalContainer(const MagicalContainer &other);
        MagicalContainer(MagicalContainer &&other) noexcept;
        MagicalContainer &operator=(const MagicalContainer &other);
        MagicalContainer &operator=(MagicalContainer &&other) noexcept;
        ~MagicalContainer();

        // Methods for MagicalContainer
        void addElement(int);
        void removeElement(int);
        size_t size() const;
        //##########################
        // void printPrime(const MagicalContainer &other);
        //#########################

        std::vector<pNode>& getElements();

    // Base class for all custom iterators
    class IteratorBase 
    {
    public:
        IteratorBase(MagicalContainer& container);
        IteratorBase(IteratorBase&) = default;
        IteratorBase& operator=(const IteratorBase&);
        IteratorBase(IteratorBase&&) noexcept = default;
        IteratorBase& operator=( IteratorBase&&) noexcept;
        virtual ~IteratorBase() = default;
        
        // Required operators for all iterators
        bool operator==(const IteratorBase&) const;
        bool operator!=(const IteratorBase&) const;
        bool operator>(const IteratorBase&) const;
        bool operator<(const IteratorBase&) const;
        int operator*();

        virtual IteratorBase& operator++();
        virtual IteratorBase& begin() = 0;
        virtual IteratorBase& end() = 0;

        MagicalContainer& _container;
        std::size_t _current;
        int _type; // 0 - Acs, 1 - SideCross, 2 - Prime
    };


    // AscendingIterator
    class AscendingIterator : public IteratorBase 
    {
    public:
        AscendingIterator(MagicalContainer&);

        AscendingIterator& begin() override;
        AscendingIterator& end() override;
    };


    // SideCrossIterator
    class SideCrossIterator : public IteratorBase 
    {
    public:
        SideCrossIterator(MagicalContainer&);

        SideCrossIterator& begin() override;
        SideCrossIterator& end() override;
        SideCrossIterator& operator++() override;

    private:
        bool reverse;
        size_t index;
        int counter;
    };

    // PrimeIterator
    class PrimeIterator : public IteratorBase 
    {
    public:
        PrimeIterator(MagicalContainer&);

        PrimeIterator& begin() override;
        PrimeIterator& end() override;
        PrimeIterator& operator++() override;
    };

};


} // namespace ariel


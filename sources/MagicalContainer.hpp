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

const int ASC_ITER  = 1;
const int SIDE_ITER  = 2;
const int PRIME_ITER = 3;



namespace ariel 
{
    typedef struct Node
    {
        int data = 0;
        bool is_prime = false;
        size_t prevPrime = MAX_VALUE; // Hold the prev prime index
        size_t nextPrime = MAX_VALUE;// Hold the next prime index
    }Node, *pNode;
    
    pNode creatNode(int data);


    class MagicalContainer 
    {
    private:

        std::vector<pNode> _elements;  // using a dynamic array for internal storage
        size_t _lastPrime;
        size_t _firstPrime;

        long contains(int element) const;
        void insertSorted(pNode newNode);
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

        std::vector<pNode>& getElements();


    // Base class for all custom iterators
    class IteratorBase 
    {
    public:
        IteratorBase(MagicalContainer& container);
        IteratorBase(MagicalContainer& container, size_t current);
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

        virtual IteratorBase& operator++() = 0;
        // virtual IteratorBase begin() = 0;
        // virtual IteratorBase end() = 0;

        MagicalContainer& _container;
        std::size_t _current;
        int _type; // 1 - Acs, 2 - SideCross, 3 - Prime
        int counter; // Count the ++ operator for SideCrossIterator.
    };



    // AscendingIterator
    class AscendingIterator : public IteratorBase 
    {
    public:
        AscendingIterator(MagicalContainer&);
        AscendingIterator(MagicalContainer&, size_t);

        AscendingIterator begin() const;//override;
        AscendingIterator end() const;//override;
        AscendingIterator& operator++() override;
    };



    // SideCrossIterator
    class SideCrossIterator : public IteratorBase 
    {
    public:
        SideCrossIterator(MagicalContainer&);
        SideCrossIterator(MagicalContainer&, size_t);

        SideCrossIterator begin() const;//override;
        SideCrossIterator end() const;//override;
        SideCrossIterator& operator++() override;

    private:
        bool reverse;
        size_t index;
    };



    // PrimeIterator
    class PrimeIterator : public IteratorBase 
    {
    public:
        PrimeIterator(MagicalContainer&);
        PrimeIterator(MagicalContainer&, size_t);

        PrimeIterator begin() const;//override;
        PrimeIterator end() const;//override;
        PrimeIterator& operator++() override;
    };


    }; // class MagicalContainer


} // namespace ariel


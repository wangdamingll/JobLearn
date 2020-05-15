#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void Insert( x )       --> Insert x
// DeleteMin( minItem )   --> Remove (and optionally return) smallest item
// T FindMin( )  --> Return smallest item
// bool IsEmpty( )        --> Return true if empty; else false
// void MakeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename T>
class BinaryHeap{
public:
    explicit BinaryHeap( int capacity = 100 ):array(capacity + 1 ),currentSize{0}{}
    explicit BinaryHeap( const vector<T> & items ):array( items.size( )+10 ),currentSize{items.size()}{
        for( int i=0; i<items.size();++i){
            array[i+1] = items[i];
        }
        BuildHeap();
    }

    bool IsEmpty()const{
        return currentSize==0;
    }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const T& FindMin() const{
        if( IsEmpty() ){
            return nullptr;
        }
        return array[1];
    }

    /**
     * Insert item x, allowing duplicates.
     */
    void Insert(const T& x){
        if( currentSize == array.size() - 1 ){
            array.resize( array.size()*2);
        }

        T copy = x;
        int hole = ++currentSize;
        array[hole] = std::move(x);
        PercolateUp(hole);
    }


    /**
     * Insert item x, allowing duplicates.
     */
    void Insert(T&& x){
        if(currentSize == array.size()-1){
            array.resize( array.size() * 2 );
        }

        int hole = ++currentSize;
        array[hole] = std::move(x);
        PercolateUp(hole);
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void DeleteMin(){
        if(IsEmpty()){
            return;
        }

        array[1] = std::move(array[currentSize--]);
        PercolateDown(1);
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void DeleteMin(T& minItem){
        if(IsEmpty()){
            return ;
        }
        minItem = std::move(array[1]);
        array[1] = std::move(array[currentSize--]);
        PercolateDown(1);
    }

    void MakeEmpty(){
        currentSize = 0;
    }

private:
    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void BuildHeap(){
        for(int i = currentSize/2; i>0;--i){
            PercolateDown(i);
        }
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void PercolateDown( int hole ){
        int child;
        T tmp = std::move(array[hole]);
        for( ; hole*2 <= currentSize; hole=child ){
            child = hole*2;
            if(child!=currentSize && array[child+1] < array[child] )
                ++child;
            if(array[child]<tmp)
                array[ hole ] = std::move(array[child]);
            else
                break;
        }
        array[hole] = std::move(tmp);
    }

    /**
     * Internal method to percolate up in the heap.
     * hole is the index at which the percolate begins.
     */
    void PercolateUp(int hole){
        array[0] = std::move(array[hole]);
        for(;hole>1 && array[0]<array[hole/2];hole/=2){
            array[ hole ] = std::move(array[hole/2]);
        }
        array[hole] = std::move(array[0]);
    }

private:
    int currentSize;  // Number of elements in heap
    vector<T> array;  // The heap array
};

#endif

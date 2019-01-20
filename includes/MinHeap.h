/**
 * @file MinHeap.h
 *
 * @brief Definition of MinHeap class, providing a MinHeap datastructure
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include <vector>
#pragma once

//templated min binary heap implementation
template <typename T>

class MinHeap
{
private:
    std::vector<T> heap; //heap data structure

    void moveUp(int index)
    {
        //moves object up to it's correct location within the heap
        int leftChildIndex = 2*index + 1;
        int rightChildIndex = 2*index + 2;
        
        //ensures left index is not greater than size of vector
        if (leftChildIndex >= (int) size())
        {
            return;
        }
        
        int minIndex = index;
        
        //chooses elements to swap
        if (heap[index] > heap[leftChildIndex])
        {
            minIndex = leftChildIndex;
        }
        
        if (rightChildIndex < (int)size() && 
            heap[minIndex] > heap[rightChildIndex])
        {
            minIndex = rightChildIndex;
        }
        
        if (minIndex != index)
        {
            //swaps elements
            T swapper = heap[index];
            heap[index] = heap[minIndex];
            heap[minIndex] = swapper;
            moveDown(minIndex);
        }
    };
    void moveDown(int index)
    {
        if (index == 0)
        {
            return;
        }
        
        int parentIndex = (index-1)/2;
        
        if (heap[parentIndex] > heap[index])
        {
            //swaps elements
            T swapper = heap[parentIndex];
            heap[parentIndex] = heap[index];
            heap[index] = swapper;
            moveUp(parentIndex);
        }
    };
    //reorders everything in heap to be in order
    void heapify()
    {
        for (int i = size()-1; i >= 0; --i)
        {
            moveDown(i);
        }
    };
    
public:
    MinHeap() {};
    MinHeap(std::vector<T> _heap) : heap(_heap) { heapify(); };
    
    //insert an item to the heap, and re-order as appropriate
    void insert(T t)
    {
        heap.push_back(t);
        moveUp((int)size());
    };
    //delete the head of the heap
    void deleteMin()
    {
        if (size() == 0)
        {
            return;
        }
        
        heap[0] = heap[size()-1];
        heap.pop_back();
        
        moveDown(0);
    };
    void display();
    T getMin() { return heap[0]; };
    unsigned long size() { return heap.size(); };
};

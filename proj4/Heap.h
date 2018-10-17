#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

template <typename T>
class Heap{
 public:
  Heap(int size, bool (*fpt) (const T&, const T&));
  ~Heap();
  T getFirst(); //returns the min or max value based on whether it's a min heap or a max heap
  bool isEmpty();
  void insert(T value);
  void deleteFirst();
  T getValue(int index);
  T* getArray();

 private:
  T *data; //the variable the array will be stored in
  int heapSize;
  int arraySize;
  bool (*compare)(const T&, const T&) ; //variable to store the function pointer

  int getLeftChildIndex(int nodeIndex);
  int getRightChildIndex(int nodeIndex);
  int getParentIndex(int nodeIndex);
  void siftUp(int nodeIndex); //After inserting an element, you must sift up the heap and change nodes accordingly
  void siftDown(int nodeIndex); //After removing the min or max element, you must sift down the heap and change nodes accordingly
};

template<typename T>
T Heap<T>::getValue(int index){
  return data[index];
}

//Constructor - takes a size and creates an array
template <typename T>
Heap<T>::Heap(int size, bool (*fpt) (const T&, const T&)) {
  data = new int[size+2]; //the size is plus 2 to account for us starting at index 1 instead of 0 and for the fact that the arrays can differ by up to 2 until they have to be rebalanced, meaning that we want to be able to hold one more than half the total capacity of the medianHeap
  heapSize = 0;
  arraySize = size;
  compare = fpt;
}

//GetFirst - Gets first element of the array, will be the minimum value in a min heap and maximum value in a max heap
template <typename T>
T Heap<T>::getFirst() {
  if (isEmpty())
    throw out_of_range("nothing there");
  else
    return data[1];
}

//IsEmpty - returns whether the heap is empty or not
template <typename T>
bool Heap<T>::isEmpty() {
  return (heapSize == 0);
}

//Destructor - deletes the area that was holding the heap values
template <typename T>
Heap<T>::~Heap() {
  delete[] data;
}

//Insert - Inserts a value at the end of the array
template <typename T>
void Heap<T>::insert(T value) {
  //since the heapSize is the index, if the next index is equal to the max size (which includes the unused 0 index), then there is no room
  if ((heapSize+1) == arraySize)
    throw out_of_range("nothing here");
  else {
    //increment heap size first, and then insert at it because heapSize starts at 0 but we don't use index 0
    heapSize++;
    data[heapSize] = value;
    siftUp(heapSize);
  }
}

//getLeftChildIndex - return the left child of the current index
template <typename T>
int Heap<T>::getLeftChildIndex(int nodeIndex) {
  return 2 * nodeIndex;
}

//getRightChildIndex - return the right child of the current index
template <typename T>
int Heap<T>::getRightChildIndex(int nodeIndex) {
  return 2 * nodeIndex + 1;
}

//getParentIndex - return the parent of the current index
template <typename T>
int Heap<T>::getParentIndex(int nodeIndex) {
  return nodeIndex / 2;
}

//siftUp - change the positions of nodes in the array based on the function pointer passed by medianHeap
template <typename T>
void Heap<T>::siftUp(int nodeIndex) {
  int parentIndex, tmp;
  if (nodeIndex != 1) { //if the value we just inserted is not the root
    parentIndex = getParentIndex(nodeIndex);
    if ( compare(data[nodeIndex], data[parentIndex]) ) {
      tmp = data[parentIndex];
      data[parentIndex] = data[nodeIndex];
      data[nodeIndex] = tmp;
      siftUp(parentIndex);
    }
  }
}

template <typename T>
void Heap<T>::deleteFirst() {
  if (isEmpty())
    throw out_of_range("nothing there");
  else {
    data[1] = data[heapSize];
    heapSize--;
    if (heapSize > 0)
      siftDown(1);
  }
}

template <typename T>
void Heap<T>::siftDown(int nodeIndex) {
  int leftChildIndex, rightChildIndex, compareIndex, tmp;
  leftChildIndex = getLeftChildIndex(nodeIndex);
  rightChildIndex = getRightChildIndex(nodeIndex);
  if (rightChildIndex > heapSize) {
    if (leftChildIndex > heapSize)
      return;
    else
      compareIndex = leftChildIndex;
  } else {
    if ( compare(data[rightChildIndex], data[leftChildIndex]) )
      compareIndex = rightChildIndex;
    else
      compareIndex = leftChildIndex;
  }
  if ( compare(data[compareIndex], data[nodeIndex]) ) {
    tmp = data[compareIndex];
    data[compareIndex] = data[nodeIndex];
    data[nodeIndex] = tmp;
    siftDown(compareIndex);
  }
}

//GetArray - returns the array so it can be accessed
template <typename T>
T* Heap<T>::getArray(){
  return data;
}


#endif

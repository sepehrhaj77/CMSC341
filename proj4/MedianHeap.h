#ifndef MEDIAN_HEAP_H
#define MEDIAN_HEAP_H

#include <iostream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;
template <typename T>
class MedianHeap;

template <typename T>
class Heap{
  friend class MedianHeap<T>;
 public:
  Heap(int size, bool (*fpt) (const T&, const T&));
  ~Heap();
  T getFirst(); //returns the min or max value based on whether it's a min heap or a max heap
  bool isEmpty();
  void insert(T value);
  void deleteFirst(int nodeIndex);
  T* getArray();
  int getSize();
  const Heap<T>& operator=( const Heap<T> &rhs ); //assignment operator
  Heap(const Heap<T> &other); //copy constructor

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


template <typename T>
class MedianHeap{
  friend class Heap<T>;
 public:
  //Constructor for Median Heap - takes two function pointers and a capacity
  MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100) ;
  
  //Copy Constructor
  MedianHeap(const MedianHeap<T>& otherH) ;
  
  //Destructor
  ~MedianHeap();
  
  //Overloaded Assignment Operator
  const MedianHeap<T>& operator=(const MedianHeap<T>& rhs)  ;

  //Size - returns size
  int size() ;

  //Capacity - returns max capacity
  int capacity() ;

  //Insert - inserts an item into the median heap
  void insert(const T& item) ;

  //Get Median - returns the median value
  T getMedian() ;

  //Get Min - returns minimum value in median heap
  T getMin();

  //Get Max - returns maximum value in max heap
  T getMax();

  //Delete Item - removes an item from the median heap
  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) ;

  //Dump - used for debugging purposes
  void dump();

  //MaxHeap Size - returns current size of max heap
  int maxHeapSize() ;

  //MinHeap Size - returns current size of min heap
  int minHeapSize() ;

  //Locate in the max heap - returns a copy of the item in position pos in max heap
  T locateInMaxHeap(int pos) ;  
  
  //Locate in the min heap - returns a copy of the item in position pos in min heap
  T locateInMinHeap(int pos) ;

 private:
  int m_size;
  int m_capacity;
  T m_median;
  T m_min;
  T m_max;
  Heap<T> *minHeap;
  Heap<T> *maxHeap;
  bool (*greater)(const T&, const T&) ; //variable to store the gt function pointer
  bool (*less)(const T&, const T&) ; //variable to store the lt function pointer

};

//Returns size of the Heap
template<typename T>
int Heap<T>::getSize(){
  return heapSize;
}

//Heap Constructor - takes a size and creates an array
template <typename T>
Heap<T>::Heap(int size, bool (*fpt) (const T&, const T&)) {
  size += 2; //the size is plus 2 to account for us starting at index 1 instead of 0 and for the fact that the arrays can differ by up to 2 until they have to be rebalanced, meaning that we want to be able to hold one more than half the total capacity of the medianHeap
  data = new T[size];
  heapSize = 0;
  arraySize = size;
  compare = fpt;
}    

//Heap copy constructor - creates a new dynamically allocated copy of a Heap object
template <class T>
Heap<T>::Heap(const Heap<T> &other){
  //copy member variables
  heapSize = other.heapSize;
  arraySize = other.arraySize;
  compare = other.compare;

  //initialize array
  data = new T[arraySize];

  //copy values from the other heap
  for(int i = 1; i <= heapSize; i++)
    data[i] = T(other.data[i]);
}

//Heap overloaded assignment operator - sets an existing heap equal to another existing heap
template <class T>
const Heap<T>& Heap<T>::operator=( const Heap<T> &rhs ){
  //free the memory of the array
  delete [] data;

  heapSize = rhs.heapSize;
  arraySize = rhs.arraySize;

  //reinitialize the array
  data = new T[arraySize];

  //copy the values from the other existing heap
  for(int i = 1; i <= heapSize; i++)
    data[i] = T(rhs.data[i]);

  return *this;
}

//GetArray - returns the array so it can be accessed
template <typename T>
T* Heap<T>::getArray(){
  return data;
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
    throw out_of_range("nothing there");
  else {
    //increment heap size first, and then insert at it because heapSize starts at 0 but we don't use index 0
    heapSize++;
    data[heapSize] = value;
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
  int parentIndex;
  T tmp;
  if (nodeIndex != 1) { //if the value we just inserted is not the root
    parentIndex = getParentIndex(nodeIndex);
    if ( compare(data[nodeIndex], data[parentIndex]) ) { //comparing current node to parent node
      //swap algorithm
      tmp = data[parentIndex];
      data[parentIndex] = data[nodeIndex];
      data[nodeIndex] = tmp;
      siftUp(parentIndex);
    }
  }
}

//deleteFirst - removes the first element of the array, aka the max value in a min heap and the min value in a min heap
template <typename T>
void Heap<T>::deleteFirst(int nodeIndex) {
  //dont remove if there are no elements
  if (isEmpty())
    throw out_of_range("nothing there");
  else {
    //set last element of heap as root and then sift down to fix heap
    data[nodeIndex] = data[heapSize];
    heapSize--;
    if (heapSize > 0) //dont sift down if we just deleted the root
      siftDown(nodeIndex);
  }
}

template <typename T>
void Heap<T>::siftDown(int nodeIndex) {
  int leftChildIndex, rightChildIndex, compareIndex;
  T tmp;
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

//MedianHeap Constructor - takes two functions pointers and a max capacity
template <typename T>
MedianHeap<T>::MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap){
  minHeap = new Heap<T>( cap/2, lt); //pass the less than function and half the capacity of the median heap to the minHeap
  maxHeap = new Heap<T>( cap/2, gt); //pass the greater than function and half the capacity of the median heap to the maxHeap
  m_size = 0;
  m_capacity = cap;
  greater = gt;
  less = lt;
}

//Median Heap Copy Constructor - creates a new copy of a median heap
template <class T>
MedianHeap<T>::MedianHeap(const MedianHeap<T> & other){
  less = other.less;
  greater = other.greater;
  m_capacity = other.m_capacity;
  minHeap = new Heap<T>(*(other.minHeap));
  maxHeap = new Heap<T>(*(other.maxHeap));
}

//Destructor for Median Heap 
template <typename T>
MedianHeap<T>::~MedianHeap(){
  delete minHeap;
  delete maxHeap;
}

//Overloaded Assignment Operator for MedianHeap
template <class T>
const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){
  //free memory
  delete maxHeap;
  delete minHeap;

  less = rhs.less;
  greater = rhs.greater;
  m_capacity = rhs.m_capacity;

  maxHeap = new Heap<T>(*(rhs.maxHeap));
  minHeap = new Heap<T>(*(rhs.minHeap));

  return *this;
}

//Size - Returns size of Median Heap
template <typename T>
int MedianHeap<T>::size() {
  m_size =  minHeap->getSize() + maxHeap->getSize();
  return m_size;
}

//Capacity - returns the maximum number of items that can be stored in the MedianHeap
template <typename T>
int MedianHeap<T>::capacity(){
  return m_capacity;  
}

//Insert - adds the item given in the parameter to the MedianHeap
template <typename T>
void MedianHeap<T>::insert(const T& item){
 m_size = size();
  //if medianHeap is full
  if(m_size == m_capacity){
    throw out_of_range("Median Heap is Full. No more Room!");
  }

  //If there are no elements in the Median Heap, add the item to the maxHeap by default
  if(m_size == 0){
    maxHeap->insert(item);
    maxHeap->siftUp(maxHeap->heapSize);
    //set the item to be the median, minimum and the maximum since it is the only element in the median heap
    m_min = item;
    m_max = item;
  }

  //Otherwise, figure out which heap to insert into, by comparing the item to the median
  else{
    //if the item is less than the median, insert it into the maxHeap
    if(less(item, getMedian())){
      maxHeap->insert(item);
      maxHeap->siftUp(maxHeap->heapSize);
    }

    //otherwise, the item is greater than or equal to the median, so insert it into the minHeap
    else{
      minHeap->insert(item);
      minHeap->siftUp(minHeap->heapSize);
    }

    //checking to see if the value we are inserting is the new minimum or maximum 
    if( less(item, m_min)){
      m_min = item;
    }

    else if( greater(item, m_max)){
      m_max = item;
    }

    //REBALANCING CHECK
    if( (maxHeap->getSize() - minHeap->getSize()) == 2){ //if the maxHeap has 2 more elements than the minHeap, we must rebalance
      T temp = maxHeap->getFirst(); //store the max value of the max heap in a temporary variable
      maxHeap->deleteFirst(1); //remove the max of the max heap
      minHeap->insert(temp); //insert the value we removed from the max heap into the min heap
      minHeap->siftUp(minHeap->heapSize);
    }

    else if( (minHeap->getSize() - maxHeap->getSize()) == 2){ //if the minHeap has 2 more elements than the maxHeap, we must also rebalance
      //same thing as above
      T temp = minHeap->getFirst();
      minHeap->deleteFirst(1);
      maxHeap->insert(temp);
      maxHeap->siftUp(maxHeap->heapSize);
    }
  }
}

//getMedian() - calculates and returns the median of the median heap
template <typename T>
T MedianHeap<T>::getMedian(){
  //if the heap is empty throw an exception
  if(m_size == 0){
    throw out_of_range("Median Heap is empty! No median found");
  }

  //if the min heap is larger, return the first value of the min heap
  if(minHeap->heapSize > maxHeap->heapSize){
    return minHeap->getFirst();
  }

  //otherwise, either the min heap is larger or they are equal, in which case we arbitrarily decide to return the first value of the max heap
  else{
    return maxHeap->getFirst();
  }

}


//returns the minimum value of the median heap
template <typename T>
T MedianHeap<T>::getMin(){
  m_size = size();
  //if the heap is empty throw an exception
  if(m_size == 0){
    throw out_of_range("Median Heap is empty! No minimum found");
  }
  return m_min;
}

//returns the maximum value of the median heap
template <typename T>
T MedianHeap<T>::getMax(){
  m_size = size();
  //if the heap is empty throw an exception
  if(m_size == 0){
    throw out_of_range("Median Heap is empty! No maximum found");
  }
  return m_max;
}

//deletes an item in the median heap
template <typename T>
bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ){
  m_size = size();
  //check if empty
  if(m_size == 0){
    throw out_of_range("Median Heap is empty! Can't remove!");
  }

  //go through the max heap first
  for(int i=1; i<=maxHeap->getSize(); i++){
    if( equalTo(givenItem, (maxHeap->data[i]) ) ){
      givenItem = maxHeap->data[i];
      maxHeap->deleteFirst(i);

      maxHeap->siftDown(i);
      maxHeap->siftUp(i);

      //REBALANCING CHECK
      if( (maxHeap->getSize() - minHeap->getSize()) == 2){ //if the maxHeap has 2 more elements than the minHeap, we must rebalance
	T temp = maxHeap->getFirst(); //store the max value of the max heap in a temporary variable
	maxHeap->deleteFirst(1); //remove the max of the max heap
	minHeap->insert(temp); //insert the value we removed from the max heap into the min heap
	minHeap->siftUp(minHeap->heapSize);
      }

      else if( (minHeap->getSize() - maxHeap->getSize()) == 2){ //if the minHeap has 2 more elements than the maxHeap, we must also rebalance
	//same thing as above
	T temp = minHeap->getFirst();
	minHeap->deleteFirst(1);
	maxHeap->insert(temp);
	maxHeap->siftUp(maxHeap->heapSize);
      }

      //check to see if you deleted the minimum
      if( equalTo(givenItem, m_min) ){
	m_min = maxHeap->data[1];
	//if so, then search through the whole max heap until you find the new minimum
	for(int i=2; i<maxHeap->heapSize; i++){
	  if( less(maxHeap->data[i], m_min)){
	    m_min = maxHeap->data[i];
	  }
	}
      }

      return true;
    } 
  }

  //go through the min heap now
  for(int i=1; i<=minHeap->getSize(); i++){
    if( equalTo(givenItem, (minHeap->data[i]) ) ){
      givenItem = minHeap->data[i];
      minHeap->deleteFirst(i);

      minHeap->siftDown(i);
      minHeap->siftUp(i);

      //REBALANCING CHECK
      if( (maxHeap->getSize() - minHeap->getSize()) == 2){ //if the maxHeap has 2 more elements than the minHeap, we must rebalance
	T temp = maxHeap->getFirst(); //store the max value of the max heap in a temporary variable
	maxHeap->deleteFirst(1); //remove the max of the max heap
	minHeap->insert(temp); //insert the value we removed from the max heap into the min heap
	minHeap->siftUp(minHeap->heapSize);
      }

      else if( (minHeap->getSize() - maxHeap->getSize()) == 2){ //if the minHeap has 2 more elements than the maxHeap, we must also rebalance
	//same thing as above
	T temp = minHeap->getFirst();
	minHeap->deleteFirst(1);
	maxHeap->insert(temp);
	maxHeap->siftUp(maxHeap->heapSize);
      }

      //check to see if you deleted the maximum
      if( equalTo(givenItem, m_max) ){
        m_max = minHeap->data[1];
        //if so, then search through the whole min heap until you find the new maximum
        for(int i=2; i<minHeap->heapSize; i++){
          if( greater(minHeap->data[i], m_max)){
            m_max = minHeap->data[i];
          }
        }
      }


      return true;
    }

  }

  return false;
}

//Dump - prints out the contents of MedianHeap
template <typename T>
void MedianHeap<T>::dump(){
  cout << "\n----MedianHeap::dump()----\n";
  cout << "---------Max Heap---------\n";

  cout << "size = " << maxHeap->heapSize << ", capacity = " << maxHeap->arraySize << endl;

  for(int i = 1; i < maxHeap->heapSize + 1; i++){
    cout << "Heap[" << i << "] = (" << maxHeap->data[i] << ")" << endl;
  }

  cout << "\n---------Min Heap---------\n";

  cout << "size = " << minHeap->heapSize << ", capacity = " << minHeap->arraySize << endl;

  for(int i = 1; i < minHeap->heapSize + 1; i++){
    cout << "Heap[" << i << "] = (" << minHeap->data[i] << ")" << endl;
  }
  cout << "\n--------------------------\n\n";

  cout << "min    = " << getMin() << endl;
  cout << "median = " << getMedian() << endl;
  cout << "max    = " << getMax() << endl << endl;

}

//MaxHeapSize - returns the size of the max heap
template <typename T>
int MedianHeap<T>::maxHeapSize(){
  return maxHeap->heapSize;
}

//MinHeapSize - returns the size of the min heap
template <typename T>
int MedianHeap<T>::minHeapSize(){
  return minHeap->heapSize;
}

//locateInMaxHeap - returns a copy of the item in position pos in the max heap 
template <typename T>
T MedianHeap<T>::locateInMaxHeap(int pos){
  if(pos < 1 || pos > maxHeap->heapSize){
    throw out_of_range("that index does not exist in the max heap!");
  }

  return maxHeap->data[pos];

}


//locateInMinHeap - returns a copy of the item in position pos in the min heap 
template <typename T>
T MedianHeap<T>::locateInMinHeap(int pos){
  if(pos < 1 || pos > minHeap->heapSize){
    throw out_of_range("that index does not exist in the min heap!");
  }

  return minHeap->data[pos];
}



#endif

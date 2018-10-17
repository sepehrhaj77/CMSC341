/*File: CBofCB.cpp
Project: CMSC 341 Project 1, Fall 2017
Author: Sepehr Hajbarat
Date: 9/20/17
Section 02
Email: sepehr1@umbc.edu
This file contains the implementation for CBofCB.cpp*/

#include "CBofCB.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>
using namespace std;

//CBofCB - Default constructor. Before compilation (not dynamically allocated) creates an array of size 7 to hold circular arrays with a default first array of size 10, initializing the other indeces to point to NULL
CBofCB::CBofCB(){
  m_obSize = 1;
  m_oldest = 0;
  m_newest = 0;

  m_buffers[0] = new InnerCB(10);  
  //initializing rest of array to NULL
  for(int i=1; i<m_obCapacity; i++)
    m_buffers[i] = NULL;
}


//CBofCB - Copy constructor. Makes complete copy of "other" object
CBofCB::CBofCB(const CBofCB& other){
  m_oldest = other.m_oldest;
  m_newest = other.m_newest;
  m_obSize = other.m_obSize;

  int counter = m_oldest;  //counter variable to keep track of which index

  //for loop to populate array with same circular buffers in same locations as "other" outer buffer through the use of InnerCB's copy constructor
  for(int i=0; i<m_obSize; i++){
    m_buffers[counter] = new InnerCB(*(other.m_buffers[counter])); //dereferences current counter spot of outer buffer since it is pointing to an InnerCB
    counter = (counter+1) % m_obCapacity; //increements counter and accounts for wrap around 
  }
}

//~CBofCB - Destructor. Does not delete outer buffer since it is not dynamically allocated; deletes all the InnerCB's located in the outer buffer
CBofCB::~CBofCB(){
  int counter = m_oldest; //variable to help only delete existing buffers, not ones already deleted by dequeue
  for (int i=0; i<m_obSize; i++){
    delete m_buffers[counter];
    counter = (counter+1) % m_obCapacity;  //increments counter and accounts for wrap around
  }
}

//Enqueue - adds the value of data parameter to the outer buffer data structure
void CBofCB::enqueue(int data){
  if(!m_buffers[m_newest]->isFull()){  //checks to make sure newest buffer is not full
    m_buffers[m_newest]->enqueue(data);
  }

  //if current newest buffer is full
  else{
    if(m_obSize == m_obCapacity){  //if entire outer buffer is full of buffers and no more can be created
      throw std::overflow_error("Outer buffer is full");
    }

    else{  //if there is room for another buffer to be created, it is created with double the size of the previous array
      int newSize = 2*(m_buffers[m_newest]->capacity()); //int variable to store capacity of new array. It is twice the capacity of the previous newest array
      m_newest = (m_newest+1) % m_obCapacity; //increments m_newest to the index of the about to be created newest InnerCB
      m_buffers[m_newest] = new InnerCB(newSize);
      m_buffers[m_newest]->enqueue(data);
      m_obSize++;
    }
  }
}

//Dequeue - Removes and returns oldest value stored in this data structure. If entire structure is empty, underflow_error exception thrown. If removing oldest item causes oldest array to become empty, array is deallocated, unless only buffer in structure 
int CBofCB::dequeue(){
  int removed; //variable to store what is being "removed" from the data structure

  if(!isEmpty()){  //checks to make sure entire data structure is not empty
    removed = m_buffers[m_oldest]->dequeue();  //removes one element from oldest array

    if(m_buffers[m_oldest]->isEmpty()){  //if the array we removed from is now empty
      
      if(m_obSize == 1){  //if there is only one InnerCB in the outer buffer, do not de-allocate it
	return removed;
      }

      else{  //if there is more than one buffer, de-allocate the now empty array and increment m_oldest to the next InnerCB. Then return the value that was "removed"
	delete m_buffers[m_oldest];
	m_oldest = (m_oldest+1) % m_obCapacity;
	m_obSize--;
	return removed;
      }

    }
    return removed;
  }

  else  //throw underflow error if enitre outer buffer has no elements.
    throw std::underflow_error("No elements in entire outer buffer to remove.");
}

//IsFull - Returns true if it is not possible to add any more items to the data structure 
bool CBofCB::isFull(){
  if(m_buffers[m_newest]->isFull() && m_obSize == m_obCapacity)
    return true;
}

//IsEmpty - Returns true if there are no itmes stored in the data structure anywhere
bool CBofCB::isEmpty(){
  int counter = m_oldest;  //counter variable to only go through allocated arrays and avoid invoking class methods on NULL pointers
  for(int i=0; i < m_obSize; i++){  //iterates through each index of the outer buffer that contains an array and tests the isEmpty() of each InnerCB
    if(!m_buffers[counter]->isEmpty())
      return false;
    counter = (counter+1) % m_obCapacity;
  }
  return true;
}

//Size - returns number of items stored in entire data structure
int CBofCB::size(){
  int sum = 0; //variable to store sum of total elements
  int counter = m_oldest; //variable to help only iterate through existing buffers
  
  for(int i=0; i < m_obSize; i++){
    sum += m_buffers[counter]->size();
    counter = (counter+1) % m_obCapacity;
  }
  return sum;
}

//Overloaded Equals Sign Operator - Before assignment, lhs and rhs buffers do not need to have inner buffers of matching capacities.
const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  if(this != &rhs){  //prevents self-assignment
    int counter = m_oldest;  //counter variable to help iterate through only existing arrays

    for (int i=0; i<m_obSize; i++){ //deletes the values in the lhs 
      delete m_buffers[counter];
      counter = (counter+1) % m_obCapacity; //accounting for wrap around
    }


    m_obSize = rhs.m_obSize;
    m_oldest = rhs.m_oldest;
    m_newest = rhs.m_newest;

    counter = m_oldest;    
    for (int i=0; i<m_obSize; i++){ //copies the values from each inner buffer from the rhs CBofCB to the lhs CBofCB, utilizing its overloaded = operator
      m_buffers[counter] = new InnerCB(*rhs.m_buffers[counter]);
      counter = (counter+1) % m_obCapacity; //accounting for wrap around
    }
  }
  //returns a reference to the lhs object that has now copied the values of the rhs
  return *this;
}

//Dump - Prints out contents of entire data structure
  void CBofCB::dump(){
  int counter = m_oldest; //counter variable to help only iterate through existing buffers

  std::cout << "-----------------------------------------" << std::endl;
  std::cout << "Outer Circular buffer dump(), m_obSize = " << m_obSize << ":" << std::endl;

  for(int i=0; i<m_obSize; i++){ //for loop to iterate through all existing buffers  
    std::cout << "[" << counter << "] ";
    m_buffers[counter]->dump();
    std::cout << std::endl;

    std::cout << counter << std::endl;
    counter = (counter+1) % m_obCapacity;  //increments counter and accounts for wrap around
    std::cout << counter << std::endl;
  }
  std::cout << "-----------------------------------------" << std::endl;
}

/*File: InnerCB.cpp
Project: CMSC 341 Project 1, Fall 2017
Author: Sepehr Hajbarat
Date: 9/19/17
Section 02
Email: sepehr1@umbc.edu
This file contains the implementation for InnerCB.h*/


#include "InnerCB.h"
#include <stdexcept>
#include <iostream>

//InnerCB - Constructor. Initializes data members and creates array of default size 10 
InnerCB::InnerCB(int n){
  m_buffer = new int[n];
  m_capacity = n;
  m_size = 0;
  m_start = 0;
  m_end = n-1;

}

//InnerCB - Copy Constructor. Creates complete copy of an InnerCB object passed to it with separately allocated memory.
InnerCB::InnerCB(const InnerCB& other){
  int counter = m_start; //counter variable to act as an iterator going through the array

  m_buffer = new int[other.m_capacity];
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;

  //for loop to populate array with same elements in same locations as "other" InnerCB object
  for(int i=0; i<m_capacity; i++){ 
    m_buffer[counter] = other.m_buffer[counter];
    counter = (counter+1) % m_capacity;
  }
}

//~InnerCB - Destructor. Deletes the array that was dynamically created in the constructor or copy constructor
InnerCB::~InnerCB(){
  delete m_buffer;
  m_buffer = NULL;
}

//Enqueue - Adds data parameter value to circular buffer. Wraps around if necessary. If full, overflow_error exception thrown
void InnerCB::enqueue(int data){
  //testing whether the buffer is full. If not, increment m_end and use modulus to account for wrap around, and then insert at m_end, incrementing m_size as well
  if(!isFull()){
    m_end = (m_end+1) % m_capacity;
    m_buffer[m_end] = data;
    m_size++;
  }
  
  //if the buffer is full, throws an overflow_error exception
  else{
    throw std::overflow_error("Buffer is currently full. Can't add");
  }
}

//Dequeue - removes the oldest item in the circular buffer and returns that value. If empty, throws an underflow_error exception
int InnerCB::dequeue(){
  int removed; //variable to store what is being "deleted"

  //testing whether the buffer is empty. If not, "delete" what is at index m_start (just pretend it doesn't exist in our case) and increment m_start. Then decrement m_size as well
  if(!isEmpty()){
    removed = m_buffer[m_start];
    m_start = (m_start + 1) % m_capacity;
    m_size--;
    return removed;
  }
  
  //if buffer is empty, throws underflow_error exception
  else{
    throw std::underflow_error("Buffer is currently empty. Nothing to remove");
  }  
}
//IsFull - returns whether the circular buffer is full, by comparing the size of the array to the capacity
bool InnerCB::isFull(){
  if (m_size == m_capacity)
    return true;
  return false;
}

//IsEmpty - returns whether the buffer is empty, by checking if m_size is 0 or not
bool InnerCB::isEmpty(){
  if(m_size == 0)
    return true;
  return false;
}

//Capacity - returns the number of int values that can be stored in the array, AKA the length of the array
int InnerCB::capacity(){
  return m_capacity;
}

//Size - returns the number of int values currently stored in the array
int InnerCB::size(){
  return m_size;
}

//Overloaded equals sign operator - Deaalocates space of current object, allocates new space and makes exact copy of InnerCB passed in parameter. Current sizes do not have to match
const InnerCB& InnerCB::operator=(const InnerCB& rhs){
  if(this != &rhs){  //prevents self-assignment
    delete [] m_buffer;  
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_buffer = new int[m_capacity];
    m_start = rhs.m_start;
    m_end = rhs.m_end;

    //copies the values from the rhs array to the lhs array
    for(int i=0; i<m_capacity; i++){
      m_buffer[i] = rhs.m_buffer[i];
    }
  }

  //returns a reference to the lhs object that has now copied the values of the rhs
  return *this;
} 

//Dump - A debugging function that prints out the contents of the InnerCB object
void InnerCB::dump(){
  std::cout << "InnerCB dump(): m_size = " << m_size << std::endl;

  int counter = m_start;  //counter variable to act as an iterator going through the array

  if(m_size == 0){ //checks if the array is empty, so as not to print anything since when the array is empty start will be one index ahead of end
    return;
  }

  while(counter != m_end){ //makes sure to stop right before reaching the end
    std::cout << "[" << counter << "] " << m_buffer[counter] << ", ";
    counter = (counter+1) % m_capacity;  //increments counter, accouinting for wrap around

    if(counter == m_end){ //displays last item in array for when the counter reaches the end
      std::cout << "[" << counter << "] " << m_buffer[counter] << ", ";
    }
  }
}

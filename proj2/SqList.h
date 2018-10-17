// File: SqList.h
// Author: Sepehr Hajbarat
// UMBC Fall 2017 CMSC 341 Project 2
// Date: 10/10/17
// SqList data structure where each linked list is guaranteed to have O(sqrt(n)) items

#ifndef _SQLIST_H_
#define _SQLIST_H_
#include "Int341.h"
#include <list>

class SqList{

 public:
  //Constructor, default
  SqList();
    
  //Copy constructor
  SqList(const SqList& other) ;
    
  //Overloaded Assignment Operator
  const SqList& operator=(const SqList& rhs);
    
  //Inserts at the beginning and calls consolidate()
  void addFirst (const Int341& x) ;

  //Inserts at the end and calls consolidate()
  void addLast (const Int341& x) ;
    
  //Removes an item at the beginning of the list, then calls consolidate()
  Int341 removeFirst ()  ;
    
  //Removes an item from the end of the list, then calls consolidate()
  Int341 removeLast ()  ; 
    
  //Inserts an item at a given position of the SqList, then calls consolidate()
  void add(int pos, const Int341& data) ;
    
  //Removes an item from a given position of a SqList and returns its value, then calls consolidate()
  Int341 remove(int pos) ;
    
  //Overloaded [] operator
  Int341& operator[](int pos) ;
    
  //Returns the position of the first occurrence of a value in a SqList
  int indexOf(const Int341& data) ;
    
  //Returns the number of items in a SqList
  int numItems();
    
  //prints out the values of the lists
  void dump() ; 
    
  //To be implemented by grading program
  void inspector();
    
 private:
  //maintains the O(sqrt(n)) bounds on the lengths of the top-level list and the inner lists
  void consolidate();
  //list of lists to represent outer list
  std::list< std::list<Int341> > L ;    
  //number of items in the entire list, n
  int m_items;
    
};

#endif

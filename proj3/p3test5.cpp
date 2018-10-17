// File: p3test5.cpp
//
// UMBC CMSC 341 Fall 2017 Project 3
//
// Tests copy constructor, destructor and assignment operator
//
// Should test this with valgrind
//

#include <iostream>
using namespace std ;

#include "ExpBST.h"

int main() {

  ExpBST T1(3,3,2.0) ;

  T1.insert(14) ;

  T1.insert(9) ; 
  T1.insert(8) ; 
  T1.insert(7) ;
  T1.insert(6) ; 
  T1.insert(5) ; 
  T1.insert(4) ; 

  T1.insert(18) ; 
  T1.insert(25) ;
  T1.insert(32) ; 

  cout << "Original T1:         " ;
  T1.inorder() ; cout << endl ;

  // Use copy constructor
  ExpBST *Tptr = new ExpBST(T1) ;

  cout << "Copied T1:           " ;
  Tptr->inorder() ; cout << endl; 
   
  ExpBST T2(3,3,2.0) ;

  T2.insert(50) ;
  T2.insert(25) ; T2.insert(75) ;
  // T2.inorder() ; cout << endl ;

  T2 = *Tptr ;
  cout << "Second copy:         " ;
  T2.inorder() ; cout << endl ; 

  cout << "Delete first copy...\n" ;
  delete Tptr ;

  cout << "Recheck original:    " ;
  T1.inorder() ; cout << endl ;
  cout << "Recheck second copy: " ;
  T2.inorder() ; cout << endl ; 

  return 0 ; 
}

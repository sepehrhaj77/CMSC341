// File: p3test4.cpp
//
// UMBC CMSC 341 Fall 2017 Project 3
//
// Checking return values from remove and find.
//

#include <iostream>
#include <cmath>
using namespace std ;

#include "ExpBST.h"


void report(const ExpBST& T) {


  cout << "***** ExpBST Report\n" ;

  cout << "   size = " << T.size() << endl ;
  cout << "   height = " << T.height() << endl ;
  cout << "   height/log(size) = " << ( (float) T.height() ) / log2(T.size()) << endl ;
    
  cout << "   numRebalance = " << T.getNumRebalance() << endl ;
  cout << "   failedRebalance = " << T.getFailedRebalance() << endl ;
  cout << "   exceedsHeight = " << T.getExceedsHeight() << endl ;

  cout << "   maxRebalanceDepth = " << T.getMaxRebalanceDepth() << endl ;
  cout << "   minRebalanceHeight = " << T.getMinRebalanceHeight() << endl ;
  cout << "   rebalanceFactor = " << T.getRebalanceFactor() << endl ;

}


int main() {

  ExpBST T(3,3,2.0) ;

  T.insert(14) ;

  T.insert(12) ; 
  T.insert(10) ; 
  T.insert(9) ; 
  T.insert(7) ;
  T.insert(4) ; 
  T.insert(3) ; 
  T.insert(1) ; 

  T.insert(15) ; 
  T.insert(18) ; 
  T.insert(21) ; 
  T.insert(25) ;
  T.insert(29) ; 
  T.insert(32) ; 
  T.insert(44) ; 

  T.insert(7) ;
  T.insert(3) ; T.insert(1) ; T.insert(4) ;
  T.insert(10) ; T.insert(9) ; T.insert(12) ;

  T.insert(25) ;
  T.insert(18) ; T.insert(15) ; T.insert(21) ;
  T.insert(32) ; T.insert(29) ; T.insert(44) ;

  //   T.dump() ;
  T.inorder() ; cout << endl ;

  int n, answer ;


  n = 3  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 4  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 29  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 39  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 301  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  // Checking remove...

  n = 21  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 18  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 7  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 13  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 29  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 32  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 14  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

}

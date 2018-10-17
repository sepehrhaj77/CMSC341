// File: p3test3.cpp
//
// UMBC CMSC 341 Fall 2017 Project 3
//
// Simple test of inserting and removing.
// This test includes inserting duplicates and
// attempt to remove keys not in the tree.
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

  ExpBST T(3, 4, 2.0) ;

  T.insert(14) ;

  T.insert(9) ; 
  T.insert(8) ; 
  T.insert(7) ;
  T.insert(6) ; 
  T.insert(5) ; 
  T.insert(4) ; 

  T.insert(18) ; 
  T.insert(25) ;
  T.insert(32) ; 

  // Inserting duplicates
  
  T.insert(3) ; T.insert(32) ; 
  T.insert(9) ; T.insert(18) ; 

  T.insert(1) ; T.insert(44) ;
  T.insert(12) ; T.insert(15) ; 
  T.insert(4) ; T.insert(29) ; 
  T.insert(10) ; T.insert(21) ;

  T.inorder() ; cout << endl ;

  cout << "removing ..." << endl; 
  int answer ;
  //   T.dump() ;

  int n ;

  n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  7 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  3 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 


  // Removing items that do not exist
  cout << endl ;
  n = 19 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 101 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = -32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  cout << endl ;

  n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  8 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  6 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  5 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  4 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  1 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 

  // Final report
  cout << endl ;
  report(T) ;
   
  return 0 ;
}

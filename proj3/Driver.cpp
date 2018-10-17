// File: p3test2.cpp
//
// UMBC CMSC 341 Fall 2017 Project 3
//
// Simple test that also removes nodes.
//
// Should see rebalancing during remove.
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

  ExpBST T(3, 3, 2.0) ;

  T.insert(14) ;

  T.insert(7) ;   T.insert(21) ;

  T.insert(7) ;   T.insert(21) ;
  T.insert(6) ;   T.insert(22) ;
  T.insert(8) ;   T.insert(20) ;

  T.insert(5) ;   T.insert(23) ;
  T.insert(9) ;   T.insert(19) ;

  T.insert(4) ;   T.insert(24) ;
  T.insert(10);   T.insert(18) ;

  T.insert(3) ;   T.insert(25) ;
  T.insert(11);   T.insert(17) ;

  T.insert(2) ;   T.insert(26) ;
  T.insert(12);   T.insert(16) ;

  T.insert(1) ;   T.insert(27) ;
  T.insert(13);   T.insert(15) ;


  T.inorder() ;
  cout << endl << endl ;

  report(T) ;

  cout << endl ;
  cout << "removing ..." << endl; 

  int n ;

  n = 27 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 26 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 24 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 23 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 22 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 20 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 19 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 17 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 16 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 

  cout << endl ;
  report(T) ;

  return 0 ;
}

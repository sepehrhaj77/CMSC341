// File: p3test1.cpp
// 
// UMBC CMSC 341 Fall 2017 Project 3
//
// Simple test of insertion
//

#include <iostream>
#include <cmath>
using namespace std ;

#include "ExpBST.h"

/*
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

  }*/



int main() {

  ExpBST T(3, 3, 2.0) ;
  int k;

  T.insert(70) ;
  T.inorder() ; cout << endl ;

  T.insert(30) ;
  T.inorder() ; cout << endl ;

  T.insert(110) ;

  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 40 *****\n" ;
  T.insert(40) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 20 *****\n" ;
  T.insert(20) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 41 *****\n" ;
  T.insert(41) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 31 *****\n" ;
  T.insert(31) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 32 *****\n" ;
  T.insert(32) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 33 *****\n" ;
  T.insert(33) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 19 *****\n" ;
  T.insert(19) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 34 *****\n" ;
  T.insert(34) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 35 *****\n" ;
  T.insert(35) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 36 *****\n" ;
  T.insert(36) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 37 *****\n" ;
  T.insert(37) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 38 *****\n" ;
  T.insert(38) ;
  T.inorder() ; cout << endl ;

  cout << "\n\n***** Insert 39 *****\n" ;
  T.insert(39) ;
  T.inorder() ; cout << endl ;
    
  cout << endl << endl ;
  //report(T) ;

}

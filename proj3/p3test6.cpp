// File: p3test6.cpp
//
// UMBC CMSC 341 Fall 2017 Project 3
//
// Simple test of locate() function
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


  T.insert(140) ;

  T.insert(90) ; 
  T.insert(80) ; 
  T.insert(70) ;
  T.insert(60) ; 
  T.insert(50) ; 
  T.insert(40) ; 
  T.insert(180) ; 
  T.insert(250) ;
  T.insert(320) ; 

  T.insert(85) ;
  T.insert(65) ;
  T.insert(55) ;

  T.insert(120) ;
  T.insert(115) ;
  T.insert(125) ;

  T.inorder() ; cout << endl ;

  int key = 9999 ;
  bool ans ;
  const char *str ;

  ans = T.locate(str="", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="LL", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="LLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="RRLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;


}

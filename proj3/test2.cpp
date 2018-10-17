// File: test2.cpp

#include <iostream>
using namespace std ;

#include "bst.h"

int main() {

  BST T ;

  T.insert(14) ;

  T.insert(7) ;
  T.insert(3) ; T.insert(1) ; T.insert(4) ;
  T.insert(10) ; T.insert(9) ; T.insert(12) ;

  T.insert(25) ;
  T.insert(18) ; T.insert(15) ; T.insert(21) ;
  T.insert(32) ; T.insert(29) ; T.insert(44) ;

  //   T.dump() ;

  DTYPE *ptr ;
  DTYPE x ;

  x = 9 ;
  if ( ( ptr = T.find(x) ) ) {
    cout << "Found " << *ptr << endl ;
  } else {
    cout <<  "Did not find " << x << endl ;
  }


  x = 19 ;
  if ( ( ptr = T.find(x) ) ) {
    cout << "Found " << *ptr << endl ;
  } else {
    cout <<  "Did not find " << x << endl ;
  }

  cout << "In order traversal:" << endl ;
  T.inorder() ;
  cout << endl ;

  cout << "\n\nMake a copy of T in S\n" ;
  BST S(T) ;

  cout << "Inorder walk of S\n" ;
  S.inorder() ;
  cout << endl ;

  cout << "*** Change T ***\n" ;
  ptr = T.find(44) ;
  *ptr = 144 ;

  cout << "In order traversal:" << endl ;
  T.inorder() ;
  cout << endl ;

  cout << "Inorder walk of S\n" ;
  S.inorder() ;
  cout << endl ;


  cout << "\n\n====== Dump of T =======\n" ;
  T.dump() ;

  cout << "\n\n====== Dump of S =======\n" ;
  S.dump() ;
}

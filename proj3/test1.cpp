// File: test1.cpp

#include <iostream>
using namespace std ;

#include "bst.h"

int main() {

  BST T ;

  T.insert(7) ;
  T.insert(3) ;
  T.insert(11) ;

  T.dump() ;

}

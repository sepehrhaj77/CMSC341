// File: p5test1.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Simple test of the HashFunction "functor" class
//
// Version: 2017-11-16
//

#include <iostream>
using namespace std ;

#include "PerfectHT.h"

int main() {

   HashFunction::setSeed(31871) ;

   HashFunction::m_debug = true ;  // yes print reboot info 

   HashFunction h(3) ;  // hash function for table with 3 slots

   int i=0 ;

   cout << "Initial hash:\n" ;
   while (true) {
      cout << "h(\"focus\")    = " << h("focus") << endl ;
      cout << "h(\"louver\")   = " << h("louver") << endl ;
      cout << "h(\"wormhole\") = " << h("wormhole") << endl ;
      cout << endl ;

      if (++i > 20) break ;

      h.reboot() ;   // re-select MAD parameters
   }

   return 0 ;
}

// File: p5test5.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Testing for memory leaks after throwing exception.
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

int main() {

   HashFunction::setSeed(767907) ;

   HashFunction::m_debug = true ;  // yes print reboot info 
   SecondaryHT::m_debug = true ;

   vector<const char *> w ;

   // Adding the same word "aardvark" 3 times guarantees
   // that SecondaryHT will not be able to create a
   // hash table without any collisions.
   //
   w.push_back("aardvark") ;
   w.push_back("aardvark") ;
   w.push_back("aardvark") ;

   try {

      SecondaryHT H2(w) ;    // will throw very_unlucky

   } catch (very_unlucky& e) {

       cout << "Exception caught: " << e.what() << endl ;

       return 127 ;  // something other than 0
   }

   return 0 ;
}

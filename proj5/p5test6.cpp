// File: p5test6.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Check copy constructor and assignment operator
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

int main() {

   HashFunction::setSeed(418738) ;

   HashFunction::m_debug = true ;  // yes print reboot info 
   SecondaryHT::m_debug = true ;

   // Prep vector for SecondaryHT constructor
   //
   vector<const char *> w ;
   w.push_back("aardvark") ;
   w.push_back("aardwolf") ;
   w.push_back("aaron") ;
   w.push_back("aback") ;
   w.push_back("abacus") ;

   // First SecondaryHT created with vector w.
   //
   SecondaryHT *H2ptr1 = new SecondaryHT(w) ;

   // Use copy constructor
   //
   SecondaryHT *H2ptr2 = new SecondaryHT(*H2ptr1) ;

   delete H2ptr1 ;

   // Use copy constructor again
   //
   SecondaryHT *H2ptr3 = new SecondaryHT(w) ;

   // Use SecondaryHT assingment operator
   // Should get deep copy.
   //
   *H2ptr3 = *H2ptr2 ;

   // Prep another vector for SecondaryHT constructor.
   //
   vector<const char *> w4 ;
   w4.push_back("ablutions") ;
   w4.push_back("ably") ;
   w4.push_back("abnegation") ;

   delete H2ptr2 ;

   // Another SecondaryHT created using vector w4
   //
   SecondaryHT *H2ptr4 = new SecondaryHT(w4) ;

   // Overwrite data stored in lhs of assignment
   // Should deallocate memory in assignment operator
   //
   *H2ptr4 = *H2ptr3 ;

   delete H2ptr3 ;

   // Let's take a look. Should have strings from
   // original vector<const char *> w
   //
   H2ptr4->dump() ;

   delete H2ptr4 ;

   return 0 ;
}

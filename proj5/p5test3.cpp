// File: p5test3.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Simple test of the SecondaryHT class.
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"
#include "1Kwords.h"


// Check that str is in H2.
//
void testIn (const SecondaryHT& H2, const char* str) {
   if (H2.isMember(str)) {
      cout << "Correct: " << str << " is in the hash table\n" ;
   } else {
      cout << "**Wrong: " << str << " is in the hash table\n" ;
   }
}


// Check that str is NOT in H2
//
void testOut (const SecondaryHT& H2, const char* str) {
   if (H2.isMember(str)) {
      cout << "**Wrong: " << str << " is not in the hash table\n" ;
   } else {
      cout << "Correct: " << str << " is not in the hash table\n" ;
   }
}


int main() {

   HashFunction::setSeed(3870151) ;

   HashFunction::m_debug = true ;  // yes print reboot info 
   SecondaryHT::m_debug = true ;

   // Prep vector used to invoke SecondaryHT constructor
   //
   vector<const char *> w ;
   w.push_back("aardvark") ;
   w.push_back("aardwolf") ;
   w.push_back("aaron") ;
   w.push_back("aback") ;
   w.push_back("abacus") ;


   SecondaryHT H2(w) ;   // make a secondary hash table.

   H2.dump() ;


   // check for errors
   //
   for (int i=0 ; i < 5 ; i++) {
      testIn(H2, w[i]) ;
   }

   for (int i=20 ; i < 25 ; i++) {
      testOut(H2, words[i]) ;
   }

   return 0 ;
}

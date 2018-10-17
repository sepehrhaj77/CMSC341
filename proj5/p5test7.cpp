// File: p5test7.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Simple test PerfectHT class.
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

// Defines global words[] array and numWords
//
#include "1Kwords.h"


int main() {

   HashFunction::setSeed(1418021) ;

   HashFunction::m_debug = true ;  // yes print reboot info 
   SecondaryHT::m_debug = true ;
   PerfectHT::m_debug = true ;


   // Create a Perfect Hashing table using
   // the first n strings in the words[] array.
   //
   int n = 400 ; PerfectHT H(words,n) ;


   // let's have a look
   //
   H.dump() ;


   // Check for errors.

   // These strings should be in H.
   //
   int notInError = 0 ;
   for (int i=0 ; i < n ; i++) {
      if(! H.isMember(words[i]) ) notInError++ ;
   }

   // These strings should NOT be in H.
   //
   int notOutError = 0 ;
   for (int i=n+1 ; i < numWords ; i++) {
      if( H.isMember(words[i]) ) notOutError++ ;
   }

   cout << "\nError Report\n" ;
   cout << "   Number of words that should be in H, but are not: "
        << notInError << endl ;

   cout << "   Number of words that should not be in H, but are: "
        << notOutError << endl ;

   return 0 ;
}

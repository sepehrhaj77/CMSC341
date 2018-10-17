// File: p5test9.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Bigger test of the PerfectHT  class
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

// defines words[] array and numWords
//
#include "words.h"


int main() {

   HashFunction::setSeed(8310317) ;

   HashFunction::m_debug = false ;  // don't debug in big tests
   SecondaryHT::m_debug = false ;
   PerfectHT::m_debug = false ;

   int n = 24000 ; PerfectHT H(words,n) ;

//   H.dump() ;


   // These words should be in H
   //
   int notInError = 0 ;
   for (int i=0 ; i < n ; i++) {
      if(! H.isMember(words[i]) ) notInError++ ;
   }

   // These words should NOT be in H
   //
   int notOutError = 0 ;
   for (int i=n+1 ; i < 2 * n ; i++) {
      if( H.isMember(words[i]) ) notOutError++ ;
   }

   cout << "\nError Report\n" ;
   cout << "   Number of words that should be in H, but are not: "
        << notInError << endl ;

   cout << "   Number of words that should not be in H, but are: "
        << notOutError << endl ;

   return 0 ;
}

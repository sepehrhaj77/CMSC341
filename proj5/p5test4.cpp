// File: p5test4.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Bigger test of the SecondaryHT class.
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

// First 1000 words.
// Defines words[] array and numWords.
//
#include "1Kwords.h"

int main() {

   HashFunction::setSeed(2127890712) ;

   HashFunction::m_debug = false ;  // no output for bigger tests
   SecondaryHT::m_debug = false ;

   int notInError, notOutError ;
   SecondaryHT *H2ptr ;

   // Do 100 trials of 3 
   //
   for (int i=0 ; i < 100 ; i++) {

      // Prep vector given to SecondaryHT constructor
      // words[] is a global array
      //
      vector<const char *> w ;
      w.push_back(words[3*i]) ;     // next set of 3 words
      w.push_back(words[3*i+1]) ;
      w.push_back(words[3*i+2]) ;

      H2ptr = new SecondaryHT(w) ;

      notInError = 0 ;   // reset error count
      notOutError = 0 ;

      cout << "\n-------------------------------------\n" ;
      cout << "Trial #" << i+1 << " error report" << endl ;

      // These 3 strings should be in H2
      //
      if (! H2ptr->isMember(words[3*i]) ) notInError++ ;
      if (! H2ptr->isMember(words[3*i+1]) ) notInError++ ;
      if (! H2ptr->isMember(words[3*i+2]) ) notInError++ ;

      if (H2ptr->isMember(words[3*i+3]) ) notOutError++ ;
      if (H2ptr->isMember(words[3*i+4]) ) notOutError++ ;
      if (H2ptr->isMember(words[3*i+5]) ) notOutError++ ;
      
      // These 3 strings should NOT be in H2
      //
      cout << "\nError Report\n" ;
      cout << "   Number of words that should be in, but are not: "
	   << notInError << endl ;

      cout << "   Number of words that should not be in, but are: "
	   << notOutError << endl ;
      cout << endl ;

      delete H2ptr ;   // deallocate
   }


   // Do 100 trials of 5 
   //
   for (int i=0 ; i < 100 ; i++) {

      // Prep vector given to SecondaryHT constructor
      // words[] is a global array
      //
      vector<const char *> w ;
      w.push_back(words[5*i]) ;         // next set of 5 words
      w.push_back(words[5*i+1]) ;
      w.push_back(words[5*i+2]) ;
      w.push_back(words[5*i+3]) ;
      w.push_back(words[5*i+4]) ;

      H2ptr = new SecondaryHT(w) ;

      notInError = 0 ;     // reset error count
      notOutError = 0 ;

      cout << "\n-------------------------------------\n" ;
      cout << "Trial #" << i+1 << " error report" << endl ;

      // These 5 strings should be in H2
      //
      if (! H2ptr->isMember(words[5*i]) ) notInError++ ;
      if (! H2ptr->isMember(words[5*i+1]) ) notInError++ ;
      if (! H2ptr->isMember(words[5*i+2]) ) notInError++ ;
      if (! H2ptr->isMember(words[5*i+3]) ) notInError++ ;
      if (! H2ptr->isMember(words[5*i+4]) ) notInError++ ;

      // These 5 strings should NOT be in H2
      //
      if (H2ptr->isMember(words[5*i+5]) ) notOutError++ ;
      if (H2ptr->isMember(words[5*i+6]) ) notOutError++ ;
      if (H2ptr->isMember(words[5*i+7]) ) notOutError++ ;
      if (H2ptr->isMember(words[5*i+8]) ) notOutError++ ;
      if (H2ptr->isMember(words[5*i+9]) ) notOutError++ ;
      
      cout << "\nError Report\n" ;
      cout << "   Number of words that should be in, but are not: "
	   << notInError << endl ;

      cout << "   Number of words that should not be in, but are: "
	   << notOutError << endl ;
      cout << endl ;

      delete H2ptr ;   // deallocate
   }

   return 0 ;
}

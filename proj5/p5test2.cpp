// File: p5test2.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Observe some statistically behavior of hash function.
//
// Version: 2017-11-16
//

#include <iostream>
using namespace std ;

#include "PerfectHT.h"
#include "1Kwords.h"


int main() {

   HashFunction::setSeed(38701) ;

   HashFunction::m_debug = true ;  // yes print reboot info 

   int slot ;    // where in the hash table

   HashFunction h(numWords) ;

   int m = h.tableSize() ;  // table size

   // dynamically allocated array to count # of collisions
   int *count = new int[m] ;

   // Do 10 times
   // Hash every word in words[] array defined in "1Kwords.h"
   // For each slot, count number of times that slot was hit.
   // 
   for (int k=0 ; k < 10 ; k++) {

      // check table size might have changed after reboot.
      // if so, reallocate
      // 
      if ( m != h.tableSize() ) { 
         m = h.tableSize() ;
         delete [] count ;
         count = new int[m] ;
      }

      // clean up previous counts, or initial garbage
      // 
      for (int i=0 ; i < m ; i++) {
	 count[i] = 0 ;
      }

      // hash each word in words[] array
      //
      for (int i=0 ; i < numWords ; i++) {
	 slot = h(words[i]) ;   
	 count[slot]++  ;
      }


      // initialize stats
      //
      int numSlotsWithCollisions=0 ;
      int numSlotsWithItems=0 ;
      int maxCollisionsInOneSlot=0 ;
      float totalSlotLengths=0 ;


      // Go through count[] array and collect some stats
      //
      for (int i=0 ; i < m ; i++) {

	 if (count[i] > 0) {
	    numSlotsWithItems++ ;
	    totalSlotLengths += count[i] ;
	 }

	 if (count[i] > 1) {
	    numSlotsWithCollisions++ ;
	    if (count[i] > maxCollisionsInOneSlot) {
	       maxCollisionsInOneSlot = count[i] ;
	    }
	 }
      }


      // report some stats
      //
      cout << "--------------------------------------------------\n" ;
      cout << "Trial #" << k+1 << endl ;
      cout << "--------------------------------------------------\n" ;
      cout << "table size = " << h.tableSize() << endl ;
      cout << "number of non-empty slots = " << numSlotsWithItems << endl ;
      cout << "average number of items in non-empty slots = " 
	   << totalSlotLengths/numSlotsWithItems << endl ; 
      cout << "number of slots with collisions = " << numSlotsWithCollisions << endl ;
      cout << "maxCollisionsInOneSlot = " << maxCollisionsInOneSlot << endl ;
      cout << endl ;


      // get new hash function
      //
      h.reboot() ;

   }

   delete [] count ;

   return 0 ;
}

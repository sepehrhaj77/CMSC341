// File: p5test8.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Testing copy constructor and assignment operator for PerfectHT class.
//
// Version: 2017-11-16
//

#include <iostream>
#include <vector>
using namespace std ;

#include "PerfectHT.h"

// Defines global array words and numWords
//
#include "1Kwords.h"


int main() {

   HashFunction::setSeed(3810021) ;

   HashFunction::m_debug = true ;  // yes print reboot info 
   SecondaryHT::m_debug = true ;
   PerfectHT::m_debug = true ;

   // make Perfect Hashing table with first 24 words.
   //
   PerfectHT *Hptr1 = new PerfectHT(words,24) ;

   // use copy constructor
   //
   PerfectHT *Hptr2 = new PerfectHT(*Hptr1) ;

   delete Hptr1 ;   // use destructor

   // make another Perfect Hashing table using words 332 to 481.
   //
   PerfectHT *Hptr3 = new PerfectHT(&words[331],150) ;

   // Use assignment operator
   //
   *Hptr3 = *Hptr2 ;

   delete Hptr2 ;   // use destructor

   // make yet another Perfect Hashing table using words 715 to 747. 
   PerfectHT *Hptr4 = new PerfectHT(&words[714],34) ;

   // Use assignment operator
   //
   *Hptr4 = *Hptr3 ;

   delete Hptr3 ;   // clean up

   Hptr4->dump() ;  // let's see

   delete Hptr4 ;   // clean up

   return 0 ;
}

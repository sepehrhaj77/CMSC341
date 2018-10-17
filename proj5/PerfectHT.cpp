// File: PerfectHT.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Implementation of HashFunction, SecondaryHT & PerfectHT classes.
//
// Version: 2017-11-30
//

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std ;

#include "PerfectHT.h"
#include "primes.h"


// =====================================================================
// HashFunction class implementation 
// =====================================================================


// By default do not print info to screen
//
bool HashFunction::m_debug = false ;


// Constructor.
// The constructor picks the smallest prime # greater than
// or equal to n for the table size. 
// Default value of n defined in header.
//  
// Initializes other hash function parameters randomly.
//
HashFunction::HashFunction(int n /* =100*/ ) {

   // note: maxPrime defined in prime.h
   //
   if (n > maxPrime) throw out_of_range("HashTable size too big.\n") ;

   m_tsize = findPrime(n) ;
   m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
   m_shift =  rand() % m_tsize ;
   m_multiplier = 33 ;  // magic number from textbook
   m_reboots = 0 ;

}


// Function that maps string to unsigned int.
// Return value can be much larger than table size.
// Uses m_multiplier data member.
// Return value must be unsgined for overflow to work correctly.
//
unsigned int HashFunction::hashCode(const char *str) const {

   unsigned int val = 0 ; 

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * m_multiplier + str[i] ;
      i++ ;
   }
   return val ; 
}


// Getter for table size
//
int HashFunction::tableSize() const {
   return m_tsize ;
}


// Overloaded () operator that makes this a "functor" class.
// Returns the slot in the hash table for str.
// Uses the MAD method: h(x) = (ax + b) % m where 
// the parameters are:
//   a = m_factor
//   b = m_shift
//   m = m_tsize
//
unsigned int HashFunction::operator() (const char *str) const {
   return ( m_factor * hashCode(str) + m_shift ) % m_tsize ;
}


// Pick new parameters for MAD method and the hashCode function.
// Note: can change table size.
//
void  HashFunction::reboot() {

   // Implement the reboot function
   // pick new values for m_factor and m_shift each reboot
   //   make sure you get *different* values
   // change m_multiplier to next odd number  every 3rd reboot
   // increase table size to next prime # every 5th reboot

  unsigned int oldFac = m_factor;
  unsigned int oldShift = m_shift;

  m_reboots+=1;

  //if third reboot
  if((m_reboots % 3) == 0) {
      m_multiplier += 2;
    }

  //if fifth reboot
  if((m_reboots % 5) == 0){
    m_tsize = findPrime(m_tsize+1);
  }

  //make sure m_factor and m_shift are different
  do{
    m_factor = ( rand() % (m_tsize - 1)) + 1;
    m_shift = rand() % m_tsize;
  }while(m_factor == oldFac and m_shift == oldShift);

  //debug statements
  if(m_debug){
    cout << "---- reboot #" << m_reboots << ": m_tsize = " << m_tsize << " m_multiplier = " << m_multiplier << " m_factor = " << m_factor << " m_shift = " << m_shift << endl;
  }
}


// Set random seed for the random number generator.
// Call once at the start of the main program.
// Uses srand() and rand() from cstdlib which is
// shared with other code. For compatibility with
// C++98, it does not have a private random number 
// generator (e.g., mt19337).
//
void HashFunction::setSeed(unsigned int seed) {
   srand(seed) ;
}


// Find the smallest prime number greater than or equal to m.  

int HashFunction::findPrime(int m) {

   // Prime numbers are in global array primes[]
   // included from "primes.h"
   //
   // Use binary search!!

  if(m > maxPrime - 1){
    throw out_of_range("prime number too big!");
  }

  int l = 0; 
  int r = numPrimes - 1;

  //make sure left index is not equal to right index
  while (l <= r)
    {
      int mid = l + (r-l)/2;
      // Check if m is present at mid
      if (primes[mid] == m or primes[mid-1] < m and primes[mid] > m) 
        return primes[mid];  
 
      // If m greater, ignore left half  
      if (primes[mid] < m) 
        l = mid + 1; 
 
      // If m is smaller, ignore right half 
      else
	r = mid - 1; 
    }
 
  // if we reach here, then element was not present
  return -1; 
}



// =====================================================================
// SecondaryHT class implementation 
// =====================================================================


// By default do not print debugging info 
bool SecondaryHT::m_debug = false ;


// Create a secondary hash table using the char * strings
// stored in "words". Makes copy of each item in words.
//
SecondaryHT::SecondaryHT(vector<const char *> words) {

   //
   // Keep trying until a table with no collisions is found
   // 
   // wrap debugging statements in "if (m_debug) { ... }"
   //
   // remember that calling HashFunction::reboot() can change 
   // the table size!
   //
   // use strdup to copy char * strings
   //
  m_attempts = 1;
  m_size = words.size();

  //vector to store the indeces of the hashed items
  vector<int> hashIndeces;
  hash = HashFunction(pow(m_size, 2));

  //variable to keep track of the hashed value of each string
  int val = 0;
  vector<int>::iterator it;

  //for loop to go through entire vector of words 
  unsigned int i;
  for(i=0; i < words.size(); i++){

    //use iterator to make sure collisions dont exist
    val = hash(words[i]);
    it = find(hashIndeces.begin(), hashIndeces.end(), val);
    
    if(it == hashIndeces.end()){ //if the hashed value does not exist in our vector of existing indeces, add it to the vector; AKA no collisions
      hashIndeces.push_back(val);
    }
    
    else{ //if there is a collision, reboot the hash function, clear the vector, and redo the hashing of all the elements
      hash.reboot();
      i=-1;
      hashIndeces.clear();
      m_attempts += 1;
    }
    
    //check for too many attempts
    if(m_attempts > maxAttempts){
      throw very_unlucky("exceeded maximum attempts");
    }
  }
  
  //allocate memory for T2
  T2 = new char*[hash.tableSize()];
  
  for(int i = 0; i < hash.tableSize(); i++){
    T2[i] = NULL;
  }

  //for loop to populate T2
  for(unsigned int i = 0; i < hashIndeces.size(); i++){
    char* temp = NULL;
    temp = strdup(words[i]);
    T2[hashIndeces[i]] = temp;
  }
}


// Copy constructor. Remember to strdup.
//
SecondaryHT::SecondaryHT(const SecondaryHT& other) {
  //copy over member variables
  m_attempts = other.m_attempts;
  m_size = other.m_size;
  hash = other.hash;

  //allocate space for T2 and set the values to null
  T2 = new char*[other.hash.tableSize()];
  for(int i = 0; i < hash.tableSize(); i++){
    T2[i] = NULL;
  }

  //populate T2 with what's in the other T2
  for(int i = 0; i < other.hash.tableSize(); i++){
    if(other.T2[i] != NULL){
      char* temp = other.T2[i];
      T2[i] = strdup(temp);
    }
  }
}


// Destructor. Use free() to free strings.
//
SecondaryHT::~SecondaryHT() {
  //go through T2 and free all the strings created by strdup()
  for (int i=0 ; i < hash.tableSize() ; i++) {
    if(T2[i] != NULL)
      free(T2[i]);
  }

  //deallocate the T2 array
  delete[] T2;
}


// Assignment operator. Remember to use strdup() and free()
//
const SecondaryHT& SecondaryHT::operator=(const SecondaryHT& rhs) {
  //delete the stuff that already exists in the lhs table
  for(int i = 0; i < hash.tableSize(); i++){
    free(T2[i]);
    T2[i] = NULL;
  }
  delete[] T2;

  //copy member variables
  m_attempts = rhs.m_attempts;
  m_size = rhs.m_size;
  hash = rhs.hash;

  //allocate space for T2 and initialize the values to NULL
  T2 = new char*[rhs.hash.tableSize()];
  for(int i = 0; i < hash.tableSize(); i++){
    T2[i] = NULL;
  }

  //set the values in T2 to the other T2's values
  for(int i = 0; i < rhs.hash.tableSize(); i++){
    if(rhs.T2[i] != NULL){
      char* temp = rhs.T2[i];
      T2[i] = strdup(temp);
    }
  }

  return *this;

}


// returns whether given word is in this hash table.
//
bool SecondaryHT::isMember (const char *word) const {

   int slot = hash(word) ;

   assert ( 0 <= slot && slot < hash.tableSize() ) ;

   if (T2[slot] == NULL) return false ;

   if ( strcmp(word, T2[slot]) != 0 ) return false ;

   return true ; 
}


// getter. Actually, the hash function has the size.
//
int SecondaryHT::tableSize() const {
   return hash.tableSize() ;
}


// Pretty print for debugging
//
void SecondaryHT::dump() const {
   cout << "=== Secondary Hash Table Dump: ===\n" ;
   cout << "Table size = " << hash.tableSize() << endl ;
   cout << "# of items = " << m_size << endl ;
   cout << "# of attempts = " << m_attempts << endl ;
 
   for (int i=0 ; i < hash.tableSize() ; i++) {
      cout << "T2[" << i << "] = " ;
      if (T2[i] != NULL) cout << T2[i] ;
      cout << endl ;
   }

   cout << "==================================\n" ;
}



// =====================================================================
// PerfectHT class implementation 
// =====================================================================


// by default, do not print debugging info
//
bool PerfectHT::m_debug = false ;


// Create a Perfect Hashing table using the first n strings 
// from the words array.
//
PerfectHT::PerfectHT (const char *words[], int n) {

   // Implement constructor for PerfectHT here.
   //
   // You will need an array of vectors of char * strings.
   // Something like;
   //
   //    vector<const char *> *hold = new vector<const char *>[m] ;
   //
   // Each hold[i] is a vector that holds the strings
   // that hashed to slot i. Then hold[i] can be passed
   // to the SecondaryHT constructor.
   //


  //create a new hash
  hash = HashFunction(n);
  int tableSize = hash.tableSize();

  //initialize PHT1 and 2
  PHT1 = new char*[tableSize];
  PHT2 = new SecondaryHT*[tableSize];

  //vector to hold all c-stringa
  vector<const char *> *hold = new vector<const char *>[tableSize];

  //initialize the values to NULL by default
  for(int i=0; i<hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  //decide which vector to store the words in
  for(int i = 0; i<n; i++){
    hold[hash(words[i])].push_back(words[i]);
  }

  for(int i = 0; i < tableSize; i++){
    if(hold[i].size() == 1){ //if there is only one element in the vector, no collisions found. Put it in PHT1
      PHT1[i] = strdup(hold[i].at(0));
    }
    else if(hold[i].size() > 1){ //if there is a collision, create a new Secondary Hash Table at that index in PHT2
      PHT2[i] = new SecondaryHT(hold[i]);
    }
  }

  //hold is not a member variable so it will not be taken care of in the destructor, deallocate the memory here
  delete[] hold;
}


// Copy constructor. Use strdup or SecondaryHT copy constructor.
//
PerfectHT::PerfectHT(const PerfectHT& other) {
  hash = other.hash;

  //creates le tables and does the intialization
  PHT1 = new char* [hash.tableSize()];
  PHT2 = new SecondaryHT* [hash.tableSize()];
  for(int i = 0; i < hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  //copy values from the other table
  for(int i = 0; i < hash.tableSize(); i++){
    if(other.PHT1[i] != NULL){
      PHT1[i] = strdup(other.PHT1[i]);
    }
    //if there's nothing in PHT1 at the current index, check PHT2
    else if(other.PHT2[i] != NULL ){
      PHT2[i] = new SecondaryHT(*(other.PHT2[i]));
    }
  }
}


// Destructor. Remember to use free() for strdup-ed strings.
//
PerfectHT::~PerfectHT() {
  //for loop to go through and free the string created by strdup()
  for(int i = 0; i < hash.tableSize(); i++){
    if(PHT1[i] != NULL){
      free(PHT1[i]);
    }
    //if theres nothing to free at PHT1 check in PHT2 to free something
    else if(PHT2[i] != NULL){
      delete PHT2[i];
    }
  }

  //deallocate the space for the PHT1 and PHT2 arrays
  delete[] PHT1;
  delete[] PHT2;
}


// Assignment operator. Use strdup() and free() for strings.
//
const PerfectHT& PerfectHT::operator=(const PerfectHT& rhs) {
  //for loop to go through array
  for(int i = 0; i < hash.tableSize(); i++){
    if(PHT1[i] != NULL){
      free(PHT1[i]);
    }
    //if nothing in PHT1 check PHT2 instead
    else if(PHT2[i] != NULL){
      delete PHT2[i];
    }
  }

  delete[] PHT1;
  delete[] PHT2;

  //copy the hash functi0n
  hash = rhs.hash;

  //creates le tables and does the intialization
  PHT1 = new char* [hash.tableSize()];
  PHT2 = new SecondaryHT* [hash.tableSize()];
  for(int i = 0; i < hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  //copy values from the other table
  for(int i = 0; i < hash.tableSize(); i++){
    if(rhs.PHT1[i] != NULL){
      PHT1[i] = strdup(rhs.PHT1[i]);
    }
    //if not located in PHT1 then check PHT2 instead and see if it's in there
    else if(rhs.PHT2[i] != NULL ){
      PHT2[i] = new SecondaryHT(*(rhs.PHT2[i]));
    }
  }
  return *this;
}


// Returns whether word is stored in this hash table.
//
bool PerfectHT::isMember(const char * str) const {
   int slot = hash(str) ; 

   if (PHT1[slot] == NULL && PHT2[slot] == NULL) return false ;

   if (PHT1[slot] != NULL) return strcmp(str,PHT1[slot]) == 0 ;

   return PHT2[slot]->isMember(str) ;
}


// Pretty print for debugging.
//
void PerfectHT::dump() const {
   int m = hash.tableSize() ;   

   cout << "------------- PerfectHT::dump()  -------------\n" ;
   cout << "table size = " << hash.tableSize() << endl ;
   cout << endl ;
   for (int j=0 ; j < m ; j++) {
      cout << "[" << j << "]:  " ;
      if (PHT1[j] != NULL) cout << PHT1[j] ;
      if (PHT2[j] != NULL) {
         cout << endl ;
         PHT2[j]->dump() ;
      }
      cout << endl ;
   }

   cout << "----------------------------------------------\n" ;
}

// File: p2comptest.cpp
//
// UMBC Fall 2017 CMSC 341 Project 2
// 
// Check that implementation of SqList has every
// function required in the project description.
//
// Version: Sep 28 2017 08:30
//

#include <iostream> 
#include "SqList.h"
#include "Int341.h"

using namespace std ;


void SqList::inspector() {

  cout << "\n\n=============================================\n" ;
  cout << "SqList::inspector() report\n" ;
  cout << "=============================================\n" ;

  bool errorFound = false ;

  int n = numItems() ;

  list< list<Int341> >::iterator it ;


  // calculate total number of items in data structure
  //
  int sum = 0 ;
  for (it = L.begin() ; it != L.end() ; it++) {
    sum += it->size() ;
  }


  // report on size()
  //
  if (n == sum) {
    cout << "numItems() correct\n" ;
  } else {
    errorFound = true ;
    cout << "*** numItems() wrong! " << endl 
	 << "    numItems() = " << n << endl 
         << "    sum of sizes = " << sum << endl ; 
  }


  // special case if no items
  //
  if (L.size() == 0) {
    cout << "Empty SqList, nothing more to check\n" ; 
    return ;
  }


  // Run down the outer list and check if there are any
  // of these errors: empty list, list too long, adjacent
  // short lists.
  //
  int prevSize, currSize ;
  bool prevIsShort = false ;
  bool currIsShort ;
   
  int index = 0 ;
   
  for(it = L.begin() ; it != L.end() ; it++) {

    currSize =  it->size() ;

    if (currSize == 0) {    // empty?
      errorFound = true ;
      currIsShort = true ;
      cout << "*** Inner list " << index << " empty! " << endl  ;

    } else if ( (currSize-1)*(currSize-1) > 4*n ) {   // too long?
      errorFound = true ;
      cout << "*** Inner list " << index << " too long! " << endl 
	   << "    inner list size  = " << currSize << endl 
	   << "    sum of sizes = " << n << endl ; 

    } else if ( 4*(currSize+1)*(currSize+1) <= n) {  // too short?
      currIsShort = true ;
      if (prevIsShort) {  // adjacent shorts?
	errorFound = true ;
	cout << "*** Adjacent short inner lists found! " << endl 
	     << "    sum of sizes = " << n << endl 
	     << "    inner list " << index-1 << " has size  = " << prevSize << endl  
	     << "    inner list " << index << " has size  = " << currSize << endl ;
      }
    } else {
      currIsShort = false ;
    }
    prevSize = currSize ;
    prevIsShort = currIsShort ;
    index++ ;
  }

  if (!errorFound) {
    cout << "No errors found!\n" ;
  }

  cout << "=============================================\n" ;
   
}



int main() {
  SqList S ;

  Int341::m_debug = true ;

  // Use add and remove functions
  //
  for (int i=0 ; i < 100 ; i++) {
    S.addLast(Int341(i)) ;
  }
  
  Int341::report();
  
  for (int i=0 ; i < 100 ;i++) {
    S.addFirst(Int341(i*i)) ;
  }

  Int341::report();

  Int341 result ;
  for (int i=0 ; i < 50 ; i++) {
    cout << "removee" << endl;
    result = S.removeFirst() ; 
    cout << "remove" << endl;
  }

  Int341::report();

  for (int i=0 ; i < 50 ; i++) {
    result = S.removeLast() ; 
  }

  S.dump() ;
  Int341::report() ;
  S.inspector() ;

  Int341 answer ;

  for (int i=1 ; i < 9 ; i+=7) {
    S.add(i,i*i) ;
  }
  for (int i=5 ; i < 18 ; i+=3) {
    answer = S.remove(i) ;
  }

  S.dump() ;
  Int341::report() ;
  S.inspector() ;

  SqList T(S) ;
  SqList U ;
  U = T ;

  U.dump() ;

  for(int i=0 ; i < U.numItems() ; i++) {
    cout << "U[" << i << "] = " << U[i].m_data << endl ;
  }
  for(int i=0 ; i < U.numItems() ; i+=7) {
    U[i] = 1000 + i ; 
    cout << "U[" << i << "] = " << U[i].m_data << endl ;
  }

  Int341 stuff(484) ;
  int pos = U.indexOf(stuff) ;
  if (pos >= 0) {
    cout << "Found " << stuff.m_data << " in index " << pos << endl ;
  } else {
    cout << "Did not find " << stuff.m_data << endl ;
  }

  stuff = Int341(99999) ;
  pos = U.indexOf(stuff) ;
  if (pos >= 0) {
    cout << "Found " << stuff.m_data << " in index " << pos << endl ;
  } else {
    cout << "Did not find " << stuff.m_data << endl ;
  }


  U.dump() ;
  Int341::report() ;

  U.inspector() ;

  return 0 ;
}

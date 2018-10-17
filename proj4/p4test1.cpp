// File: p4test1.cpp
//
// UMBC CMSC 341 Fall 2017 Project 4
//
// Simple test of MedianHeap with int
//

#include <iostream>
using namespace std ;

#include "MedianHeap.h"

bool lt(const int& x, const int& y) {
  return x < y ;
}


bool gt(const int& x, const int& y) {
  return x > y ;
}


int main() {
    MedianHeap<int> MH(lt,gt,12) ;

    MH.insert(5) ;
    MH.insert(7) ;
    MH.insert(13) ;
    MH.insert(9) ;
    MH.insert(17) ;
    MH.dump() ;

    // test some edge cases
    MedianHeap<int> MH2(lt,gt,3) ;

    cout << "\n\nTest some edge cases:\n" ;

    MH2.insert(10) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;

    MH2.insert(20) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;

    MH2.insert(5) ;
    cout << "MH2.getMin() = " << MH2.getMin() << endl ;
    cout << "MH2.getMedian() = " << MH2.getMedian() << endl ;
    cout << "MH2.getMax() = " << MH2.getMax() << endl ;
}


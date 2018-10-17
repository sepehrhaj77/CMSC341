// File: SqList.h
// Author: Sepehr Hajbarat
// UMBC Fall 2017 CMSC 341 Project 2
// Date: 10/10/17
// SqList data structure where each linked list is guaranteed to have O(sqrt(n)) items
#include "SqList.h"
#include "Int341.h"
#include <list>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

//SqList() - default constructor that intializes a SqList properly
SqList::SqList(){
  list<Int341> temp;
  L.push_back(temp);
  m_items = 0;  
}

//SqList(const SqList& other) - Copy constructor. Makes complete copy of other object
SqList::SqList(const SqList& other): L(other.L),m_items(other.m_items)
{
}

//operator = - overloaded assignemnt operator.
const SqList& SqList::operator= (const SqList& rhs){
  m_items = rhs.m_items;
  L = rhs.L;
  return *this;
}

//consolidate() - maintains the O(sqrt(n)) bounds on the lengths of the top-level list and the inner lists. If an empty outer list is found, delete it. If two short lists in a row are encountered, merge them. If an inner list is found to have more than 2sqrt(n) items, split them into two lists of equal length
void SqList::consolidate(){
  //variable to hold value of what is too long for a list
  double big = 2 * sqrt(m_items);
  //variable to hold the value of what is "too short" for a list
  double small = sqrt(m_items)/2;
  //variable to keep track of whether two short lists have been encountered in a row
  int numSmall = 0;

  double listSize;

  //for loop to iterate through outer list
  for(list< list<Int341> >::iterator out = L.begin(); out != L.end(); out++){
    //if current list is empty, delete it
    if((*out).empty()){
      out = L.erase(out);
    }
    listSize = out->size();
    //checking to see if the current list is short
    if(listSize <= small){
      numSmall++; //increment number of short lists encountered in a row
      if(numSmall == 2){
	list< list<Int341> >::iterator prev = out; //creating a second iterator to help merge the two short inner lists
	prev--; //decrement the iterator to point to the previous list so we can merge
	out->splice(out->begin(), *prev); //add the previous short list to the current short lsit
	prev = L.erase(prev); //delete the previous list since it is now empty
	numSmall = 0;
      }
    }
    //if list is not small, set small list counter back to 0
    else{
      numSmall = 0;
    }
    //if the list is too big, separate it into two smaller lists of equal length
    if(listSize > big){
      list<Int341> temp; //empty list to be inserted at next index
      list< list<Int341> >::iterator prev = out; //create new iterator to help insert new empty list for splitting of current long list
      L.insert(out, temp); //insert an empty list at the next index 
      prev--; //increment next because insert places something before the iterator
      int halfway = (out->size() / 2)-1; //variable to store where the mid point of the list is
      list<Int341>::iterator inside = out->begin(); //iterator to go through big list and reach halfway point
      advance(inside, halfway); //move the iterator to the halfway point of the list
      out->splice(prev->begin(), *out, out->begin(), inside); 
    }
  }
}

//addFirst - inserts at the beginning of the SqList and then calls consolidate()
void SqList::addFirst(const Int341& x){
  //if the outer list is empty
  if(L.empty()){
    list<Int341> temp;
    L.push_back(temp);
  }

  L.front().push_front(x); //pushes x onto the front of the first list
  //increments "n", the number of items in the entire SqList
  m_items++;
  consolidate();
}

//addLast - inserts at the end of the SqList and then calls consolidate()
void SqList::addLast(const Int341& x){
  //if the outer list is empty
  if(L.empty()){
    list<Int341> temp;
    L.push_back(temp);
  }
  
  L.back().push_back(x); //pushes x onto the end of the last list
  //increments "n", the number of items in the entire SqList
  m_items++;
  consolidate();
}

//removeFirst() - removes an item at the beginning of the list and then calls consolidate
Int341 SqList::removeFirst(){
  //checking if the list is empty, throwing an out of range exception if it is
  if(L.empty())
    throw out_of_range("List is empty");
  //temp variable to store the first item before popping it so it can be returned
  Int341 temp = L.front().front();
  L.front().pop_front();
  //decrements "n", the number of items in the entire SqList
  m_items--;

  //if the list we removed from is now empty, delete it
  if(L.front().empty()){
    L.pop_front();
  }
  
  cout << "removerino" << endl;
  
  consolidate();
  return temp;
}

//removeLast() - removes an item at the end of the list and then calls consolidate
Int341 SqList::removeLast(){
  //checking if the list is empty, throwing an out of range exception if it is
  if(L.empty())
    throw out_of_range("List is empty"); 
  Int341 temp = L.back().back();
  L.back().pop_back();
  //decrements "n", the number of items in the entire SqList
  m_items--;

  //if the list we removed from is now empty, delete it
  if(L.back().empty())
    L.pop_back();
  consolidate();
  return temp;
}

//add(int pos, const Int341& data) - inserts an item at a given position of the list, then calls consolidate
void SqList::add(int pos, const Int341& data){
  int counter = 0; //counter variable to keep track of total number of elements passed (by looking at the size of inner lists)

  //initial check to make sure the position is not invalid
  if(pos < 0 || pos > m_items)
    throw out_of_range("Not a valid position");

  //if the list L is empty, create a new list and insert it there. We know pos is the valid number 0 because if it is less than or greater than 0, an exception will be thrown above
  if(L.empty()){
    list<Int341> temp;
    L.push_back(temp);
  }

  //if pos is equal to the number of items in the entire list, simply insert it at the very end
  if(pos == m_items){
    addLast(data);
    return;
  }

  //If the position is not an edge case, and is simply an insertion in the middle

  //iterator to go through the outside list
  list< list<Int341> >::iterator out;

  //iterator to go through the inner list
  list<Int341>::iterator in;

  //for loop to iterate through the outer lists until the correct list to insert in is found
  for(out = L.begin(); out != L.end(); out++){

    //if the position to insert at is greater than the size of the current list plus previous ones, then add the current lists size to counter and move on the next outer list
    if( (out->size()) + counter < pos){
      counter += (out->size());
    }

    //if the position to insert at is within the current outer list
    else{

      //variable to keep track of how many times inner list iterator has traversed, to know when to insert "data"
      int innerPos = 0;  

      //for loop to iterate through the inner list which we want to insert in
      for(in = out->begin(); in != out->end(); in++){

	//if statement to see if we have moved far enough forward in the inner list to now insert the value of data
	if(innerPos == (pos - counter)){ //pos - counter gives you the index of the inner list which you will insert at
	    out->insert(in, data.m_data);
	    m_items++;
	    return;
	}
	else
	  innerPos++;  //if we are not yet at the index, increment innerPos
      }
    }
  }
  consolidate();
}

//remove() - removes an item from a given position of a SqList and treturns its value, then calls consolidate()
Int341 SqList::remove(int pos){
  int counter = 0; //counter variable to keep track of total number of elements passed (by looking at the size of inner lists)
  //initial check to make sure the position is not invalid
  if(pos < 0 || pos > m_items)
    throw out_of_range("Not a valid position");
  //if the list L is empty, throw an out of range error
  if(L.empty()){
    throw out_of_range("List is empty. Can't remove");
  }
  //if pos is equal to the number of items in the entire list, simply delete the last element
  if(pos == m_items){
    return removeLast();
  }
  //if pos is the first one
  if(pos == 0){
    return removeFirst();
  }
  //If the position is not an edge case, and is simply an insertion in the middle

  list< list<Int341> >::iterator out;  //iterator to go through the outside list
  list<Int341>::iterator in;  //iterator to go through the inner list
  //for loop to iterate through the outer lists until the correct list to insert in is found
  for(out = L.begin(); out != L.end(); out++){
    //if the position to insert at is greater than the size of the current list plus previous ones, then add the current lists size to counter and move on the next outer list
    if( (out->size()) + counter < pos){
      counter += (out->size());
    }
    //if the position to insert at is within the current outer list
    else{
      int innerPos = 0;//variable to keep track of how many times inner list iterator has traversed
      //for loop to iterate through the inner list which we want to insert in
      for(in = out->begin(); in != out->end(); in++){
        //if statement to see if we have moved far enough forward in the inner list to now insert the value of data
        if(innerPos == (pos - counter)){ //pos - counter gives you the index of the inner list which you will insert at
	  Int341 temp = *in;
	  out->erase(in); 
	  m_items--;
	  consolidate();
	  return temp;
        }
        else
          innerPos++;  //if we are not yet at the index, increment innerPos
      }
    }
  }
}

//operator[] - returns a reference to the element at pos
Int341& SqList::operator[](int pos){
  int counter = 0; //counter variable to keep track of total number of elements passed (by looking at the size of inner lists)

  //initial check to make sure the position is not invalid
  if(pos < 0 || pos > m_items)
    throw out_of_range("Not a valid position");

  //if the list L is empty, create a new list and insert it there. We know pos is the valid number 0 because if it is less than or greater than 0, an exception will be thrown above
  if(L.empty()){
    throw out_of_range("Not a valid position");
  }

  //iterator to go through the outside list
  list< list<Int341> >::iterator out;
  //iterator to go through the inner list
  list<Int341>::iterator in;
  //for loop to iterate through the outer lists until the correct list to insert in is found
  for(out = L.begin(); out != L.end(); out++){
    //if the position to insert at is greater than the size of the current list plus previous ones, then add the current lists size to counter and move on the next outer list
    if( (out->size()) + counter <= pos){
      counter += (out->size());
    }
    //if the position to insert at is within the current outer list
    else{
      //variable to keep track of how many times inner list iterator has traversed, to know when to insert "data"
      int innerPos = 0;
      //for loop to iterate through the inner list which we want to insert in
      for(in = out->begin(); in != out->end(); in++){
        //if statement to see if we have moved far enough forward in the inner list to now insert the value of data
        if(innerPos == (pos - counter)){ //pos - counter gives you the index of the inner list which you will insert at
	  return *in;
	  // innerPos++; //have to increment innerPos so that it doesn't keep adding data forever since innerPos will keep equaling (pos-counter) once the correct location is found
        }
        else
          innerPos++;  //if we are not yet at the index, increment innerPos
      }
    }
  }
}

//indexOf() - Returns the index of first occurence of a value
int SqList::indexOf(const Int341& data){
  int index = 0;
  for(list< list<Int341> >::iterator out = L.begin(); out != L.end(); out++){
    for(list<Int341>::iterator in = out->begin(); in != out->end(); in++){
      if(in->m_data == data.m_data){
	return index;
      }
      index++;
    }
  }
}

//numItems() - returns the number of items in the SqList
int SqList::numItems(){
  return m_items;
}

//dump () - prints out the number of items in the SqList and for each inner list, the size of the inner list, and each item in the inner list
void SqList::dump(){
  cout << "----- SqList dump() -----" << endl;
  cout << "number of items = " << m_items << endl;
  cout << "-------------------------" << endl;
  
  //iterator to go through the outside list
  list< list<Int341> >::iterator out;
  //iterator to go through the inner list
  list<Int341>::iterator in;
  
  //counter variable to keep track of which outer list we are at
  int counter = 0;
  
  //for loop to iterate through the outer list
  for(out = L.begin(); out!=L.end(); out++){
    cout << counter << "(" << out->size() << ") : ";
    //for loop to iterate through the inner list
    for(in = out->begin(); in != out->end(); in++){
      cout << in->m_data << " ";
    }
    counter++;
    cout << endl;
  }
  cout << endl;
  cout << "-------------------------" << endl;

}

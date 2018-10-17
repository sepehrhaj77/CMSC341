// File: bst.cpp

#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
using namespace std ;

#include "ExpBST.h"

int ExpBST::m_depth;
int ExpBST::m_minHeight;
float ExpBST::m_factor;


//Default Constructor
ExpBST::ExpBST() {
  nptr = NULL ;
  //  m_depth = 0;
  //m_minHeight = 0;
  //m_factor = 0.0;
  m_numRebalance = 0;
  m_numFailedRebalance = 0;
  m_numExceedsHeight = 0;
  m_height = 0;
  m_size = 1;
}

//Constructor - we will be using this one to create the tree
ExpBST::ExpBST(int depth, int minHeight, float factor){
  nptr = NULL;
  m_depth = depth;
  m_minHeight = minHeight;
  m_factor = factor;
  m_numRebalance = 0;
  m_numFailedRebalance = 0;
  m_numExceedsHeight = 0;
  m_height = 0;
  m_size = 1;
}

//Copy Constructor
ExpBST::ExpBST(const ExpBST& other) {
  if ( other.empty() ) {
    nptr = NULL ;
  } else {
    nptr = new ExpBSTNode( *(other.nptr) ) ;
  }
}

//Destructor
ExpBST::~ExpBST() {
  //   cout << "BST destructor, this = " << this << endl ;
  delete nptr ;
}


//MyLeft - Returns the left node of the current node
ExpBST& ExpBST::myLeft() {
  return nptr->left ; 
}

//MyRight - Returns the right node of the current node
ExpBST& ExpBST::myRight() {
  return nptr->right ; 
}

//MyData - Returns the int data value at the current node
DTYPE& ExpBST::myData() {
  return nptr->data ;
}

//Empty - returns true if the tree has no nodes
bool ExpBST::empty() const{
  return nptr == NULL ;
}

//Height - returns the height of the tree
int ExpBST::height() const{
  if(nptr == NULL){//if there is nothing to call it on
    return -1;
  }
  return m_height;
}

//Size - returns the size of the tree
int ExpBST::size() const{
  if(nptr == NULL){ //if the tree is empty, return 0 for the size
    return 0;
  }
  return m_size;
}

//Find - Reports whether the value in the parameter is in the tree
bool ExpBST::find(DTYPE key) {

  if ( empty() ) return NULL ;

  if (myData() == key) return &myData() ;

  if (myData() < key) return myRight().find(key) ;

  return  myLeft().find(key) ;
}

//InOrder - Returns the elements of the tree in order from least to greatest
void ExpBST::inorder() {
  
  if ( empty() ) return ;

  cout << "(" ;
  myLeft().inorder() ;

  cout << myData() << ":" << height() << ":" << size();

  myRight().inorder() ;
  cout << ")" ;

  return  ;
}



void ExpBST::insert(DTYPE key) {
  if ( empty() ) { //if the tree is empty, create a new node as the root and set nptr = to it

    nptr = new ExpBSTNode(key) ;
    updateHeight();
    updateSize();

  } else if(myData() == key){ //if the key is already in the tree, do nothing.

    return;

  } else if (myData() < key) {  //if the key is bigger than the current node, go to the right subtree
    myRight().insert(key) ;
    m_height = updateHeight(); //update the height after you have inserted the node
    m_size = updateSize();
    if(m_height > (2 * log2(m_size))){
      rebalance();
      m_numRebalance++;
    } 
  } 

  else { //if the key is less than the current node, go to the left subtree
    myLeft().insert(key) ;
    m_height = updateHeight(); //update the height after you have inserted the node
    m_size = updateSize();
    if(m_height > (2 * log2(m_size))){
      rebalance();
      m_numRebalance++;
    }
  }
}



ExpBSTNode *ExpBST::removeMaxNode() {


  if ( empty() ) return NULL ;
  
  if (! myRight().empty() ) {
    return myRight().removeMaxNode() ;
  }

  ExpBSTNode *answer = nptr ;
  nptr = myLeft().nptr ;  // don't do deep BST copy!

  // must unlink from tree o.w.
  // destructor will kill subtrees
  answer->unlink() ;

  return answer ;
   
}



bool ExpBST::remove(DTYPE key) {
  bool answer;

  if ( empty() ) return false ;

  if (myData() < key) {
    answer =  myRight().remove(key) ;
    m_size = updateSize();
    m_height = updateHeight();
    return answer;
  }

  if (myData() > key) {
    answer = myLeft().remove(key) ;
    m_size = updateSize();
    m_height = updateHeight();
    return answer;
  }

  ExpBSTNode *temp ;

  // otherwise, nptr->data == x
  if ( myLeft().empty() ) {

    temp = nptr ;
    nptr = myRight().nptr ;
    m_height = updateHeight(); //update the height after the node has been removed and values correctly swapped

  } else if ( myRight().empty() ) {

    temp = nptr ;
    nptr = myLeft().nptr ; 
    m_height = updateHeight(); //update the height after the node has been removed and values correctly swapped

  } else {

    ExpBSTNode *pred = myLeft().removeMaxNode() ;
    assert( pred != NULL ) ;

    temp = nptr ;
    nptr = pred ;
    pred->left.nptr = temp->left.nptr ;
    pred->right.nptr = temp->right.nptr ;
    m_height = updateHeight(); //update the height after the node has been removed and values correctly swapped

  }
  m_size = updateSize();
  // must unlink from tree o.w.
  // destructor will kill subtrees
  temp->unlink() ;
  delete temp ;
  return true;


}


const ExpBST& ExpBST::operator=(const ExpBST& rhs) {

  if (this == &rhs) return *this ;
   
  delete nptr ;

  if ( rhs.empty() ) {
    nptr = NULL ;
  } else {
    nptr = new ExpBSTNode( *(rhs.nptr) ) ;
  }

  return *this ;
}


//Node default constructor - do nothing
ExpBSTNode::ExpBSTNode() {
  
}

//Node constructor - do nothing
ExpBSTNode::ExpBSTNode(DTYPE x) 
  : data(x) {
  // do nothing
}


//Node destructor - do nothing
ExpBSTNode::~ExpBSTNode() {

  // cout << "BSTNode destructor, this = " << this << endl ;

  // do nothing else

}


void ExpBSTNode::unlink() {
  left.nptr = NULL ;
  right.nptr = NULL ;
}


//UpdateHeight - Updates the height. Called everytime a node is inserted or removed
int ExpBST::updateHeight(){
  if(nptr == NULL){//if there is no node, the height is -1
    return -1;
  }
  else{
    return max(myLeft().height(), myRight().height() ) + 1;
  }
}

//UpdateSize - Updates the size. Called everytmie a node is inserted or removed
int ExpBST::updateSize(){
  if(nptr == NULL){
    return 0;
  }
  else{
    if (!myRight().empty() and !myLeft().empty()){
      return myLeft().size() + myRight().size() + 1;
    }
    else if (!myRight().empty()){
      return myRight().size() + 1;
    }
    else if (!myLeft().empty()){
      return myLeft().size() + 1;
    }
    else{//in case it has no children, it has a size of one
      return 1;
    }
  }
}

//Locate - Returns whether there is a node in a position of the ExpBST and stores the key in the reference parameter
bool ExpBST::locate(const char *position, int& key) {  
  string str = position;
  
  if(nptr == NULL){ //if there is no node at the current location we have gone to, return false
    return false;
  }
  
  if(str == ""){ //if there are no letters remaining, return the current node's value
    key = myData(); 
    return true;
  }
  else{ //otherwise, we have to keep traversing down the tree

    if(str.at(0) == 'L'){ //if the current first letter is L, go to the left tree
      str.erase(0,1); //remove the first letter of the string
      return myLeft().locate(str.c_str(), key); //call the function again with the shortened string
    }

    else if(str.at(0) == 'R'){ //if the current first letter is R, go to right tree
      str.erase(0,1); //remove the first letter of the string
      return myRight().locate(str.c_str(), key); //call the function again with the shortened string
    }

  }

}

//Rebalance - rebalances the tree if it is not fitting under the condition of the height of a subtree being less than or equal to log(n) with n nodes.
void ExpBST::rebalance(){
  cout << "rebalancing" << endl;
  ExpBSTNode** array;
  int index = 0;
  int depth = 0;
  int start = 0;

  int maxArraySize = pow(2,m_depth+1) - 1; //the max size of the array is calculated based on the max depth we want to go down
  array = new ExpBSTNode*[maxArraySize]; //create an array to store the nodes

  truncInorder(array, index, depth); //stores the values up to the max depth in the array variable

  for(int i=1; i<index-1; i+=2)
    array[i]->unlink();

  nptr = treeBuilder(array, nptr, index); //rebuilds the tree accordingly. Index is passed because it will be one greater than the index of the last element inserted

  if(m_height > (2 * log2(m_size))){
    m_numExceedsHeight++;
  }

  delete[] array;  //deallocate the array we made to store the nodes
}

//TreeBuilder - Rebuilds the tree based on the optimal value from the stuff stored in the array created by truncInorder
ExpBSTNode* ExpBST::treeBuilder(ExpBSTNode** arr, ExpBSTNode* root, int size){
  // Constucts BST from array of nodes
  return treeBuilderHelper(arr, 0, size-1);
}


//TreeBuilder - Builds an optimal tree rearranging the nodes
ExpBSTNode* ExpBST::treeBuilderHelper(ExpBSTNode** arr, int start, int end){
  // base case
  if(start > end){
    return NULL;
  }

  // Get the middle element and make it the root 
  int mid = (start + end)/2;
  ExpBSTNode *root = arr[mid];

  myLeft().nptr = treeBuilderHelper(arr, start, mid-1);
  myRight().nptr = treeBuilderHelper(arr, mid+1, end);

  return root;
}

//Truncated inorder walk - does an inorder walk and stores the values of the nodes in an array
void ExpBST::truncInorder(ExpBSTNode** arr, int &index, int &depth){
  //If we have exceeded the max depth, don't do anything. Just return the array back.
  if(depth > m_depth){
    return;
  }

  if ( empty() ){ //if empty, increment the index at which we are inserting and then return the array in which we are storing the nodes
    index++;
    return;
  }

  //if a node exists at the current location, and has no children, there is no need to go any further down
  if(myLeft().empty() and myRight().empty()){
    arr[index] = nptr;
    index++;
    return;
  }

  depth++;
  myLeft().truncInorder(arr, index, depth) ;
  depth--;

  arr[index] = nptr;
  index++;

  depth++;
  myRight().truncInorder(arr, index, depth) ;
  depth--;

  return;
}


//resetStats - resets the stats of the variables in this function
void ExpBST::resetStats(){
  m_numRebalance = 0;
  m_numFailedRebalance = 0;
  m_numExceedsHeight = 0;

}

//GetNumRebalance - returns number of rebalances
int ExpBST::getNumRebalance() const {
  return m_numRebalance;
}

//GetFailedRebalance - returns number of failed rebalances
int ExpBST::getFailedRebalance() const{
  return m_numFailedRebalance;
}

//GetExceedsHeight - returns number of times it exceeded height
int ExpBST::getExceedsHeight() const{
  return m_numExceedsHeight;
}

//GetMaxRebalanceDepth - returns max rebalance depth
int ExpBST::getMaxRebalanceDepth() const{
  return m_depth;
}

//GetMinRebalanceDepth - returns minimum rebalance depth
int ExpBST::getMinRebalanceHeight() const{
  return m_minHeight;
}

//GetRebalanceFactor - returns rebalance factor
float ExpBST::getRebalanceFactor() const {
  return m_factor;
}




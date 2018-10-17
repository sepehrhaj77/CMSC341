//
//Author: Sepehr Hajbarat

#ifndef _EXPBST_H_
#define _EXPBST_H_

#define DTYPE int
#include <iostream>
#include <stdlib.h>


class ExpBSTNode ;

class ExpBST{
  friend class ExpBSTNode ;

 public:
  //A default constructor with the signature. Not going to be used but default constructor is good to have
  ExpBST() ;

  //A constructor with the signature
  ExpBST(int depth, int minHeight, float factor) ;

  //Copy Constructor
  ExpBST(const ExpBST& other) ;

  //Destructor
  ~ExpBST() ;

  //The following functions report on attributes of the ExpBST tree
  bool empty() const  ;    // tree has no nodes
  int  height() const ;    // height of tree
  int  size() const ;      // number of nodes in tree

  //Reports whether the given key is stored in the tree
  bool find(int key) ;

  //Adds an item to ExpBST
  void insert (int key) ;

  //Finds and removes an item with the given key value
  bool remove(int key) ;

  //Performs in order walk of ExpBST at each node
  void inorder() ; 

  //Overloaded assignment operator
  const ExpBST& operator=(const ExpBST& rhs) ;

  //These three return the values passed to the constructor above
  int getMaxRebalanceDepth() const  ; 
  int getMinRebalanceHeight() const ;
  float getRebalanceFactor() const ;

  //The following four functions report statistics of the ExpBST tree related to rebalancing
  int getNumRebalance() const ;
  int getFailedRebalance() const ;
  int getExceedsHeight() const ;
  void resetStats() ;

  //returns whether there is a node in a position of the ExpBST and stores the key in the reference parameter
  bool locate(const char *position, int& key) ;
  

 private:
  int m_height;
  int m_size;
  
  static int m_depth;
  static int m_minHeight;
  static float m_factor;
  
  int m_numRebalance;
  int m_numFailedRebalance;
  int m_numExceedsHeight;

  ExpBSTNode *nptr ;

  ExpBST& myLeft() ;
  ExpBST& myRight() ;
  DTYPE& myData() ;
  int updateHeight();
  int updateSize();

  //Rebalances a subtree of the ExpBST
  void rebalance();

  //Performs an inorder walk up to a max depth and stores the nodes in an array
  void truncInorder(ExpBSTNode** arr, int &index, int &depth);

  //Builds the new tree after rebalancing
  ExpBSTNode* treeBuilderHelper(ExpBSTNode** arr, int start, int end);
  ExpBSTNode* treeBuilder(ExpBSTNode** arr, ExpBSTNode* root, int size);
  ExpBSTNode *removeMaxNode() ;  
};

class ExpBSTNode {
  friend class ExpBST ;

 public:
  ExpBSTNode() ;
  ExpBSTNode(DTYPE x) ;

  ~ExpBSTNode() ;

  void unlink() ;

 private:
  DTYPE data ;
  ExpBST left, right ;
} ;


#endif

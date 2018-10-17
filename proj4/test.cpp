#include "Heap.h"
#include <iostream>

using namespace std;

bool lt(const int& x, const int& y) {
  return x < y ;
}

bool gt(const int& x, const int& y) {
  return x > y ;
}

int main(){

  Heap<int> h(11, lt);
  h.insert(5);
  h.insert(7);
  h.insert(13);
  h.insert(9);
  h.insert(17);
  h.insert(19);
  h.insert(12);
  h.insert(17);
  h.insert(21);
  h.insert(23);

  h.deleteFirst();
  h.deleteFirst();

  for(int i = 1; i<11; i++)
    cout << h.getValue(i) << endl;

  return 0;
}

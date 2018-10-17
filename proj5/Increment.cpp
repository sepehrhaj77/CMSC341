#include <iostream>
using namespace std ;

class Increment {
public:
   Increment(int n=1) {
      m_addThis = n ;
   }

   int operator() (int x) {
      return x + m_addThis ;
   }

   int m_addThis ;
} ;

int main() {
   Increment add1 ;

   cout << add1(5) << endl ;    // prints 6
   cout << add1(8) << endl ;    // prints 9

   Increment add7(7) ;

   cout << add7(5) << endl ;    // prints 12 
   cout << add7(8) << endl ;    // prints 15 

   cout << add1(5) << endl ;    // still prints 6

}

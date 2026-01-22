#include <iostream>

#include "container.h"
#include "vector.h"
#include "stack.h"

using namespace std;

int main()
{
    // Iteration sur les elements de Vector
    Vector<int> vect1(100, 0);

    for(Vector<int>::const_iterator it = vect1.cbegin() ; it != vect1.cend() ; it++) {
        cout << *it << endl;
    }

    // Iteration sur les elements de Stack - Adaptateur d'objets
    AO::Stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);

    for(AO::Stack<int>::iterator it = stk.begin() ; it != stk.end() ; it++) {
        cout << *it << endl;
    }

    // Iteration sur les elements de Stack - Adaptateur de classes
    AC::Stack<int> stkc;
    stkc.push(4);
    stkc.push(5);
    stkc.push(6);

    for(AC::Stack<int>::iterator it = stkc.begin() ; it != stkc.end() ; it++) {
        cout << *it << endl;
    }


    return 0;
}
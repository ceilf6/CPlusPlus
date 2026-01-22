#include <iostream>

#include "container.h"
#include "vector.h"
#include "stack.h"

class A {
private:
    int a;
    int b;
public:
    A() : a(1), b(2) { }
};

int main()
{
    AO::Stack<int> stk;
    stk.push(1);
    stk.push(2);

    AO::Stack<A> stk2;
    stk2.push(A());

    AC::Stack<int> stkc;
    stkc.push(1);
    stkc.push(2);

    AC::Stack<A> stkc2;
    stkc2.push(A());

    return 0;
}
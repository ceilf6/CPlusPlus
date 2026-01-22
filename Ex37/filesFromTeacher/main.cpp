#include <iostream>

#include "container.h"
#include "vector.h"
#include "stack.h"

using namespace std;

int main()
{
    // 迭代 Vector 的元素
    Vector<int> vect1(100, 0);

    for(Vector<int>::const_iterator it = vect1.cbegin() ; it != vect1.cend() ; it++) {
        cout << *it << endl;
    }

    // 迭代 Stack 的元素 - 对象适配器
    AO::Stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);

    for(AO::Stack<int>::iterator it = stk.begin() ; it != stk.end() ; it++) {
        cout << *it << endl;
    }

    // 迭代 Stack 的元素 - 类适配器
    AC::Stack<int> stkc;
    stkc.push(4);
    stkc.push(5);
    stkc.push(6);

    for(AC::Stack<int>::iterator it = stkc.begin() ; it != stkc.end() ; it++) {
        cout << *it << endl;
    }


    return 0;
}
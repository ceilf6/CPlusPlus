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

    // 测试 countGreaterThan 方法
    cout << "\n=== 测试 countGreaterThan 方法 ===" << endl;

    // 测试 Vector
    Vector<int> vect2(10, 5);  // 创建包含10个值为5的元素
    vect2.push_back(10);
    vect2.push_back(15);
    vect2.push_back(3);
    vect2.push_back(8);

    cout << "Vector中大于7的元素个数: " << vect2.countGreaterThan(7) << endl;  // 应该是3 (10, 15, 8)
    cout << "Vector中大于5的元素个数: " << vect2.countGreaterThan(5) << endl;  // 应该是3 (10, 15, 8)
    cout << "Vector中大于15的元素个数: " << vect2.countGreaterThan(15) << endl; // 应该是0

    // 测试 AO::Stack
    AO::Stack<int> stk2;
    stk2.push(5);
    stk2.push(10);
    stk2.push(3);
    stk2.push(15);
    stk2.push(8);

    cout << "AO::Stack中大于7的元素个数: " << stk2.countGreaterThan(7) << endl;  // 应该是3 (10, 15, 8)
    cout << "AO::Stack中大于5的元素个数: " << stk2.countGreaterThan(5) << endl;  // 应该是3 (10, 15, 8)

    // 测试 AC::Stack
    AC::Stack<int> stkc2;
    stkc2.push(5);
    stkc2.push(10);
    stkc2.push(3);
    stkc2.push(15);
    stkc2.push(8);

    cout << "AC::Stack中大于7的元素个数: " << stkc2.countGreaterThan(7) << endl;  // 应该是3 (10, 15, 8)
    cout << "AC::Stack中大于5的元素个数: " << stkc2.countGreaterThan(5) << endl;  // 应该是3 (10, 15, 8)

    return 0;
}
#include <iostream>
#include "fraction.hpp"

using namespace std;
using namespace MATH;

Fraction *myFunction()
{
    Fraction fx(7, 8);
    Fraction *pfy = new Fraction(2, 3);
    return pfy;
}

// 其实析构的本质就是垃圾回收机制（在JS中体现为闭包延长生命周期，实现防抖节流等等）

int main()
{
    Fraction f1(3, 4);
    Fraction f2(1, 6);
    Fraction *pf3 = new Fraction(1, 2);

    cout << "\n---- 进入一个作用域 ----\n";
    Fraction *pf6;
    {
        Fraction f4(3, 8);
        Fraction f5(4, 6);
        pf6 = new Fraction(1, 3);
    }
    cout << "---- 离开作用域 ----\n";

    // 函数作用域
    cout << "\n---- 进入函数 ----\n";
    Fraction *pf7 = myFunction();
    cout << "---- 离开函数 ----\n";

    cout << "\n---- 手动释放内存 ----\n";
    delete pf6;
    delete pf7;
    delete pf3;

    cout << "\n---- 测试加法 ----\n";
    cout << f1.getNumerateur() << '/' << f1.getDenominateur() << " + " << f2.getNumerateur() << '/' << f2.getDenominateur() << endl;
    Fraction r = f1.somme(f2);
    r.afficher();
    cout << endl;

    cout << "\n---- 程序结束 ----\n";

    return 0;
}

/*
结果：

+ 构造 Fraction 对象: 0x16b5e2fb4 => 3/4
+ 构造 Fraction 对象: 0x16b5e2fac => 1/6
+ 构造 Fraction 对象: 0x120606140 => 1/2

---- 进入一个作用域 ----
+ 构造 Fraction 对象: 0x16b5e2f80 => 3/8
+ 构造 Fraction 对象: 0x16b5e2f78 => 4/6
+ 构造 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x16b5e2f78 => 2/3（p5化简后的结果）
- 析构 Fraction 对象: 0x16b5e2f80 => 3/8
---- 离开作用域 ----

这里可以发现栈内存的对象被析构了，但是用 new 创在堆内存上的 p6 并没有被清除

---- 进入函数 ----
+ 构造 Fraction 对象: 0x16b5e2eb8 => 7/8
+ 构造 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x16b5e2eb8 => 7/8
---- 离开函数 ----

---- 手动释放内存 ----
- 析构 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x120606140 => 1/2

---- 测试加法 ----
3/4 + 1/6
+ 构造 Fraction 对象: 0x16b5e2f68 => 22/24
11/12

---- 程序结束 ----
- 析构 Fraction 对象: 0x16b5e2f68 => 11/12
- 析构 Fraction 对象: 0x16b5e2fac => 1/6
- 析构 Fraction 对象: 0x16b5e2fb4 => 3/4
*/
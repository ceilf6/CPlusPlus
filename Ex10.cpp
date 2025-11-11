#include <iostream>

int main()
{
    /*
        * : 1. 声明指针;2. 解引用取值
        1. int* ptr; // 表示声明了一个指向整型类型的指针
        2. int value = *ptr; // 解指针拿到了 ptr 指针指向的值并赋值给另一个变量
    */
    /*
        & : 1. 声明引用;2. 取地址
        1. int& ref = var; // 声明了 ref 指向的和 var 同一个内存地址
        2. int* ptr = &ref; // ptr 指向的是变量 ref 的内存地址
    */

    double *pt0 = 0;              // 0 可以是 int,double,float,long,char,空指针：这里用到的就是 double 类型
    double *pt1;                  // = 4096; // 变量和指针的类型必须相同：4096是 int 类型
    double *pt2 = (double *)4096; // 将指针进行了显式转换。但这是危险的，如果解引用就会导致undefined行为
    void *pt3 = pt1;              // 任意对象类型的指针，都可以隐式转换给 void*
    // pt1 = pt3;                 // 但是 void* 类型赋给其他的必须进行显式转换：如下面一行
    pt1 = (double *)pt3;

    // const 类型 *ptr ：指针指向的值不能变
    // 类型 const *ptr ：和上面一样都是值不能变

    // 类型 * const ptr ：类型紧接* const - ptr指针为常量不能变

    double d1 = 36;
    const double d2 = 36;
    double *pt4 = &d1;
    const double *pt5 = &d1;
    std::cout << "--d1: " << d1 << std::endl;
    *pt4 = 2.1; // 通过 d1 的指针 pt4 来修改 d1 的值
    std::cout << "--d1: " << d1 << std::endl;
    // *pt5 = 2.1; // 上面加了 const 导致这个指针无法改变
    // pt4 = &d2; // 不能将值赋给指针变量
    pt5 = &d2;
    double *const pt6 = &d1;
    // pt6 = &d1; // 上面定义了不可变指针
    *pt6 = 2.78;
    // double *const pt6b = &d2; // 注意 pt6b 是指针不可变，但是 d2 是值不可变
    const double *const pt6b = &d2; // 除非对值也设为常量（只能更严格指向更宽松的）
    const double *const pt7 = &d1;
    // pt7 = &d1; // pt7的值和指针都不可变
    // *pt7 = 2.78;
    double const *pt8 = &d1; // 注意不是类型紧接，所以是值不能变
    pt8 = &d2;               // 指向 const double 的可以指向 const 的，也能指向更宽松的不 const 的
    pt8 = &d1;
    // *pt8 = 3.14;          // 值不能变

    return 0;
}
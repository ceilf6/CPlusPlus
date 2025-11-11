#include <iostream>

// 利用地址或者引用、通过中间变量或者解构等方法进行交换
// 如果不用地址或引用而是直接传(int a,int b)会导致传入的只是a和b的值拷贝，无法改变内存层面的值
// 而像python、JS、Java这些语言不需要指针也能成功改变的原因是这些语言封了一层使得传入的其实是一个引用对象，那么使用者就不需要考虑内存的细节了
// 但正是因为 C++ 的颗粒度小所以在性能上非常有优势，且会避免语言开发者出于好意的封装导致的使用者在调用API时被无意篡改了数据

void inverseByPtr(int *a, int *b)
{
    std::cout << "指针传递前a,b值: " << *a << ',' << *b << std::endl;
    int temp = *a;
    *a = *b;
    *b = temp;
    std::cout << "指针传递后a,b值: " << *a << ',' << *b << std::endl;
}
void inverseByRef(int &a, int &b)
{
    std::cout << "引用传递前a,b值: " << a << ',' << b << std::endl;
    // int temp = a;
    // a = b;
    // b = temp;
    std::tie(a, b) = std::make_tuple(b, a); // 通过元组解构的方式
    std::cout << "引用传递后a,b值: " << a << ',' << b << std::endl;
}
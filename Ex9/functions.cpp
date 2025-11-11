/*

这是我首推的功能函数单独文件写法，为了展示 inline 就先注释掉了

#include <iostream>

void func(int A)
{
    std::cout << "成功调用函数1" << A << std::endl;
}

void func(int A2, std::string B2)
{
    std::cout << "成功调用函数2" << A2 << ' ' << B2 << std::endl;
}

void func(int A3, std::string B3, float C3)
{
    std::cout << "成功调用函数3" << A3 << ' ' << B3 << ' ' << C3 << std::endl;
}

int func(double A)
{
    std::cout << "成功调用形参为double类型的参数" << A << std::endl;
}
*/
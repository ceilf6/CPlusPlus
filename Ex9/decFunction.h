// #ifndef DECFUNCTION_H
// #define DECFUNCTION_H

// #include <string>
// // #include <iostream>

// void func(int a);
// void func(int a2, std::string b2);
// void func(int a3, std::string b3, float c3);
// // int func(int a);
// // float func(int a);
// // 报错: 无法重载仅按返回类型区分的函数，因为返回类型不参与重载
// int func(double a);

// #endif

#ifndef DECFUNCTION_H
#define DECFUNCTION_H

#include <string>
#include <iostream>

inline void func(int a) // 注意inline必须要将函数体也一起写出来不能只是声明（因为到时候是直接粘贴过去的）
{
    std::cout << "成功调用函数1" << a << std::endl;
}

inline void func(int a2, std::string b2)
{
    std::cout << "成功调用函数2" << a2 << ' ' << b2 << std::endl;
}

inline void func(int a3, std::string b3, float c3)
{
    std::cout << "成功调用函数3" << a3 << ' ' << b3 << ' ' << c3 << std::endl;
}
// int func(int a);
// float func(int a);
// 报错: 无法重载仅按返回类型区分的函数，因为返回类型不参与重载

inline int func(double a)
{
    std::cout << "成功调用形参为double类型的参数" << a << std::endl;
}

#endif
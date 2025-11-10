/*
reecrire re-ecrire 重新写
ne faisant appel. qu’aux nouvelles possibilites d’entrees-sorties du C++ : 只使用 C++ 的新输入输出功能
使用 const 定义常量而不是 #define
*/

#include <iostream>

constexpr double PI = 3.14159;
// constexpr指编译期已知，可以直接在编译期使用，而不用像const得在运行时去内存里面拿，比const性能更优

void calculateCircle()
{
    std::cout << "请输入圆的半径: ";
    double r;

    if (!(std::cin >> r) || r < 0)
    {
        std::cout << "输入错误！半径必须为非负数。" << std::endl;
        return;
    }

    double circumference = 2 * PI * r;
    double area = PI * r * r;

    std::cout << "圆的周长: " << circumference << '\n';
    std::cout << "圆的面积: " << area << '\n';
}

int main()
{
    calculateCircle();
    return 0;
}
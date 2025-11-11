#include "decFunction.h"
#include "usePlace2.h"

int main()
{
    func(1);
    func(1, "2");
    func(1, "2", 3.0);
    func(1.0000000000000000000000); // 精准匹配优先级大于提升整型的优先级

    std::cout << '\n'
              << "尝试调用第二个使用相同头文件函数体的函数" << std::endl
              << '\n';

    test();

    return 0;
}
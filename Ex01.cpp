// 仓库地址：https://github.com/ceilf6/CPlusPlus

#include <iostream> // 导入输入输出数据流
#include <string>

// #include<bits/stdc++.h>
// 上面两行还可以用万能头进行替换，优点是不需要记忆各个功能需要的库的名称，但是缺点有不是C++的标准头文件、编译速度慢

using namespace std; // 使用std的命名空间（不使用也可以，就是下面得用std::cout、std::cin，比较麻烦
void bonjour()
{
    cout << "输入您的名字";             // 输入
    string name;                        // 定义变量类型
    cin >> name;                        // 输入
    cout << "bonjour " << name << '\n'; // 格式化输出
}

int main()
{ // 主函数调用上面定义的功能函数实现模块化区分、代码的松耦合
    bonjour();
    return 0;
}
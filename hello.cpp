#include<iostream>
#include<string>
using namespace std;
void bonjour(){
    cout<<"输入您的名字"; // 输入
    string name; // 定义变量类型
    cin>>name; // 输入
    cout<<"bonjour "<<name<<'\n'; // 格式化输出
}

int main(){ // 主函数调用上面定义的功能函数实现模块化区分、代码的松耦合
    bonjour();
    return 0;
}
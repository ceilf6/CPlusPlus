#include "decFunction.h"
// 只需要导入包含声明的头文件即可，至于实现部分到时候编译器自己会去找（但是别忘记编译实现的function文件）

int main()
{
    French::sayhi();
    English::sayhi();
    China::sayhi();
    return 0;
}
#include "decFunction.h"
#include "usePlace2.h"

int test()
{
    func(12);
    func(12, "22");
    func(12, "22", 23.0);
    func(12.0000000000000000000000); // 精准匹配优先级大于提升整型的优先级
    return 0;
}

/*
如果没有在 dec头文件 中使用inline会发现报错:
1 warning generated.
duplicate symbol '_${函数名}' in:
    多个文件路径
ld: 1 duplicate symbol for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
*/
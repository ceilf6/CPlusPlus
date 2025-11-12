#include "fractionPatch.hpp"

namespace MATH
{
    Fraction operator+(const Fraction &f1, const Fraction &f2)
    {
        // 利用已有的 somme 方法
        return f1.somme(f2);

        // 或者直接实现：
        // return Fraction(
        //     f1.getNumerateur() * f2.getDenominateur() +
        //     f1.getDenominateur() * f2.getNumerateur(),
        //     f1.getDenominateur() * f2.getDenominateur()
        // );
    }

    Fraction operator+(const Fraction &f, int n)
    {
        // int n 可以看作 n/1
        return Fraction(
            f.getNumerateur() + n * f.getDenominateur(),
            f.getDenominateur());
    }

    Fraction operator+(int n, const Fraction &f)
    {
        // 加法满足交换律，直接调用上面的函数
        return f + n;
    }

    // 前缀版本：先递增，再返回
    Fraction &operator++(Fraction &f)
    {
        // 分子加上分母，相当于 +1
        f.setFraction(
            f.getNumerateur() + f.getDenominateur(),
            f.getDenominateur());
        return f;
    }

    // 后缀版本：先返回旧值，再递增
    Fraction operator++(Fraction &f, int)
    {
        // 保存当前值
        Fraction temp(f);

        // 递增当前对象
        ++f; // 调用前缀版本

        // 返回旧值
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const Fraction &f)
    {
        os << f.getNumerateur() << "/" << f.getDenominateur();
        return os; // 返回流引用，支持链式调用如 cout << f1 << f2
    }
}

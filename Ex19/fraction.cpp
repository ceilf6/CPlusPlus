#include "fraction.hpp"

// C++的this 和 py的self 更像，是指向当前对象的指针、内存地址
// （只不过 py的self 更加显式）（和 JS的this 差远，JS的this的四条规则更加动态）

namespace MATH // namespace 不是全局生效所以如果空间分散在多处的话得多次 namespace
{
    // 类也是一种作用域，像 namespace 一样需要 :: 来访问
    // 这样就告诉了编译器 这个函数是属于类的
    Fraction::Fraction(int n, int d) : numerateur_(n), denominateur_(d)
    // 类的成员名(参数) ：将参数赋值给类的成员
    {
        std::cout << "+ 构造 Fraction 对象: " << this << " => "
                  << numerateur_ << "/" << denominateur_ << std::endl;
        simplification();
    }
    // 拷贝构造
    Fraction::Fraction(const Fraction &f)
        : numerateur_(f.numerateur_), denominateur_(f.denominateur_)
    {
        std::cout << "+ 拷贝构造 Fraction: " << this << " <= " << &f << std::endl;
    }

    // ~加类名：析构函数，当对象离开作用域时或者 delete 时自动调用
    // 析构函数用于清理资源，不释放对象本体内存，delete才是释放对象并且顺便调用析构
    Fraction::~Fraction()
    {
        // Fraction 类本身没有 new 内存，所以不需要操作，这里只是用作展示
        std::cout << "- 析构 Fraction 对象: " << this << " => "
                  << numerateur_ << "/" << denominateur_ << std::endl;
    }

    // setter
    void Fraction::setFraction(int n, int d)
    {
        numerateur_ = n;
        denominateur_ = d;
        simplification();
    }

    // 简化函数
    void Fraction::simplification()
    {
        // 特值处理
        if (denominateur_ == 0)
        {
            std::cout << "分母不能为0，重设为1\n";
            denominateur_ = 1;
            return;
        }

        if (numerateur_ == 0)
        {
            denominateur_ = 1;
            return;
        }

        int a = (numerateur_ > 0) ? numerateur_ : -numerateur_;
        int b = (denominateur_ > 0) ? denominateur_ : -denominateur_;

        /*
        // 通过欧几里得算法找最大公约数
        while (a != b)
        {
            if (a > b)
                a -= b;
            else
                b -= a;
        }
        */
        // 辗转相减更快
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }

        numerateur_ /= a;
        denominateur_ /= a;

        if (denominateur_ < 0)
        {
            denominateur_ = -denominateur_;
            numerateur_ = -numerateur_;
        }
    }

    // 加法
    Fraction Fraction::somme(const Fraction &f) const
    {
        return Fraction(
            numerateur_ * f.denominateur_ + denominateur_ * f.numerateur_,
            denominateur_ * f.denominateur_);
        // 这里不需要简化，因为 Fraction 构造函数内部最后会调用
    }

    // 展示
    void Fraction::afficher() const
    {
        std::cout << numerateur_ << "/" << denominateur_;
    }
}
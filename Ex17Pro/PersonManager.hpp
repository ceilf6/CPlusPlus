#ifndef PERSONMANAGER_HPP
#define PERSONMANAGER_HPP

#include "Person.hpp"
#include <vector>

// 多个体数组管理

class PersonManager
{
private:
    std::vector<Person> persons_;

public:
    // 如果插入已有对象用 push_back ；直接传参数用 emplace_back
    void add(const Person &p)
    {
        persons_.push_back(p); // vector 用 push_back 动态管理数组
    }

    template <typename... Args>  // 可变参数模版，表示可以接受任意数量、任意类型的参数
    void emplace(Args &&...args) // &&是万能引用，... 和JS一样都用于展开
    {
        persons_.emplace_back(std::forward<Args>(args)...);
        /*
        emplace_back 是vector更高效的插入方式，
        直接在容器内部原地构造对象，而不是先构造一个对象再移动进去
        */
    }

    void clear()
    {
        persons_.clear();
    }

    void print() const
    {
        if (!persons_.size())
        {
            std::cout << "== Null == NoBody ==" << std::endl;
            return;
        }
        for (const auto &p : persons_)
        {
            std::cout << p << std::endl;
        }
    }
};

#endif
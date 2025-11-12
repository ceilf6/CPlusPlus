#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

// 个体管理

class Person
{
private:
    std::string name_; // 变量名后加 _ 用于表示这是类的成员变量（防止重名）
    unsigned int age_;

public:
    Person(std::string name = "", unsigned int age = 0)
        : name_(std::move(name)), age_(age) {}

    // 由于本代码中的成员属性是私有的，而外部需要打印，就像外暴露 getter 函数
    const std::string &name() const { return name_; } // 通过 const 确保安全性
    unsigned int age() const { return age_; }

    void reset()
    {
        name_.clear(); // string 直接 clear 即可
        age_ = 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &p)
    // friend 表示该函数是类的朋友就能直接访问类的私有成员了
    {
        return os << p.name_ << " (" << p.age_ << ")";
        // 利用重载输出运算直接返回数据流，调用该函数的时候直接接到 std::cout 上即可
    }
};

#endif
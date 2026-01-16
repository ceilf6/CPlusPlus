#ifndef AGENDA_H
#define AGENDA_H

#include <vector>
#include <iostream>
#include "../Ex28/evenement.h"
// cd /Users/a86198/Desktop/cpp/Ex29 && g++ -std=c++17 main.cpp agenda.cpp ../Ex28/timing.cpp ../Ex28/evenement.cpp -o main && ./main

namespace TIME
{

    class Agenda
    {
    private:
        std::vector<Evt1j *> evenements; // 异构存储：基类指针
        /*
        1. 异构存储
            通过 基类指针 + virtual 实现对不同派生类型的统一处理
            遍历时每个指针调用正确的虚函数
        2. 注意存的是 指针Evt1j* 而不是对象
            1. 如果存的是对象在例如 push_back 时会发生对象切片
                对象切片：当派生类对象如 Evt1jDur 被复制到基类容器时，只有基类部分被保留，派生类的额外成员会被切掉
            2. 实现多态性：C++的运行时多态只能通过指针或引用实现

        对象切片例子：
        class A {
        public:
            int a;
        };

        class B : public A {
        public:
            int b;
        };

        B b;
        A a = b;   // 对象切片发生在这里

        b (B对象):
        +---------+
        |   a     |  ← A 部分
        +---------+
        |   b     |  ← B 特有
        +---------+

        a (A对象):
        +---------+
        |   a     |  ← 只复制了 A 部分
        +---------+

        但是如果用指针或引用的话不会切片，因为根本不需要动，指向的都是同一个
        */

        Agenda(const Agenda &) = delete;
        // 禁止复制（考点！）
        /*
        Agenda只保存裸指针，拷贝会导致多个 Agenda 指向同一个事件，所有权不清晰、容易出错
        */

        Agenda &operator=(const Agenda &) = delete;

    public:
        Agenda() = default;
        ~Agenda() = default; // Agenda 不拥有事件，不负责 delete

        // 添加事件（不复制对象）
        Agenda &operator<<(Evt1j &e);

        // 显示所有事件
        void afficher(std::ostream &f = std::cout) const;
    };

} // namespace TIME

#endif
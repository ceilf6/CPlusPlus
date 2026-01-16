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

        */

        // 禁止复制（考点！）
        Agenda(const Agenda &) = delete;
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
#include "agenda.h"

using namespace TIME;

int main()
{
    Agenda ag;

    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Rdv e2(Date(12, 11, 2013), "Reunion UV",
           Horaire(17, 30), Duree(60),
           "Intervenants UV", "Bureau");
    EvtPj e3(Date(1, 5, 2026), Date(3, 5, 2026), "Festival");

    ag << e1 << e2 << e3; // Prototype：内部 clone

    // 双向遍历（Iterator）
    for (auto it = ag.begin(); it != ag.end(); ++it)
    {
        std::cout << *it;
    }

    std::cout << "--- reverse ---\n";
    auto it = ag.end();
    --it;
    std::cout << *it;

    return 0;
}

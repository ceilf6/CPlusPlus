#include "agenda.h"

namespace TIME
{

    Agenda &Agenda::operator<<(Evt1j &e)
    {
        evenements.push_back(&e); // 只存地址
        return *this;
    }

    void Agenda::afficher(std::ostream &f) const
    {
        f << "===== Agenda =====\n";
        for (const auto &evt : evenements)
        {
            evt->afficher(f); // ★ 多态调用
            f << "-----------------\n";
        }
    }

} // namespace TIME
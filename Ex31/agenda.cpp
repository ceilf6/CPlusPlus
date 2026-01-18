#include "agenda.h"

namespace TIME
{

    Agenda &Agenda::operator<<(const Evt &e)
    {
        events.push_back(e.clone()); // Prototype：多态深拷贝
        return *this;
    }

    Agenda::Iterator Agenda::begin()
    {
        return Iterator(events.begin());
    }
    Agenda::Iterator Agenda::end()
    {
        return Iterator(events.end());
    }

    void Agenda::afficher(std::ostream &f) const
    {
        f << "===== Agenda =====\n";
        for (const auto &p : events)
        {
            p->afficher(f);
        }
    }

} // namespace TIME

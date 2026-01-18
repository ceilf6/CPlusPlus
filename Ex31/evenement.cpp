#include "evenement.h"

namespace TIME
{

    /* ===== Evt ===== */
    Evt::Evt(const std::string &s) : sujet(s) {}
    const std::string &Evt::getDescription() const { return sujet; }

    std::ostream &operator<<(std::ostream &os, const Evt &e)
    {
        e.afficher(os);
        return os;
    }

    /* ===== Evt1j ===== */
    Evt1j::Evt1j(const Date &d, const std::string &s) : Evt(s), date(d) {}
    const Date &Evt1j::getDate() const { return date; }

    void Evt1j::afficher(std::ostream &f) const
    {
        f << "[Evt1j] " << date << " | " << getDescription() << "\n";
    }
    std::unique_ptr<Evt> Evt1j::clone() const
    {
        return std::make_unique<Evt1j>(*this);
    }

    /* ===== Evt1jDur ===== */
    Evt1jDur::Evt1jDur(const Date &d, const std::string &s,
                       const Horaire &h, const Duree &du)
        : Evt1j(d, s), debut(h), duree(du) {}

    const Horaire &Evt1jDur::getHoraire() const { return debut; }
    const Duree &Evt1jDur::getDuree() const { return duree; }

    void Evt1jDur::afficher(std::ostream &f) const
    {
        f << "[Evt1jDur] " << getDate()
          << " " << debut << " (" << duree << ") | "
          << getDescription() << "\n";
    }
    std::unique_ptr<Evt> Evt1jDur::clone() const
    {
        return std::make_unique<Evt1jDur>(*this);
    }

    /* ===== Rdv ===== */
    Rdv::Rdv(const Date &d, const std::string &s,
             const Horaire &h, const Duree &du,
             const std::string &pers, const std::string &l)
        : Evt1jDur(d, s, h, du), personnes(pers), lieu(l) {}

    void Rdv::afficher(std::ostream &f) const
    {
        f << "[Rdv] " << getDate()
          << " " << getHoraire() << " (" << getDuree() << ") | "
          << getDescription()
          << " | " << personnes << " @ " << lieu << "\n";
    }
    std::unique_ptr<Evt> Rdv::clone() const
    {
        return std::make_unique<Rdv>(*this);
    }

    /* ===== EvtPj ===== */
    EvtPj::EvtPj(const Date &d1, const Date &d2, const std::string &s)
        : Evt(s), debut(d1), fin(d2) {}

    void EvtPj::afficher(std::ostream &f) const
    {
        f << "[EvtPj] " << debut << " -> " << fin
          << " | " << getDescription() << "\n";
    }
    std::unique_ptr<Evt> EvtPj::clone() const
    {
        return std::make_unique<EvtPj>(*this);
    }

} // namespace TIME

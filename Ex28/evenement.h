#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <iostream>
#include <string>
#include "timing.h"

namespace TIME
{

    /* ===== Evt1j ===== */
    class Evt1j
    {
    private:
        Date date;
        std::string sujet;

    public:
        Evt1j(const Date &d, const std::string &s);

        // ★ Ex28 关键：必须虚析构，才能通过基类指针 delete 派生对象
        virtual ~Evt1j();

        const Date &getDate() const;
        const std::string &getDescription() const;

        // ★ Ex28 关键：必须 virtual 才能多态调用 afficher()
        virtual void afficher(std::ostream &f = std::cout) const;

        // ★ Ex28 Q1.2：让 cout << event; 可用于任何事件（多态）
        friend std::ostream &operator<<(std::ostream &os, const Evt1j &e);
    };

    /* ===== Evt1jDur ===== */
    class Evt1jDur : public Evt1j
    {
    private:
        Horaire debut;
        Duree duree;

    public:
        Evt1jDur(const Date &d,
                 const std::string &s,
                 const Horaire &h,
                 const Duree &du);

        ~Evt1jDur() override;

        const Horaire &getHoraire() const;
        const Duree &getDuree() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

    /* ===== Rdv ===== */
    class Rdv : public Evt1jDur
    {
    private:
        std::string personnes;
        std::string lieu;

    public:
        Rdv(const Date &d,
            const std::string &s,
            const Horaire &h,
            const Duree &du,
            const std::string &pers,
            const std::string &l);

        ~Rdv() override;

        const std::string &getPersonnes() const;
        const std::string &getLieu() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

} // namespace TIME

#endif
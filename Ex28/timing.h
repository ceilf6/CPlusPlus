#ifndef TIMING_H
#define TIMING_H

#include <iostream>

namespace TIME
{

    /* ===== Date ===== */
    class Date
    {
    private:
        int jour, mois, annee;

    public:
        Date(int j = 1, int m = 1, int a = 1970);

        int getJour() const;
        int getMois() const;
        int getAnnee() const;

        friend std::ostream &operator<<(std::ostream &os, const Date &d);
    };

    /* ===== Horaire ===== */
    class Horaire
    {
    private:
        int heure, minute;

    public:
        Horaire(int h = 0, int m = 0);

        int getHeure() const;
        int getMinute() const;

        friend std::ostream &operator<<(std::ostream &os, const Horaire &h);
    };

    /* ===== Duree ===== */
    class Duree
    {
    private:
        int minutes;

    public:
        explicit Duree(int m = 0);

        int getMinutes() const;

        friend std::ostream &operator<<(std::ostream &os, const Duree &d);
    };

} // namespace TIME

#endif
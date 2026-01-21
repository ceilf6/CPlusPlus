#ifndef CPP_EVENEMENT_H
#define CPP_EVENEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "timing.h"

namespace TIME {
    class Evt {
    private:
        std::string sujet;
    public:
        Evt(const std::string &s) : sujet(s) {}

        const std::string &getDescription() const { return sujet; }

        virtual void afficher(std::ostream &f = std::cout) const = 0;
    };

    class EvtPj : public Evt {
        Date debut;
        Date fin;
    public:
        EvtPj(const Date &d, const Date &f, const std::string &s) :
                Evt(s), debut(d), fin(f) {}

        const Date &getDateDebut() const { return debut; }

        const Date &getDateFin() const { return fin; }

        void afficher(std::ostream &f = std::cout) const;
    };

    class Evt1j : public Evt {
    private:
        Date date;
    public:
        Evt1j(const Date &d, const std::string &s) : Evt(s), date(d) {}

        const Date &getDate() const { return date; }

        virtual void afficher(std::ostream &f = std::cout) const;
    };


    class Evt1jDur : public Evt1j {
    private:
        Horaire debut;
        Duree duree;
    public:
        Evt1jDur(const Date &d, const std::string &s,
                 const Horaire &h, const Duree& t) :
                Evt1j(d, s), // appel au constructeur de la classe de base
                debut(h), duree(t) {}

        const Horaire &getHoraire() const { return debut; }

        const Duree &getDuree() const { return duree; }

        void afficher(std::ostream &f = std::cout) const;

    };


    class Rdv : public Evt1jDur {
        std::string personne;
        std::string lieu;
    public:
        Rdv(const Date &d, const std::string &s,
            const Horaire &h, const Duree &dur,
            const std::string &p, const std::string &l) :
                Evt1jDur(d, s, h, dur),
                personne(p), lieu(l) {}

        Rdv &operator=(const Rdv &r) {
            Evt1jDur *x = this;
            *x = r; // recopie de la partie Evt1jDur
            personne = r.personne;
            lieu = r.lieu;
            return *this;
        }

        Rdv(const Rdv &r) : Evt1jDur(r), personne(r.personne), lieu(r.lieu) {}

        const std::string &getPersonne() const { return personne; }

        const std::string &getLieu() const { return lieu; }

        void afficher(std::ostream &f = std::cout) const;
    };

    class Agenda {
        std::vector<Evt *> tab;
    public:
        class iterator : public std::vector<Evt *>::iterator {
        public:
            Evt &operator*() const {
                return *std::vector<Evt *>::iterator::operator*();
            }

        private:
            friend class Agenda;

            iterator(const std::vector<Evt *>::iterator &it) :
                    std::vector<Evt *>::iterator(it) {}
        };

        iterator begin() { return iterator(tab.begin()); }

        iterator end() { return iterator(tab.end()); }

        class const_iterator : public std::vector<Evt *>::const_iterator {
        public:
            const Evt &operator*() const {
                return *std::vector<Evt *>::const_iterator::operator*();
            }

        private:
            friend class Agenda;

            const_iterator(const std::vector<Evt *>::const_iterator &it) :
                    std::vector<Evt *>::const_iterator(it) {}
        };

        const_iterator cbegin() const { return const_iterator(tab.cbegin()); }

        const_iterator cend() const { return const_iterator(tab.cend()); }

        const_iterator begin() const { return const_iterator(tab.begin()); }

        const_iterator end() const { return const_iterator(tab.end()); }


        class reverse_iterator : public std::vector<Evt *>::reverse_iterator {
        public:
            Evt &operator*() const {
                return *std::vector<Evt *>::reverse_iterator::operator*();
            }

        private:
            friend class Agenda;

            reverse_iterator(const std::vector<Evt *>::reverse_iterator &it) :
                    std::vector<Evt *>::reverse_iterator(it) {}
        };

        reverse_iterator rbegin() { return reverse_iterator(tab.rbegin()); }

        reverse_iterator rend() { return reverse_iterator(tab.rend()); }

        class const_reverse_iterator : public std::vector<Evt *>::const_reverse_iterator {
        public:
            const Evt &operator*() const {
                return *std::vector<Evt *>::const_reverse_iterator::operator*();
            }

        private:
            friend class Agenda;

            const_reverse_iterator(const std::vector<Evt *>::const_reverse_iterator &it) :
                    std::vector<Evt *>::const_reverse_iterator(it) {}
        };

        const_reverse_iterator crbegin() const { return const_reverse_iterator(tab.crbegin()); }

        const_reverse_iterator crend() const { return const_reverse_iterator(tab.crend()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(tab.rbegin()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(tab.rend()); }


        Agenda() = default;

        virtual ~Agenda(); // destructeur par défaut virtuel
        Agenda(const Agenda &) = delete;

        Agenda &operator=(const Agenda &) = delete;

        Agenda &operator<<(Evt &e);

        void afficher(std::ostream &f = std::cout) const;
    };
}

std::ostream &operator<<(std::ostream &, const TIME::Evt &);

#endif //CPP_EVENEMENT_H

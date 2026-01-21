#ifndef CPP_EVENEMENT_H
#define CPP_EVENEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "timing.h"

namespace TIME{
    class Evt {
    private:
        std::string sujet;
    public:
        Evt(const std::string& s): sujet(s){}
        const std::string& getDescription() const { return sujet; }
        virtual std::string toString() const=0;
        void afficher(std::ostream& f=std::cout) const { f<<toString(); }
        virtual Evt* clone() const = 0;
    };

    class EvtPj : public Evt {
        Date debut;
        Date fin;
    public:
        EvtPj(const Date& d,const Date& f, const std::string& s):
                Evt(s),debut(d),fin(f){}
        const Date& getDateDebut() const { return debut; }
        const Date& getDateFin() const { return fin; }
        std::string toString() const;
        EvtPj* clone() const;
    };

    class Evt1j : public Evt{
    private:
        Date date;
    public:
        Evt1j(const Date& d, const std::string& s): Evt(s), date(d){}
        const Date& getDate() const { return date; }
        std::string toString() const;
        Evt1j* clone() const;
    };



    class Evt1jDur : public Evt1j {
    private:
        Horaire debut;
        Duree duree;
    public:
        Evt1jDur(const Date& d, const std::string& s,
                 const Horaire& h, const Duree& t):
                Evt1j(d,s), // appel au constructeur de la classe de base
                debut(h),duree(t){}
        const Horaire& getHoraire() const { return debut; }
        const Duree& getDuree() const { return duree; }
        std::string toString() const;
        Evt1jDur* clone() const;

    };



    class Rdv : public Evt1jDur {
        std::string personne;
        std::string lieu;
    public:
        Rdv(const Date& d, const std::string& s,
            const Horaire& h,const Duree& dur,
            const std::string& p, const std::string& l):
                Evt1jDur(d,s,h,dur),
                personne(p),lieu(l){}

        Rdv& operator=(const Rdv& r){
            Evt1jDur* x=this;
            *x=r; // recopie de la partie Evt1jDur
            personne=r.personne;
            lieu=r.lieu;
            return *this;
        }

        Rdv(const Rdv& r):Evt1jDur(r),personne(r.personne),lieu(r.lieu){}

        const std::string& getPersonne() const { return personne; }
        const std::string& getLieu() const { return lieu; }
        std::string toString() const;
        Rdv* clone() const;
    };

    class Agenda {
        std::vector<Evt*> tab;
    public:
        class iterator : public std::vector<Evt*>::iterator {
        public:
            Evt & operator*() const {
                return *std::vector<Evt*>::iterator::operator*();
            }
        private:
            friend class Agenda;
            iterator(const std::vector<Evt*>::iterator& it):
                    std::vector<Evt*>::iterator(it) {}
        };
        iterator begin() { return iterator(tab.begin()); }
        iterator end() { return iterator(tab.end()); }
        class const_iterator : public std::vector<Evt*>::const_iterator {
        public:
            const Evt& operator*() const {
                return *std::vector<Evt*>::const_iterator::operator*();
            }
        private:
            friend class Agenda;
            const_iterator(const std::vector<Evt*>::const_iterator& it) :
                    std::vector<Evt*>::const_iterator(it) {}
        };
        const_iterator cbegin() const { return const_iterator(tab.begin()); }
        const_iterator cend() const { return const_iterator(tab.end()); }
        const_iterator begin() const { return const_iterator(tab.begin()); }
        const_iterator end() const { return const_iterator(tab.end()); }

        Agenda() = default;
        virtual ~Agenda(); // destructeur par défaut virtuel
        Agenda(const Agenda&) = delete;
        Agenda& operator=(const Agenda&) = delete;
        Agenda& operator<<(Evt& e);
        void afficher(std::ostream& f = std::cout)const;
    };

    inline Date getDate(const Evt& e){
        const Evt1j* pt1=dynamic_cast<const Evt1j*>(&e);
        const EvtPj* pt2=dynamic_cast<const EvtPj*>(&e);
        if (pt1) return pt1->getDate();
        if (pt2) return pt2->getDateDebut();
        throw "type evt inattendu";
    }

    inline bool operator<(const Evt& e1, const Evt& e2){
        Date d1=getDate(e1);
        Date d2=getDate(e2);
        if (d1 < d2) return true;
        if (d2 < d1) return false;
// d1==d2
        const Evt1jDur* pt1=dynamic_cast<const Evt1jDur*>(&e1);
        const Evt1jDur* pt2=dynamic_cast<const Evt1jDur*>(&e2);
        if (pt1==nullptr && pt2!=nullptr) return true;
        if (pt1!=nullptr && pt2==nullptr) return false;
// ce sont deux evt avec un horaire, on les compare
        return pt1->getHoraire() < pt2->getHoraire();
    }
}

std::ostream& operator<<(std::ostream&, const TIME::Evt&);




#endif //CPP_EVENEMENT_H

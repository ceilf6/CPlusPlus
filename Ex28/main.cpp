#include <iostream>
#include "evenement.h"

int main()
{
    using namespace TIME;

    std::cout << "===== Question 1 : Polymorphisme =====\n";

    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Evt1j e2(Date(11, 6, 2013), "Shenzhou");
    Evt1jDur e3(Date(11, 6, 2013), "Lancement de Longue Marche", Horaire(17, 38), Duree(10));
    Rdv e4(Date(11, 4, 2013), "reunion UV", Horaire(17, 30), Duree(60), "Intervenants UV", "bureau");

    e1.afficher();
    e2.afficher();
    e3.afficher();
    e4.afficher();

    Evt1j *pt1 = &e1;
    Evt1j *pt2 = &e2;
    Evt1j *pt3 = &e3;
    Evt1j *pt4 = &e4;

    std::cout << "\n-- appels via pointeurs de base --\n";
    pt1->afficher();
    pt2->afficher();
    pt3->afficher(); // doit appeler Evt1jDur::afficher
    pt4->afficher(); // doit appeler Rdv::afficher

    std::cout << "\n-- operator<< polymorphe --\n";
    std::cout << *pt1 << *pt3 << *pt4;

    std::cout << "\n===== Question 2 : Polymorphisme et destruction =====\n";

    std::cout << "\n-- delete via Rdv* --\n";
    Rdv *pt5 = new Rdv(Date(12, 11, 2013), "reunion UV", Horaire(17, 30), Duree(60),
                       "Intervenants UV", "bureau");
    pt5->afficher();
    delete pt5;

    std::cout << "\n-- delete via Evt1j* (base) --\n";
    Evt1j *pt6 = new Rdv(Date(12, 11, 2013), "reunion UV", Horaire(17, 30), Duree(60),
                         "Intervenants UV", "bureau");
    pt6->afficher();
    delete pt6; // doit détruire Rdv puis Evt1jDur puis Evt1j

    return 0;
}
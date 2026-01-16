#include <iostream>
#include "agenda.h"

int main()
{
    using namespace TIME;

    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Evt1jDur e2(Date(11, 6, 2013), "Lancement Longue Marche",
                Horaire(17, 38), Duree(10));
    Rdv e3(Date(12, 11, 2013), "reunion UV",
           Horaire(17, 30), Duree(60),
           "Intervenants UV", "bureau");

    Agenda ag;
    ag << e1 << e2 << e3; // opérateur << enchaînable

    ag.afficher();

    return 0;
}
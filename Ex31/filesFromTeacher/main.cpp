#include <iostream>
#include "evenement.h"


int main() {
    using namespace std;
    using namespace TIME;
    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Evt1j e2(Date(11, 6, 2013), "Shenzhou");
    Evt1jDur e3(Date(11, 6, 2013), "Lancement de Longue Marche", Horaire(17, 38), Duree
            (0, 10));
    Rdv e4(Date(11, 4, 2013), "reunion UV", Horaire(17, 30), Duree(60), "Intervenants UV", "bureau");


    return 0;
}

#include <iostream>
#include "evenement.h"


int main() {
    using namespace std;
    using namespace TIME;
    Evt1j e1(Date(4,10,1957),"Spoutnik");
    Evt1jDur e2(Date(4,4,2012),"courses",Horaire(19,0),Duree(45));
    Rdv e3(Date(11,4,2012),"reunion UV",Horaire(17,30),Duree(60),"Intervenants UV","bureau");
    Evt1j e4(Date(20,7,1969),"Premier Homme sur la Lune");
    Evt1j e5(Date(14,7,1789),"Prise de la Bastille");
    Rdv e6(Date(9,4,2012),"reunion",Horaire(10,45),Duree(1,30),"etudiant","passerelle");
    Evt1jDur e7(Date(6,12,2012),"St Nicolas",Horaire(19,0),Duree(45));
    EvtPj e8(Date(21,6,2010), Date(28,6,2010), "examens");
    Rdv e9(Date(19,5,2013),"rdv",Horaire(11,45),Duree(2,30),"Mr X","Utseus");
    Agenda mon_agenda;
    mon_agenda<<e1<<e2<<e3<<e4<<e5<<e6<<e7<<e8;

    //iterator
    for(auto it=mon_agenda.begin(); it!=mon_agenda.end(); ++it)
        std::cout << *it <<"\n";

    // const_iterator
    for(auto it=mon_agenda.cbegin(); it!=mon_agenda.cend(); ++it)
        std::cout  <<*it  <<"\n";

    // maintenant, on peut aussi utiliser un range for
    for(auto& e : mon_agenda) std:cout<<e<<"\n";



    return 0;
}

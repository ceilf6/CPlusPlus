#include "mylog.h"
#include "evenement.h"

using namespace TIME;

void MyLog::addEvt(
    const Date &d,
    const Horaire &h,
    const std::string &s)
{
    if (hasLast)
    {
        if (d < lastDate || (d == lastDate && h < lastHoraire))
        {
            throw LogError();
        }
    }

    Rdv evt(d, s, h, Duree(0), "", "");
    agenda << evt;

    lastDate = d;
    lastHoraire = h;
    hasLast = true;
}

void MyLog::displayLog(std::ostream &f) const
{
    agenda.afficher(f);
}
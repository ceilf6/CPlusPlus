#include "SommaireCard.h"
#include <iostream>

void SommaireCard::addChapitre(Card *c)
{
    chapitres.push_back(c);
}

void SommaireCard::handleClick(const std::string &intitule)
{
    if (intitule.rfind("chapitre", 0) == 0)
    {
        int num = std::stoi(intitule.substr(8));
        if (num > 0 && num <= chapitres.size())
        {
            chapitres[num - 1]->afficher();
        }
        else
        {
            std::cout << "Chapitre inexistant\n";
        }
    }
    else
    {
        Card::handleClick(intitule);
    }
}
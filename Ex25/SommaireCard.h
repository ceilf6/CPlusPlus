#ifndef SOMMAIRECARD_H
#define SOMMAIRECARD_H

#include "Card.h"
#include <vector>

class SommaireCard : public Card
{
    std::vector<Card *> chapitres;

public:
    void addChapitre(Card *c);
    void handleClick(const std::string &intitule) override;
};

#endif
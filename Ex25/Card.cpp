#include "Card.h"
#include <iostream>

Card::Card() : previous(nullptr), next(nullptr) {}

Card::~Card()
{
    for (auto w : widgets)
    {
        delete w;
    }
}

void Card::setPrevious(Card *p)
{
    previous = p;
}

void Card::setNext(Card *n)
{
    next = n;
}

Card *Card::getPrevious() const
{
    return previous;
}

Card *Card::getNext() const
{
    return next;
}

void Card::addWidget(Widget *w)
{
    widgets.push_back(w);
}

void Card::afficher()
{
    std::cout << "\n=== Affichage de la carte ===\n";
    for (auto w : widgets)
    {
        w->afficher();
    }
}

void Card::handleClick(const std::string &intitule)
{
    if (intitule == "precedent" && previous)
    {
        previous->afficher();
    }
    else if (intitule == "suivant" && next)
    {
        next->afficher();
    }
    else
    {
        std::cout << "Navigation impossible\n";
    }
}
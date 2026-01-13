#include "Button.h"
#include "Card.h"
#include <iostream>

Button::Button(const std::string &i, Card *c)
    : intitule(i), owner(c) {}

void Button::onClick()
{
    std::cout << "Bouton cliqué : " << intitule << std::endl;
    owner->handleClick(intitule);
}

void Button::afficher()
{
    std::cout << "[Button] " << intitule << std::endl;
}

std::string Button::getIntitule() const
{
    return intitule;
}
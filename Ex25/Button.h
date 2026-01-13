#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "Widget.h"

class Card; // 前向声明

class Button : public Widget
{
protected:
    std::string intitule;
    Card *owner;

public:
    Button(const std::string &i, Card *c);

    void onClick();
    void afficher() override;

    std::string getIntitule() const;
};

#endif
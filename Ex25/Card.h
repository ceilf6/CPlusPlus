#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include "Widget.h"

class Card
{
protected:
    Card *previous;
    Card *next;
    std::vector<Widget *> widgets;

public:
    Card();
    virtual ~Card();

    void setPrevious(Card *p);
    void setNext(Card *n);

    Card *getPrevious() const;
    Card *getNext() const;

    void addWidget(Widget *w);

    virtual void afficher();
    virtual void handleClick(const std::string &intitule);
};

#endif
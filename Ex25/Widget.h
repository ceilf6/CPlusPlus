#ifndef WIDGET_H
#define WIDGET_H

class Widget
{
public:
    virtual void afficher() = 0;
    virtual ~Widget() = default;
};

#endif
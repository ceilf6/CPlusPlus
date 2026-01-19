#include <iostream>
#include "Q7.h"

template <class A, class B>
std::ostream &operator<<(std::ostream &f, const relation<A, B> &r)
{
    f << "Relation " << r.get_nom() << std::endl;
    for (relation<A, B>::iterator it = r.begin(); it != r.end(); ++it)
        f << (*it).first << r, get_symbole() << it->second;
    return f;
}
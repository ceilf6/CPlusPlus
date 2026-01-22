#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "vector.h"

using namespace TD;

namespace AO {
    // adapteur d’objet
    template<class T, class CONT=Vector<T>>
    class Stack {
        CONT cont;
    public:
        Stack():cont(0){}

        void push(const T& x) { cont.push_back(x); }
        void pop() { cont.pop_back(); }

        const T& top() const { return cont.back(); }
        T& top() { return cont.back(); }

        bool empty() const { return cont.empty(); }
        void clear() { cont.clear(); }
    };
}

namespace AC { // adapteur de classe
    template<class T, class CONT=Vector<T>>
    class Stack : private CONT {
    public:
        Stack(): CONT(0){}
        void push(const T& x) { CONT::push_back(x); }
        void pop() { CONT::pop_back(); }
        const T& top() const { return CONT::back(); }
        T& top() { return CONT::back(); }
        // bool empty() const { return CONT::empty(); }
        // void clear() { CONT::clear(); }
        using CONT::empty; // On recupere la methode empty de la class CONT
        using CONT::clear; // On recupere le methode clear de la class CONT
    };
}

#endif // STACK_H_INCLUDED
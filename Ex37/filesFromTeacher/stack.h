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
        class iterator {
            // Le type : type de l'iterateur du contenur dont on fait une composition
            typename CONT::iterator courant;
        public:
            iterator():courant() {}
            iterator(typename CONT::iterator c):courant(c) {}
            iterator& operator++() { courant++; return *this; }
            iterator operator++(int) { iterator tmp=*this; courant++; return tmp; }
            bool operator==(const iterator& it) const { return courant==it.courant; }
            bool operator!=(const iterator& it) const { return courant!=it.courant; }
            T& operator*() const { return *courant; }
        };

        iterator begin() { return iterator(cont.begin()); }
        iterator end() { return iterator(cont.end()); }

        class const_iterator {
            // Le type : type de l'iterateur du contenur dont on fait une composition
            typename CONT::const_iterator courant;
        public:
            const_iterator():courant() {}
            const_iterator(typename CONT::const_iterator c):courant(c) {}
            const_iterator& operator++() { courant++; return *this; }
            const_iterator operator++(int) { const_iterator tmp=*this; courant++; return tmp; }
            bool operator==(const const_iterator& it) const { return courant==it.courant; }
            bool operator!=(const const_iterator& it) const { return courant!=it.courant; }
            const T& operator*() const { return *courant; }
        };

        const_iterator cbegin() const { return const_iterator(cont.cbegin()); }
        const_iterator cend() const { return const_iterator(cont.cend()); }

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
        class iterator : public CONT::iterator {
            // Le type : type de l'iterateur du contenur dont on fait une composition
            typename CONT::iterator courant;
        public:
            iterator():courant() {}
            iterator(typename CONT::iterator c):CONT::iterator(c) {}
        };

        iterator begin() { return iterator(CONT::begin()); }
        iterator end() { return iterator(CONT::end()); }

        class const_iterator : public CONT::const_iterator {
            // Le type : type de l'iterateur du contenur dont on fait une composition
            typename CONT::const_iterator courant;
        public:
            const_iterator():CONT::const_iterator() {}
            const_iterator(typename CONT::const_iterator c):courant(c) {}
        };

        const_iterator cbegin() const { return const_iterator(CONT::begin()); }
        const_iterator cend() const { return const_iterator(CONT::end()); }

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
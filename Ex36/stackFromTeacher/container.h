#ifndef CPP_LO02_CONTAINER_H
#define CPP_LO02_CONTAINER_H

#include <string>
#include <stdexcept>

using namespace std;

namespace TD {

    class ContainerException : public exception {
    protected: // remplacer private par protected
        string info;
    public:
        ContainerException(const string& i="") noexcept :info(i){}
        const char* what() const noexcept { return info.c_str(); }
        ~ContainerException()noexcept{}
    };

    template<class T> class Container {
    protected:
        unsigned int nb; // Nombre d'elements dans le conteneur

    public:
        Container(unsigned int nb) : nb(nb) {}
        virtual ~Container() { }

        // Methodes concretes pures (car on a tres probablement pas besoin de redefinir plus tard !)
        unsigned int size()const { return nb; }
        bool empty()const { if(nb == 0) { return true; } else { return false; } }

        // Methodes virtuelles pures ��OBLIGEES de redefinir pour avoir une classe concrete !)
        virtual T& element(unsigned int i) =0; // Obliger de redfinir dans classes derivees
        virtual const T& element(unsigned int i)const=0;

        // Methodes virtuelles "simples" (On peut ou pas redefinir plus tard ... On peut garder
        // le code d'origine ....)
        virtual T& front();
        virtual const T& front()const;
        virtual T& back();
        virtual const T& back()const;

        virtual void push_back(const T& x) = 0;
        virtual void pop_back() = 0;

        // Methode concrete ou virtual simple : au choix !
        void clear() { while(!empty()) { pop_back(); } }
    };
}

// On peut utiliser la methode "element", meme si on a pas definit cette methode, car on connait son comportement
// En effet, on sait que la methode "element" permet de recuperer une reference d'un element a la position i
template<class T> T& TD::Container<T>::front() {
    if(!empty())
        return element(0);
    else
        throw ContainerException("Conteneur vide");
}

template<class T> const T& TD::Container<T>::front() const {
    if(!empty())
        return element(0);
    else
        throw ContainerException("Conteneur vide");
}

template<class T> T& TD::Container<T>::back() {
    if(!empty())
        return element(nb-1);
    else
        throw ContainerException("Conteneur vide");
}

template<class T> const T& TD::Container<T>::back() const {
    if(!empty())
        return element(nb-1);
    else
        throw ContainerException("Conteneur vide");
}


#endif //CPP_LO02_CONTAINER_H

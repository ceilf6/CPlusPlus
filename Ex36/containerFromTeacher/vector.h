#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "container.h"

namespace TD {
    template<class T>
    class Vector : public Container<T> {
        T* tab;
        // memory_size : taille memoire dynamique du conteneur
        unsigned int memory_size;
    public:
        // initialize_with : parameter pour initializer les "s" valeurs du conteneurs (on fourni un constructeur pour un objet ou une valeur pour un type natif)
        Vector(unsigned int s=0, const T& initialize_with=T());
        Vector(const Vector<T>&);
        ~Vector();
        Vector<T>& operator=(const Vector<T>& t);

        // Mot clef override : mot-clef qui signifie qu'on donne une redefinition/definition de la methode
        // Redefinition des methodes element et push/pop_back (qui sont virtuelles pures dans la classe de base Container)
        T& element(unsigned int i) override;
        const T& element(unsigned int i) const override;

        void push_back(const T& x) override;
        void pop_back() override;

        // Ajout de l'operateur [] pour l'access directe aux elements du conteneur
        T& operator[](unsigned int i) { return tab[i]; }
        const T& operator[](unsigned int i) const { return tab[i]; }

    };
}

template<class T>
TD::Vector<T>::Vector(unsigned int s, const T& initialize_with):
        Container<T>(s), tab(new T[s]), memory_size(s)
{
    // initialize_with : parameter pour initializer les "s" valeurs du conteneurs (on fourni un constructeur pour un objet ou une valeur pour un type natif)
    for(unsigned int i=0; i<Container<T>::nb; i++) {
        tab[i]=initialize_with;
    }
}

template<class T> TD::Vector<T>::Vector(const TD::Vector<T>& t):
        Container<T>(t.nb), tab(new T[t.size()]), memory_size(t.size())
{
    for(unsigned int i=0; i<Container<T>::nb; i++) {
        tab[i]=t.tab[i];
    }
}

template<class T> TD::Vector<T>::~Vector(){
    delete[] tab;
}

template<class T> T& TD::Vector<T>::element(unsigned int i){
    // On utilise l’opéeateur de réeolution de portee Container<T> car certaines spécialisations de Container<T> pourraient ne pas contenir cet attribut (heritage prive ou autre)
    // donc on s’engage ici avec le compilateur à n’utiliser que des spécialisations qui auront toujours cet attribut
    if (i<Container<T>::nb) return tab[i];
    throw ContainerException("erreur Vector : demande hors limite");
}

template<class T> const T& TD::Vector<T>::element(unsigned int i) const{
    if (i<Container<T>::nb) return tab[i];
    throw ContainerException("erreur Vector : demande hors limite");
}

// Constructeur de recopie
template<class T>
TD::Vector<T>& TD::Vector<T>::operator=(const TD::Vector<T>& t){
    if (this!=&t){
        T* newtab = new T[t.nb];

        for(unsigned int i=0; i<t.nb; i++) {
            newtab[i]=t.tab[i];
        }

        Container<T>::nb=t.nb;
        memory_size=t.nb;
        T* old=tab;
        tab=newtab;

        delete[] old;
    }
    return *this;
}

// Definition de la methode push_back
template<class T> void TD::Vector<T>::push_back(const T& x){
    // On a besoin ici d'agrandir la taille de "tab"
    // Agrandissement memoire
    if (Container<T>::nb==memory_size){
        T* newtab = new T[memory_size+5];

        for(unsigned int i=0; i<Container<T>::size(); i++) {
            newtab[i]=tab[i];
        }

        T* old=tab;
        memory_size+=5;
        tab=newtab;

        delete[] old;
    }
    tab[Container<T>::nb++]=x;
}

template<class T> void TD::Vector<T>::pop_back(){
    if (!this->empty()){
        Container<T>::nb--;
    }
    else throw ContainerException("erreur Vector :: Vector vide");
}

#endif // VECTOR_H_INCLUDED
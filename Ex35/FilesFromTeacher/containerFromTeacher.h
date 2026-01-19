#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdexcept>
#include <cstddef>
#include <algorithm>  // Pour std::copy

// Exception pour les accès hors limites
class ContainerException : public std::exception {
private:
    const char* message;
    
public:
    ContainerException(const char* msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message;
    }
};

// Classe abstraite template Container
template<typename T>
class Container {
public:
    // Destructeur virtuel
    virtual ~Container() {}
    
    // Méthodes de l'interface commune (méthodes virtuelles pures)
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual T& element(size_t i) = 0;
    virtual const T& element(size_t i) const = 0;
    virtual void push_back(const T& x) = 0;
    virtual void pop_back() = 0;
    virtual void clear() = 0;
    
    // Méthodes template (implémentées dans la classe de base)
    T& front() {
        if (empty()) {
            throw ContainerException("Container is empty - cannot access front element");
        }
        return element(0);
    }
    
    const T& front() const {
        if (empty()) {
            throw ContainerException("Container is empty - cannot access front element");
        }
        return element(0);
    }
    
    T& back() {
        if (empty()) {
            throw ContainerException("Container is empty - cannot access back element");
        }
        return element(size() - 1);
    }
    
    const T& back() const {
        if (empty()) {
            throw ContainerException("Container is empty - cannot access back element");
        }
        return element(size() - 1);
    }
    
protected:
    void checkIndex(size_t i) const {
        if (i >= size()) {
            throw ContainerException("Index out of bounds");
        }
    }
    
    void checkNotEmptyForPop() const {
        if (empty()) {
            throw ContainerException("Container is empty - cannot pop element");
        }
    }
};

// Classe Vector héritant de Container
template<typename T>
class Vector : public Container<T> {
private:
    T* data;           // Tableau dynamique d'éléments
    size_t capacity;   // Capacité du tableau
    size_t count;      // Nombre d'éléments réellement présents
    
    // Méthode privée pour redimensionner le tableau (INTERNE - renommée)
    void resizeInternal(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        
        // Copier les éléments existants
        for (size_t i = 0; i < count; ++i) {
            new_data[i] = data[i];
        }
        
        // Initialiser les nouvelles cases avec le constructeur par défaut
        for (size_t i = count; i < new_capacity; ++i) {
            new_data[i] = T();  // Constructeur sans argument
        }
        
        // Libérer l'ancienne mémoire et mettre à jour
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    
public:
    // Constructeur principal avec valeurs par défaut
    Vector(size_t initial_size = 0, const T& initial_value = T())
        : capacity(initial_size > 0 ? initial_size : 1), 
          count(initial_size) {
        
        data = new T[capacity];
        
        // Initialiser tous les éléments avec initial_value
        for (size_t i = 0; i < count; ++i) {
            data[i] = initial_value;
        }
        
        // Initialiser le reste avec le constructeur par défaut
        for (size_t i = count; i < capacity; ++i) {
            data[i] = T();
        }
    }
    
    // Constructeur de copie
    Vector(const Vector& other) 
        : capacity(other.capacity), count(other.count) {
        
        data = new T[capacity];
        
        // Copie profonde des éléments
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
        
        // Initialiser le reste
        for (size_t i = count; i < capacity; ++i) {
            data[i] = T();
        }
    }
    
    // Opérateur d'affectation
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            // Libérer l'ancienne mémoire
            delete[] data;
            
            // Copier les attributs
            capacity = other.capacity;
            count = other.count;
            
            // Allouer nouvelle mémoire
            data = new T[capacity];
            
            // Copie profonde des éléments
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
            
            // Initialiser le reste
            for (size_t i = count; i < capacity; ++i) {
                data[i] = T();
            }
        }
        return *this;
    }
    
    // Destructeur
    ~Vector() {
        delete[] data;
    }
    
    // Implémentation des méthodes virtuelles pures de Container
    size_t size() const override {
        return count;
    }
    
    bool empty() const override {
        return count == 0;
    }
    
    T& element(size_t i) override {
        if (i >= count) {
            throw ContainerException("Vector: index out of bounds");
        }
        return data[i];
    }
    
    const T& element(size_t i) const override {
        if (i >= count) {
            throw ContainerException("Vector: index out of bounds");
        }
        return data[i];
    }
    
    void push_back(const T& x) override {
        // Si le tableau est plein, le redimensionner
        if (count >= capacity) {
            resizeInternal(capacity * 2);
        }
        
        data[count++] = x;
    }
    
    void pop_back() override {
        if (count > 0) {
            --count;
        } else {
            throw ContainerException("Vector: cannot pop from empty vector");
        }
    }
    
    void clear() override {
        count = 0;
    }
    
    // Surcharge de l'opérateur [] pour un accès plus naturel
    T& operator[](size_t i) {
        return element(i);
    }
    
    const T& operator[](size_t i) const {
        return element(i);
    }
    
    // Méthodes supplémentaires utiles pour Vector
    
    // Réserver de la mémoire sans changer la taille
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            resizeInternal(new_capacity);
        }
    }
    
    // Redimensionner le vector (PUBLIQUE - pour l'utilisateur)
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity) {
            resizeInternal(new_size * 2);
        }
        
        // Si on agrandit, remplir avec value
        if (new_size > count) {
            for (size_t i = count; i < new_size; ++i) {
                data[i] = value;
            }
        }
        
        count = new_size;
    }
    
    // Obtenir la capacité actuelle
    size_t getCapacity() const {
        return capacity;
    }
    
    // Réduire la capacité à la taille actuelle
    void shrink_to_fit() {
        if (capacity > count) {
            resizeInternal(count);
        }
    }
    
    // Insérer un élément à une position spécifique
    void insert(size_t position, const T& value) {
        if (position > count) {
            throw ContainerException("Vector: insert position out of bounds");
        }
        
        // Vérifier si besoin de redimensionner
        if (count >= capacity) {
            resizeInternal(capacity * 2);
        }
        
        // Décaler les éléments vers la droite
        for (size_t i = count; i > position; --i) {
            data[i] = data[i - 1];
        }
        
        // Insérer le nouvel élément
        data[position] = value;
        ++count;
    }
    
    // Supprimer un élément à une position spécifique
    void erase(size_t position) {
        if (position >= count) {
            throw ContainerException("Vector: erase position out of bounds");
        }
        
        // Décaler les éléments vers la gauche
        for (size_t i = position; i < count - 1; ++i) {
            data[i] = data[i + 1];
        }
        
        --count;
    }
};

#endif // CONTAINER_H

#ifndef STACK_OBJECT_ADAPTER_H
#define STACK_OBJECT_ADAPTER_H

#include "stack_exception.h"
#include "container.h"
#include "vector.h"

template<typename T>
class StackObjectAdapter {
private:
    Container<T>* container;
    bool ownsContainer;
    
public:
    StackObjectAdapter() 
        : container(new Vector<T>()), ownsContainer(true) {}
    
    StackObjectAdapter(Container<T>* cont) 
        : container(cont), ownsContainer(true) {}
    
    StackObjectAdapter(Container<T>& cont) 
        : container(&cont), ownsContainer(false) {}
    
    StackObjectAdapter(const StackObjectAdapter& other) 
        : container(new Vector<T>(*dynamic_cast<Vector<T>*>(other.container))),
          ownsContainer(true) {}
    
    StackObjectAdapter& operator=(const StackObjectAdapter& other) {
        if (this != &other) {
            if (ownsContainer) {
                delete container;
            }
            container = new Vector<T>(*dynamic_cast<Vector<T>*>(other.container));
            ownsContainer = true;
        }
        return *this;
    }
    
    ~StackObjectAdapter() {
        if (ownsContainer) {
            delete container;
        }
    }
    
    bool empty() const {
        return container->empty();
    }
    
    size_t size() const {
        return container->size();
    }
    
    void push(const T& x) {
        container->push_back(x);
    }
    
    void pop() {
        if (empty()) {
            throw StackException("Stack is empty - cannot pop");
        }
        container->pop_back();
    }
    
    T& top() {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return container->back();
    }
    
    const T& top() const {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return container->back();
    }
    
    void clear() {
        container->clear();
    }
    
    void setContainer(Container<T>* newContainer, bool takeOwnership = true) {
        if (ownsContainer) {
            delete container;
        }
        container = newContainer;
        ownsContainer = takeOwnership;
    }
};

#endif // STACK_OBJECT_ADAPTER_H
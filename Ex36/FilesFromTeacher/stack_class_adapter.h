#ifndef STACK_CLASS_ADAPTER_H
#define STACK_CLASS_ADAPTER_H

#include "stack_exception.h"
#include "vector.h"

template<typename T, typename Container = Vector<T>>
class StackClassAdapter : private Container {
public:
    StackClassAdapter() = default;
    
    bool empty() const {
        return Container::empty();
    }
    
    size_t size() const {
        return Container::size();
    }
    
    void push(const T& x) {
        Container::push_back(x);
    }
    
    void pop() {
        if (empty()) {
            throw StackException("Stack is empty - cannot pop");
        }
        Container::pop_back();
    }
    
    T& top() {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return Container::back();
    }
    
    const T& top() const {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return Container::back();
    }
    
    void clear() {
        Container::clear();
    }
};

#endif // STACK_CLASS_ADAPTER_H
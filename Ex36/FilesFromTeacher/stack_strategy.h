#ifndef STACK_STRATEGY_H
#define STACK_STRATEGY_H

#include "stack_exception.h"
#include "container.h"
#include "vector.h"
#include <memory>

template<typename T>
class StackStrategy {
public:
    virtual ~StackStrategy() = default;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual void push(const T& x) = 0;
    virtual void pop() = 0;
    virtual T& top() = 0;
    virtual const T& top() const = 0;
    virtual void clear() = 0;
    virtual StackStrategy<T>* clone() const = 0;
};

template<typename T, typename ContainerType>
class ContainerStackStrategy : public StackStrategy<T> {
private:
    ContainerType container;
    
public:
    bool empty() const override {
        return container.empty();
    }
    
    size_t size() const override {
        return container.size();
    }
    
    void push(const T& x) override {
        container.push_back(x);
    }
    
    void pop() override {
        if (empty()) {
            throw StackException("Stack is empty - cannot pop");
        }
        container.pop_back();
    }
    
    T& top() override {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return container.back();
    }
    
    const T& top() const override {
        if (empty()) {
            throw StackException("Stack is empty - cannot access top");
        }
        return container.back();
    }
    
    void clear() override {
        container.clear();
    }
    
    StackStrategy<T>* clone() const override {
        return new ContainerStackStrategy<T, ContainerType>(*this);
    }
};

template<typename T>
class Stack {
private:
    std::unique_ptr<StackStrategy<T>> strategy;
    
public:
    Stack() : strategy(new ContainerStackStrategy<T, Vector<T>>()) {}
    
    Stack(StackStrategy<T>* strat) : strategy(strat) {}
    
    Stack(const Stack& other) : strategy(other.strategy->clone()) {}
    
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            strategy.reset(other.strategy->clone());
        }
        return *this;
    }
    
    bool empty() const {
        return strategy->empty();
    }
    
    size_t size() const {
        return strategy->size();
    }
    
    void push(const T& x) {
        strategy->push(x);
    }
    
    void pop() {
        strategy->pop();
    }
    
    T& top() {
        return strategy->top();
    }
    
    const T& top() const {
        return strategy->top();
    }
    
    void clear() {
        strategy->clear();
    }
    
    void setStrategy(StackStrategy<T>* newStrategy) {
        strategy.reset(newStrategy);
    }
};

#endif // STACK_STRATEGY_H
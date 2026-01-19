#ifndef STACK_EXCEPTION_H
#define STACK_EXCEPTION_H

#include <stdexcept>

class StackException : public std::exception {
private:
    const char* message;
    
public:
    StackException(const char* msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message;
    }
};

#endif // STACK_EXCEPTION_H
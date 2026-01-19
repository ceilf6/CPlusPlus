#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdexcept>
#include <cstddef>

class ContainerException : public std::exception
{
private:
    const char *message;

public:
    ContainerException(const char *msg) : message(msg) {}

    virtual const char *what() const noexcept override
    {
        return message;
    }
};

template <typename T>
class Container
{
public:
    virtual ~Container() {}
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual T &element(size_t i) = 0;
    virtual const T &element(size_t i) const = 0;
    virtual void push_back(const T &x) = 0;
    virtual void pop_back() = 0;
    virtual void clear() = 0;

    T &front()
    {
        if (empty())
            throw ContainerException("empty");
        return element(0);
    }

    const T &front() const
    {
        if (empty())
            throw ContainerException("empty");
        return element(0);
    }

    T &back()
    {
        if (empty())
            throw ContainerException("empty");
        return element(size() - 1);
    }

    const T &back() const
    {
        if (empty())
            throw ContainerException("empty");
        return element(size() - 1);
    }
};

#endif // CONTAINER_H

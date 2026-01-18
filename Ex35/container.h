#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <stdexcept>
#include <cstddef>

namespace TD
{

    /* ===== Exception ===== */
    class ContainerException : public std::exception
    {
    protected:
        std::string info;

    public:
        ContainerException(const std::string &i = "") noexcept : info(i) {}
        const char *what() const noexcept override { return info.c_str(); }
    };

    /* ===== Abstract Container ===== */
    template <typename T>
    class Container
    {
    public:
        virtual ~Container() = default;

        // Template methods (fixed algorithm)
        /*
        定义骨架
        */
        size_t size() const { return getSize(); }
        bool empty() const { return size() == 0; }

        T &element(size_t i)
        {
            if (i >= size())
                throw ContainerException("Index out of range");
            return at(i);
        }

        const T &element(size_t i) const
        {
            if (i >= size())
                throw ContainerException("Index out of range");
            return at(i);
        }

        T &front()
        {
            if (empty())
                throw ContainerException("Container empty");
            return at(0);
        }

        const T &front() const
        {
            if (empty())
                throw ContainerException("Container empty");
            return at(0);
        }

        T &back()
        {
            if (empty())
                throw ContainerException("Container empty");
            return at(size() - 1);
        }

        const T &back() const
        {
            if (empty())
                throw ContainerException("Container empty");
            return at(size() - 1);
        }

        void push_back(const T &x) { doPushBack(x); }
        void pop_back()
        {
            if (empty())
                throw ContainerException("Container empty");
            doPopBack();
        }

        void clear() { doClear(); }

    protected:
        // Hook methods (to be implemented by subclasses)
        virtual T &at(size_t i) = 0;
        virtual const T &at(size_t i) const = 0;
        virtual void doPushBack(const T &x) = 0;
        virtual void doPopBack() = 0;
        virtual void doClear() = 0;
        virtual size_t getSize() const = 0;
    };

} // namespace TD

#endif
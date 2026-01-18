#ifndef VECTOR_H
#define VECTOR_H

#include "container.h"
#include <algorithm>

namespace TD
{

    template <typename T>
    class Vector : public Container<T>
    {
    private:
        T *tab;
        size_t sz;
        size_t cap;

        void resize(size_t newCap)
        {
            T *newTab = new T[newCap];
            for (size_t i = 0; i < sz; ++i)
                newTab[i] = tab[i];
            delete[] tab;
            tab = newTab;
            cap = newCap;
        }

    protected:
        T &at(size_t i) override { return tab[i]; }
        const T &at(size_t i) const override { return tab[i]; }
        size_t getSize() const override { return sz; }

        void doPushBack(const T &x) override
        {
            if (sz == cap)
                resize(cap == 0 ? 1 : cap * 2);
            tab[sz++] = x;
        }

        void doPopBack() override { --sz; }

        void doClear() override { sz = 0; }

    public:
        Vector(size_t initialSize = 0, const T &value = T())
            : tab(nullptr), sz(initialSize), cap(initialSize)
        {
            if (cap > 0)
            {
                tab = new T[cap];
                for (size_t i = 0; i < sz; ++i)
                    tab[i] = value;
            }
        }

        ~Vector() { delete[] tab; }

        Vector(const Vector &other)
            : tab(new T[other.cap]), sz(other.sz), cap(other.cap)
        {
            for (size_t i = 0; i < sz; ++i)
                tab[i] = other.tab[i];
        }

        Vector &operator=(const Vector &other)
        {
            if (this != &other)
            {
                delete[] tab;
                cap = other.cap;
                sz = other.sz;
                tab = new T[cap];
                /*
                深拷贝
                */
                for (size_t i = 0; i < sz; ++i)
                    tab[i] = other.tab[i];
            }
            return *this;
        }

        T &operator[](size_t i) { return this->element(i); }
        const T &operator[](size_t i) const { return this->element(i); }
    };

} // namespace TD

#endif
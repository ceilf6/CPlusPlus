#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "vector.h"

using namespace TD;

namespace AO
{
    // 对象适配器
    template <class T, class CONT = Vector<T>>
    class Stack
    {
        CONT cont;

    public:
        class iterator
        {
            // 类型：我们进行组合的容器的迭代器类型
            typename CONT::iterator courant;

        public:
            iterator() : courant() {}
            iterator(typename CONT::iterator c) : courant(c) {}
            iterator &operator++()
            {
                courant++;
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                courant++;
                return tmp;
            }
            bool operator==(const iterator &it) const { return courant == it.courant; }
            bool operator!=(const iterator &it) const { return courant != it.courant; }
            T &operator*() const { return *courant; }
        };

        iterator begin() { return iterator(cont.begin()); }
        iterator end() { return iterator(cont.end()); }

        class const_iterator
        {
            // 类型：我们进行组合的容器的迭代器类型
            typename CONT::const_iterator courant;

        public:
            const_iterator() : courant() {}
            const_iterator(typename CONT::const_iterator c) : courant(c) {}
            const_iterator &operator++()
            {
                courant++;
                return *this;
            }
            const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                courant++;
                return tmp;
            }
            bool operator==(const const_iterator &it) const { return courant == it.courant; }
            bool operator!=(const const_iterator &it) const { return courant != it.courant; }
            const T &operator*() const { return *courant; }
        };

        const_iterator cbegin() const { return const_iterator(cont.cbegin()); }
        const_iterator cend() const { return const_iterator(cont.cend()); }

        Stack() : cont(0) {}

        void push(const T &x) { cont.push_back(x); }
        void pop() { cont.pop_back(); }

        const T &top() const { return cont.back(); }
        T &top() { return cont.back(); }

        bool empty() const { return cont.empty(); }
        void clear() { cont.clear(); }

        // 使用迭代器计算大于x的元素个数
        unsigned int countGreaterThan(const T &x) const
        {
            unsigned int count = 0;
            // 使用const_iterator遍历容器
            for (const_iterator it = cbegin(); it != cend(); ++it)
            {
                if (*it > x)
                {
                    count++;
                }
            }
            return count;
        }
    };
}

namespace AC
{ // 类适配器
    template <class T, class CONT = Vector<T>>
    class Stack : private CONT
    {
    public:
        class iterator : public CONT::iterator
        {
            // 类型：我们进行组合的容器的迭代器类型
            typename CONT::iterator courant;

        public:
            iterator() : courant() {}
            iterator(typename CONT::iterator c) : CONT::iterator(c) {}
        };

        iterator begin() { return iterator(CONT::begin()); }
        iterator end() { return iterator(CONT::end()); }

        class const_iterator : public CONT::const_iterator
        {
            // 类型：我们进行组合的容器的迭代器类型
            typename CONT::const_iterator courant;

        public:
            const_iterator() : CONT::const_iterator() {}
            const_iterator(typename CONT::const_iterator c) : courant(c) {}
        };

        const_iterator cbegin() const { return const_iterator(CONT::cbegin()); }
        const_iterator cend() const { return const_iterator(CONT::cend()); }

        Stack() : CONT(0) {}
        void push(const T &x) { CONT::push_back(x); }
        void pop() { CONT::pop_back(); }
        const T &top() const { return CONT::back(); }
        T &top() { return CONT::back(); }
        // bool empty() const { return CONT::empty(); }
        // void clear() { CONT::clear(); }
        using CONT::clear; // 我们获取 CONT 类的 clear 方法
        using CONT::empty; // 我们获取 CONT 类的 empty 方法

        // 使用迭代器计算大于x的元素个数
        unsigned int countGreaterThan(const T &x) const
        {
            unsigned int count = 0;
            // 使用const_iterator遍历容器
            for (const_iterator it = cbegin(); it != cend(); ++it)
            {
                if (*it > x)
                {
                    count++;
                }
            }
            return count;
        }

        // 或者直接 using CONT::countGreaterThan;
    };
}

#endif // STACK_H_INCLUDED
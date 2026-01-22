#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "container.h"

namespace TD
{
    template <class T>
    class Vector : public Container<T>
    {
        T *tab;
        // memory_size : 容器的动态内存大小
        unsigned int memory_size;

    public:
        class iterator
        {
            T *courant;

        public:
            iterator(T *c = 0) : courant(c) {}
            iterator &operator++()
            {
                courant++;
                return *this;
            } // 前缀一元运算符
            iterator operator++(int)
            {
                iterator tmp = *this;
                courant++;
                return tmp;
            } // 后缀一元运算符
            bool operator==(const iterator &it) const { return courant == it.courant; }
            bool operator!=(const iterator &it) const { return courant != it.courant; }
            T &operator*() const { return *courant; }
        };

        iterator begin() { return iterator(tab); }
        iterator end() { return iterator(tab + Container<T>::nb); }

        class const_iterator
        {
            const T *courant;

        public:
            const_iterator(const T *c = 0) : courant(c) {}
            const_iterator &operator++()
            {
                courant++;
                return *this;
            } // 前缀一元运算符
            const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                courant++;
                return tmp;
            } // 后缀一元运算符
            bool operator==(const const_iterator &it) const { return courant == it.courant; }
            bool operator!=(const const_iterator &it) const { return courant != it.courant; }
            const T &operator*() const { return *courant; }
        };

        const_iterator cbegin() const { return const_iterator(tab); }
        const_iterator cend() const { return const_iterator(tab + Container<T>::nb); }

        // initialize_with : 用于初始化容器的 "s" 个值的参数（为对象提供构造函数或为原生类型提供值）
        Vector(unsigned int s = 0, const T &initialize_with = T());
        Vector(const Vector<T> &);
        ~Vector();
        Vector<T> &operator=(const Vector<T> &t);

        // 关键字 override：表示我们提供方法的重新定义/定义
        // 重新定义 element 和 push/pop_back 方法（它们在基类 Container 中是纯虚的）
        T &element(unsigned int i) override;
        const T &element(unsigned int i) const override;

        void push_back(const T &x) override;
        void pop_back() override;

        // 添加运算符 [] 以直接访问容器的元素
        T &operator[](unsigned int i) { return tab[i]; }
        const T &operator[](unsigned int i) const { return tab[i]; }
    };
}

template <class T>
TD::Vector<T>::Vector(unsigned int s, const T &initialize_with) : Container<T>(s), tab(new T[s]), memory_size(s)
{
    // initialize_with : 用于初始化容器的 "s" 个值的参数（为对象提供构造函数或为原生类型提供值）
    for (unsigned int i = 0; i < Container<T>::nb; i++)
    {
        tab[i] = initialize_with;
    }
}

template <class T>
TD::Vector<T>::Vector(const TD::Vector<T> &t) : Container<T>(t.nb), tab(new T[t.size()]), memory_size(t.size())
{
    for (unsigned int i = 0; i < Container<T>::nb; i++)
    {
        tab[i] = t.tab[i];
    }
}

template <class T>
TD::Vector<T>::~Vector()
{
    delete[] tab;
}

template <class T>
T &TD::Vector<T>::element(unsigned int i)
{
    // 我们使用作用域解析运算符 Container<T>，因为某些 Container<T> 的特化可能不包含此属性（私有继承或其他）
    // 因此我们在这里与编译器约定只使用始终具有此属性的特化
    if (i < Container<T>::nb)
        return tab[i];
    throw ContainerException("错误 Vector：请求超出范围");
}

template <class T>
const T &TD::Vector<T>::element(unsigned int i) const
{
    if (i < Container<T>::nb)
        return tab[i];
    throw ContainerException("错误 Vector：请求超出范围");
}

// 拷贝赋值运算符
template <class T>
TD::Vector<T> &TD::Vector<T>::operator=(const TD::Vector<T> &t)
{
    if (this != &t)
    {
        T *newtab = new T[t.nb];

        for (unsigned int i = 0; i < t.nb; i++)
        {
            newtab[i] = t.tab[i];
        }

        Container<T>::nb = t.nb;
        memory_size = t.nb;
        T *old = tab;
        tab = newtab;

        delete[] old;
    }
    return *this;
}

// push_back 方法的定义
template <class T>
void TD::Vector<T>::push_back(const T &x)
{
    // 这里我们需要增大 "tab" 的大小
    // 内存扩容
    if (Container<T>::nb == memory_size)
    {
        T *newtab = new T[memory_size + 5];

        for (unsigned int i = 0; i < Container<T>::size(); i++)
        {
            newtab[i] = tab[i];
        }

        T *old = tab;
        memory_size += 5;
        tab = newtab;

        delete[] old;
    }
    tab[Container<T>::nb++] = x;
}

template <class T>
void TD::Vector<T>::pop_back()
{
    if (!this->empty())
    {
        Container<T>::nb--;
    }
    else
        throw ContainerException("错误 Vector :: Vector 为空");
}

#endif // VECTOR_H_INCLUDED
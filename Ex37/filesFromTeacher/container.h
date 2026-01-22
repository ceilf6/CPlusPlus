#ifndef CPP_LO02_CONTAINER_H
#define CPP_LO02_CONTAINER_H

#include <string>
#include <stdexcept>

using namespace std;

namespace TD
{

    class ContainerException : public exception
    {
    protected: // 将 private 替换为 protected
        string info;

    public:
        ContainerException(const string &i = "") noexcept : info(i) {}
        const char *what() const noexcept { return info.c_str(); }
        ~ContainerException() noexcept {}
    };

    template <class T>
    class Container
    {
    protected:
        unsigned int nb; // 容器中的元素数量

    public:
        Container(unsigned int nb) : nb(nb) {}
        virtual ~Container() {}

        // 具体方法（因为我们很可能不需要在之后重新定义！）
        unsigned int size() const { return nb; }
        bool empty() const { return nb == 0; }

        // 纯虚方法（必须重新定义才能得到具体类！）
        virtual T &element(unsigned int i) = 0; // 必须在派生类中重新定义
        virtual const T &element(unsigned int i) const = 0;

        // "简单"虚方法（可以选择是否在之后重新定义...可以保留原始代码...）
        virtual T &front();
        virtual const T &front() const;
        virtual T &back();
        virtual const T &back() const;

        virtual void push_back(const T &x) = 0;
        virtual void pop_back() = 0;

        // 具体方法或简单虚方法：可选！
        void clear()
        {
            while (!empty())
            {
                pop_back();
            }
        }
    };
}

// 我们可以使用 "element" 方法，即使我们还没有定义这个方法，因为我们知道它的行为
// 实际上，我们知道 "element" 方法允许获取位置 i 处元素的引用
template <class T>
T &TD::Container<T>::front()
{
    if (!empty())
        return element(0);
    else
        throw ContainerException("容器为空");
}

template <class T>
const T &TD::Container<T>::front() const
{
    if (!empty())
        return element(0);
    else
        throw ContainerException("容器为空");
}

template <class T>
T &TD::Container<T>::back()
{
    if (!empty())
        return element(nb - 1);
    else
        throw ContainerException("容器为空");
}

template <class T>
const T &TD::Container<T>::back() const
{
    if (!empty())
        return element(nb - 1);
    else
        throw ContainerException("容器为空");
}

#endif // CPP_LO02_CONTAINER_H

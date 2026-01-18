// stack_class_adapter.h
#ifndef STACK_CLASS_ADAPTER_H
#define STACK_CLASS_ADAPTER_H

#include "vector.h"

/*
通过调用 Ex35 容器的公共接口，对其进行适配，从而实现栈语义
*/

namespace TD
{

    template <typename T>
    class Stack : private Vector<T>
    { // 关键：private 继承
        /*
        不想暴露 operator[] 和 element(i)
        只保留 Stack 语义
        */
    public:
        bool empty() const
        {
            return Vector<T>::empty();
        }

        void push(const T &x)
        {
            // 栈：只允许在尾端入栈
            Vector<T>::push_back(x);
        }

        void pop()
        {
            // 栈：只允许在尾端出栈
            Vector<T>::pop_back();
        }

        size_t size() const
        {
            return Vector<T>::size();
        }

        T &top()
        {
            // 栈顶 = 容器尾端元素
            return Vector<T>::back();
        }

        const T &top() const
        {
            return Vector<T>::back();
        }

        void clear()
        {
            Vector<T>::clear();
        }
    };

}

#endif
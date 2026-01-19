#ifndef AGENDA_H
#define AGENDA_H

#include <vector>
#include <memory>
#include <iterator>
#include "evenement.h"

namespace TIME
{

    class Agenda
    {
    private:
        // Prototype 后：Agenda 拥有事件（组合）
        std::vector<std::unique_ptr<Evt>> events;

        Agenda(const Agenda &) = delete;
        Agenda &operator=(const Agenda &) = delete;

    public:
        Agenda() = default;
        ~Agenda() = default;

        // Prototype：加入时 clone
        Agenda &operator<<(const Evt &e);

        // ===== 双向迭代器 =====
        /*
        迭代器模式：
        不暴露 vector 细节，即使将来底层换成数组/队列/树形结构，外部的代码仍然封装成果
        */
        class Iterator
        {
            using VecIt = std::vector<std::unique_ptr<Evt>>::iterator;
            VecIt it;

        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = Evt;
            using reference = Evt &;
            using pointer = Evt *;

            explicit Iterator(VecIt v) : it(v) {}
            reference operator*() const { return *(*it); }
            pointer operator->() const { return it->get(); }

            /*
            it: 真正指向当前元素的迭代器
            this: Iterator* 指向迭代器对象本身
            *this: Iterator& 当前迭代器对象
            */
            Iterator &operator++()
            {
                ++it;
                return *this; // 并不是返回元素而是将迭代器往前
            }
            Iterator operator++(int)
            {
                Iterator tmp(*this); // 拷贝：tmp.it指向原来的位置
                ++(*this);
                return tmp;
            }
            Iterator &operator--()
            {
                --it;
                return *this;
            }
            Iterator operator--(int)
            {
                Iterator tmp(*this);
                --(*this);
                return tmp;
            }

            bool operator==(const Iterator &other) const { return it == other.it; }
            bool operator!=(const Iterator &other) const { return it != other.it; }
        };

        Iterator begin();
        Iterator end();

        void afficher(std::ostream &f = std::cout) const;
    };

} // namespace TIME

#endif

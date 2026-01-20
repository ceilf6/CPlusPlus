#ifndef CPP_EVENEMENT_H
#define CPP_EVENEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "timing.h"

namespace TIME
{
    class Evt
    {
    private:
        std::string sujet;

    public:
        Evt(const std::string &s) : sujet(s) {}

        const std::string &getDescription() const { return sujet; }

        virtual void afficher(std::ostream &f = std::cout) const = 0;
        // 纯虚函数 - 不能被实例化 - 用于规定模版的抽象类
    };

    class EvtPj : public Evt
    {
        Date debut;
        Date fin;

    public:
        EvtPj(const Date &d, const Date &f, const std::string &s) : Evt(s), debut(d), fin(f) {}

        const Date &getDateDebut() const { return debut; }

        const Date &getDateFin() const { return fin; }

        void afficher(std::ostream &f = std::cout) const;
    };

    class Evt1j : public Evt
    {
    private:
        Date date;

    public:
        Evt1j(const Date &d, const std::string &s) : Evt(s), date(d) {}

        const Date &getDate() const { return date; }

        virtual void afficher(std::ostream &f = std::cout) const;
    };

    class Evt1jDur : public Evt1j
    {
    private:
        Horaire debut;
        Duree duree;

    public:
        Evt1jDur(const Date &d, const std::string &s,
                 const Horaire &h, const Duree &t) : Evt1j(d, s), // appel au constructeur de la classe de base
                                                     debut(h), duree(t)
        {
        }

        const Horaire &getHoraire() const { return debut; }

        const Duree &getDuree() const { return duree; }

        void afficher(std::ostream &f = std::cout) const;
    };

    class Rdv : public Evt1jDur
    {
        std::string personne;
        std::string lieu;

    public:
        Rdv(const Date &d, const std::string &s,
            const Horaire &h, const Duree &dur,
            const std::string &p, const std::string &l) : Evt1jDur(d, s, h, dur),
                                                          personne(p), lieu(l) {}

        /*
        C++中this一般指向调用该函数的对象
        这里 = 操作符的重载就是需要将 r 赋值到 this 上
        */
        Rdv &operator=(const Rdv &r) // const 确保 r 不会被修改
        {
            // 可以加一句 if (this != &r)
            Evt1jDur *x = this; // 由于 Rdv 继承自父类 Evt1jDur ，所以向上调整是安全的
            *x = r;             // 只复制父类部分
                                // 上面两句或者通过 Evt1jDur::operator=(r); 显式调用父类赋值（但是这里父类没有实现
            // 复制子类部分
            personne = r.personne;
            lieu = r.lieu;
            return *this; // 返回引用
        }

        Rdv(const Rdv &r) : Evt1jDur(r), personne(r.personne), lieu(r.lieu) {}

        const std::string &getPersonne() const { return personne; }

        const std::string &getLieu() const { return lieu; }

        void afficher(std::ostream &f = std::cout) const;
    };

    class Agenda
    {
        std::vector<Evt *> tab; // 存储事件指针的动态数组：使用指针实现多态、可存储不同类型的事件

    public:
        Agenda() = default;

        virtual ~Agenda()
        {
            for (Evt *evt : tab)
            {
                delete evt;
            }
        }; // 基类的析构都要 virtual

        // 禁止拷贝构造和赋值，防止浅拷贝导致的指针问题
        Agenda(const Agenda &) = delete;
        Agenda &operator=(const Agenda &) = delete;

        // 重载<<添加事件：存储时间的地址
        Agenda &operator<<(Evt &e)
        {
            tab.push_back(&e);
            return *this;
        };

        void afficher(std::ostream &f = std::cout) const
        {
            for (unsigned int i = 0; i < tab.size(); i++)
            {
                tab[i]->afficher(f); // 迭代、调用各自的 afficher
            }
        };
    };
}

std::ostream &operator<<(std::ostream &, const TIME::Evt &);

#endif // CPP_EVENEMENT_H

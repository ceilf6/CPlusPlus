#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <iostream>
#include <string>
#include <memory>
#include "timing.h"

namespace TIME
{

    /* ===== 抽象事件 Evt ===== */
    class Evt
    {
    private:
        std::string sujet;

    public:
        explicit Evt(const std::string &s);
        virtual ~Evt() = default;

        const std::string &getDescription() const;

        // 多态显示
        virtual void afficher(std::ostream &f = std::cout) const = 0;
        /*
        =0 表示这是一个纯虚函数、不能被实例化，所有具体子类都必须实现 afficher()
        const 就是之前说的修饰成员函数的行为约束：函数体内不能修改该类对象的非mutable成员变量
        */

        // Prototype：多态深拷贝
        /*
        通过 virtual clone 复制在运行时，不依赖具体类型，实现多态深拷贝

        必须在基类声明 clone ，因为 Evt 是抽象类，Agenda 只知道 Evt，需要按真实类型复制，这只能通过虚函数完成

        unique_ptr<Evt> 明确了所有权唯一，自动释放避免内存泄漏，表达了是组合关系
        */
        virtual std::unique_ptr<Evt> clone() const = 0;
    };

    // 通用输出（靠 afficher 的虚函数）
    std::ostream &operator<<(std::ostream &os, const Evt &e);

    /* ===== 单日事件 ===== */
    class Evt1j : public Evt
    {
    private:
        Date date;

    public:
        Evt1j(const Date &d, const std::string &s);
        const Date &getDate() const;

        void afficher(std::ostream &f = std::cout) const override;
        std::unique_ptr<Evt> clone() const override;
    };

    /* ===== 单日 + 时长 ===== */
    class Evt1jDur : public Evt1j
    {
    private:
        Horaire debut;
        Duree duree;

    public:
        Evt1jDur(const Date &d, const std::string &s,
                 const Horaire &h, const Duree &du);

        const Horaire &getHoraire() const;
        const Duree &getDuree() const;

        void afficher(std::ostream &f = std::cout) const override;
        std::unique_ptr<Evt> clone() const override;
    };

    /* ===== 会议 ===== */
    class Rdv : public Evt1jDur
    {
    private:
        std::string personnes;
        std::string lieu;

    public:
        Rdv(const Date &d, const std::string &s,
            const Horaire &h, const Duree &du,
            const std::string &pers, const std::string &l);

        void afficher(std::ostream &f = std::cout) const override;
        std::unique_ptr<Evt> clone() const override;
    };

    /* ===== 多日事件 ===== */
    class EvtPj : public Evt
    {
    private:
        Date debut;
        Date fin;

    public:
        EvtPj(const Date &d1, const Date &d2, const std::string &s);

        void afficher(std::ostream &f = std::cout) const override;
        std::unique_ptr<Evt> clone() const override;
    };

} // namespace TIME

#endif

#include "log.h"
#include "agenda.h"
/*
一种方案是用对象适配器
MyLog 内部持有一个 Agenda 对象，把 Log 接口转接为 Agenda 的能力
*/
class MyLog : public Log
{
private:
    TIME::Agenda agenda;
    TIME::Date lastDate;
    TIME::Horaire lastHoraire;
    bool hasLast = false;

public:
    void addEvt(
        const TIME::Date &d,
        const TIME::Horaire &h,
        const std::string &s) override;

    void displayLog(std::ostream &f) const override;
};

/*
第二种方案是用类适配器
*/
class MyLog : public Log, public TIME::Agenda
{
private:
    TIME::Date lastDate;
    TIME::Horaire lastHoraire;
    bool hasLast = false;

public:
    void addEvt(
        const TIME::Date &d,
        const TIME::Horaire &h,
        const std::string &s) override;

    void displayLog(std::ostream &f) const override
    {
        afficher(f);
    }
};
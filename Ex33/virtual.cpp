/*
第二种方法是直接在基类 Evt 中添加接口

class Evt {
public:
    virtual ~Evt() = default;

    virtual const char* typeName() const = 0;
    virtual void afficher(std::ostream&) const = 0;
};

每个派生类实现自己的类型名
class Rdv : public Evt {
public:
    const char* typeName() const override {
        return "Rdv";
    }
};

class Evt1j : public Evt {
public:
    const char* typeName() const override {
        return "Evt1j";
    }
};

class EvtPj : public Evt {
public:
    const char* typeName() const override {
        return "EvtPj";
    }
};
*/
#include <map>
#include <string>
#include <iostream>

void Agenda::statistiques(std::ostream &out) const
{
    std::map<std::string, int> compteur;

    for (const auto &evt : events)
    {
        compteur[evt->typeName()]++;
    }

    out << "=== Statistiques (typeName) ===\n";
    for (const auto &[name, count] : compteur)
    {
        out << name << " : " << count << '\n';
    }
}
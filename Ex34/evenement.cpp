#include <sstream>
#include "evenement.h"

Evt::Evt(const std::string &s) : sujet(s) {}

void Evt::afficher(std::ostream &f) const
{
    // 模板方法：统一显示流程
    f << toString() << std::endl;
}

/*
细节延迟给子类 - 在每个具体类中具体分析实现 toString()
*/
std::string Evt1j::toString() const
{
    std::stringstream ss;
    ss << "[Evt1j] " << date << " : " << sujet;
    return ss.str();
}
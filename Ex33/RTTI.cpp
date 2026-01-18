#include <map>
#include <typeindex>
#include <iostream>

void Agenda::statistiques(std::ostream &out) const
{
    std::map<std::type_index, int> compteur;

    for (const auto &evt : events)
    {
        // evt 是 unique_ptr<Evt>
        /*
        对每个事件取运行时类型信息 typeid 得到 std::type_info 类型
        然后用 std::type_index 将其包装成可作为容器key的类型，取变量名为 ti
        */
        std::type_index ti(typeid(*evt));
        compteur[ti]++;
        // 用于 map 统计
    }

    out << "=== Statistiques (RTTI) ===\n";
    for (const auto &[type, count] : compteur)
    {
        out << type.name() << " : " << count << '\n';
    }
}
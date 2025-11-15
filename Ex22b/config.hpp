#ifndef SET_CONFIG_H
#define SET_CONFIG_H

#include <cstddef>

/*
之前老师的代码是直接在类中将卡牌以及卡牌配置等的数量通过数字配置
如果后期代码要拓展的话就需要一个个去找出更换
所以最好的做法就是开一个配置文件去统一管理
我现在只替换了 config::NB_CARTES ，还是先不大改老师的代码，大家能体会到这种统一数据管理模式就好
*/

namespace config
{
    constexpr size_t NB_CARTES = 81;
    constexpr size_t NB_COULEURS = 3;
    constexpr size_t NB_NOMBRES = 3;
    constexpr size_t NB_FORMES = 3;
    constexpr size_t NB_REMPLISSAGES = 3;
}

#endif
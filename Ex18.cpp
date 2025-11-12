#include <string>
#include <iostream>
struct compte
{
    std::string id;
    int solde;
};

// 注意函数得返回引用 & 否则后续不能对返回进行操作
int &operation(struct compte *p, std::string id, int n)
{
    for (int i = 0; i < n; i++) // 题目要求，否则用 map + contains 判断更快
        if (p[i].id == id)
            return p[i].solde; // 当函数签名有 & 时返回数组[i]是直接返回的引用
                               // 函数内部不需要操作，直接返回就好

    throw std::runtime_error("Not found!");
};

int main()
{
    compte tab[4] = {{"courant", 0}, {"codevi", 1500}, {"epargne", 200}, {"cel", 300}};
    std::cout << "== 操作前各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    operation(tab, "courant", 4) = 100; // courant 账户余额设为 100
    operation(tab, "codevi", 4) += 100; // codevi 账户余额 +100
    operation(tab, "cel", 4) -= 50;     // cel 账户余额 -50

    std::cout << "\n== 操作后各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    std::cout << "\n== 尝试不存在的key ==\n";
    operation(tab, "ceilf6", 4) += 10000;
    std::cout << "\n== 操作后各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    return 0;
}
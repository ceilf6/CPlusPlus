#include <string>
#include <iostream>

// 题目要求在 16 的基础上用更优雅的 string，且我进一步用 16 中提到的内置函数写法，如果不习惯的只需要将 16 中的 char 都替换为 std::string 即可，同时不需要循环赋值字符串、直接 = 即可,以及字符串的清除 clear() API

struct personne
{
    std::string nom;
    unsigned int age;

    // 默认构造 + 带参构造
    personne(const std::string &name = "", unsigned int a = 0)
        : nom(name), age(a) {}

    // 清空
    void raz()
    {
        nom.clear(); //
        age = 0;
    }

    // 输出自身信息
    void affiche() const
    {
        std::cout << "Nom : " << nom << ", Age : " << age << std::endl;
    }
};

// 打印数组
void affiche_tab(const personne *p, int n)
{
    for (int i = 0; i < n; i++)
        p[i].affiche();
}

// 复制数组
void copy_tab(const personne *src, personne *dest, int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main()
{
    personne a("Alice", 20);
    personne b("Bob", 25);

    std::cout << "== constructeur + affiche ==\n";
    a.affiche();
    b.affiche();

    std::cout << "\n== raz ==\n";
    a.raz();
    a.affiche();

    personne tab1[2] = {personne("Charlie", 22), personne("David", 30)};
    personne tab2[2];

    std::cout << "\n== affiche_tab ==\n";
    affiche_tab(tab1, 2);

    std::cout << "\n== copy_tab ==\n";
    copy_tab(tab1, tab2, 2);
    affiche_tab(tab2, 2);

    return 0;
}
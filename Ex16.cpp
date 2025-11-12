#include <stdio.h>
#include <iostream> // 性能比stdio更佳但是格式化比较麻烦
struct personne
{
    char nom[30];
    unsigned int age;
};

void raz(struct personne *p)
{
    p->nom[0] = '\0'; // 直接在字符串数组第一个设置终止符号即可优雅清空
    p->age = 0;
}

void affiche_struct(const struct personne *p)
{
    // if (p->nom[0] != '\0')
    // {
    printf("Nom : %s, Age : %u\n", p->nom, p->age);
    // }
    // else
    // {
    //     printf("Nom : Null, Age : %u\n", p->age);
    // }
}

void affiche_tab(const struct personne *p, int n = -1) // 传p[]会自动退化为指向首元素的指针
{
    if (n == -1)
    {
        // n = sizeof(*p); 这样拿到的只是首元素的大小，C++无法推测数组的结束（除非用 vector 或者有标识符）
        std::cout << "请传入数组长度" << std::endl;
    }
    for (int i = 0; i < n; i++)
    {
        affiche_struct(&p[i]);
    }
}

// 这个函数也可以直接写在 struct 里面作为构造函数（函数名必须要和结构体名相同，而且注意设置默认值）
void init_struct(struct personne *p, const char *name, unsigned int age)
{
    // 题目要求不能用 strcpy 函数，且字符串是用 char[] 就只能一个个循环过去迁移
    int i = 0;
    while (name[i] != '\0' && i < 29)
    {
        p->nom[i] = name[i];
        i++;
    }
    p->nom[i] = '\0';
    p->age = age;
}

void copy_struct(const struct personne *src, struct personne *dest)
{
    // 由于用的 char[] 所以得解构赋值，string 的话直接 = 即可
    int i = 0;
    while (src->nom[i] != '\0' && i < 29)
    {
        dest->nom[i] = src->nom[i];
        i++;
    }
    dest->nom[i] = '\0';
    dest->age = src->age;
}

void copy_tab(const struct personne *src, struct personne *dest, int n)
{
    for (int i = 0; i < n; i++)
    {
        copy_struct(&src[i], &dest[i]);
    }
}

int main()
{
    struct personne a, b;
    struct personne tab1[2];
    struct personne tab2[2];

    init_struct(&a, "Alice", 20);
    init_struct(&b, "Bob", 25);

    printf("== init_struct + affiche_struct ==\n");
    affiche_struct(&a);
    affiche_struct(&b);

    printf("\n== raz ==\n");
    raz(&a);
    affiche_struct(&a);

    init_struct(&tab1[0], "Charlie", 22);
    init_struct(&tab1[1], "David", 30);

    printf("\n== affiche_tab ==\n");
    affiche_tab(tab1, 2);

    printf("\n== copy_tab ==\n");
    copy_tab(tab1, tab2, 2);
    affiche_tab(tab2, 2);
}
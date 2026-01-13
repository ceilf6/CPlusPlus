#include "SommaireCard.h"
#include "Button.h"

int main()
{
    SommaireCard *sommaire = new SommaireCard();
    Card *c1 = new Card();
    Card *c2 = new Card();

    // 双向线性结构
    sommaire->setNext(c1);
    c1->setPrevious(sommaire);
    c1->setNext(c2);
    c2->setPrevious(c1);

    // 目录卡知道章节
    sommaire->addChapitre(c1);
    sommaire->addChapitre(c2);

    // 按钮
    sommaire->addWidget(new Button("chapitre1", sommaire));
    sommaire->addWidget(new Button("chapitre2", sommaire));

    c1->addWidget(new Button("precedent", c1));
    c1->addWidget(new Button("suivant", c1));

    c2->addWidget(new Button("precedent", c2));

    // 测试
    sommaire->afficher();
    sommaire->handleClick("chapitre1");
    c1->handleClick("suivant");

    delete sommaire;
    delete c1;
    delete c2;

    return 0;
}
#include "oop.h"

using namespace std;

namespace oop
{
    initializer_list<Attribute1> Attribute1s = {Attribute1::enum1, Attribute1::enum2};
    initializer_list<Attribute2> Attribute2s = {Attribute2::enum1, Attribute2::enum2};

    string toString(Attribute1 att1)
    {
        switch (att1)
        {
        case Attribute1::enum1:
            return "enum1";
        case Attribute1::enum2:
            return "enum2";
        }
    }
    // out-stream
    ostream &operator<<(ostream &f, Attribute1 att1)
    {
        f << toString(att1);
        return f;
    }

    bool Entity2::isPaired() const
    {
        return relatedEntity->getAtt1() == att1;
    }

    bool Entity3::anyPaired() const
    {
        for (size_t i = 0; i < NbEntities1; i++)
        {
            if (entities1[i]->getAtt2() == att2)
            {
                return true;
            }
        }
        return false;
    }

    // 组合关系：管理类拥有实体：构建时创建实体数组，析构时销毁实体数组
    EntityManager::EntityManager()
    {
        size_t index = 0;
        for (auto att1 : Attribute1s)
            for (auto att2 : Attribute2s)
                Entities[index++] = new Entity1(att1, att2); // new返回的指针
    }
    EntityManager::~EntityManager()
    {
        for (size_t i = 0; i < oop::NbEntity1; i++)
            delete Entities[i];
    }
    const Entity1 &EntityManager::getEntity1(size_t index) const
    {
        if (index >= NbEntity1)
            throw SetException("Entity iexistante");
        return *Entities[index];
    }

    // 动态管理
    void Dynamic::add(const Entity1 &ent1)
    {
        if (nb == nbMax)
        {
            const Entity1 **newArray = new const Entity1 *[nbMax + 5];
            for (size_t i = 0; i < nb; i++)
                newArray[i] = entities[i];
            const Entity1 **old = entities;
            delete[] old;
            entities = newArray;
            nbMax += 5;
        }
        entities[nb] = &ent1;
        nb++;
    };
    void Dynamic::rem(const Entity1 &ent1)
    {
        size_t idx = 0;
        while (idx < nb && entities[idx] != &ent1)
            idx++;
        if (idx == nb)
            throw SetException("this entity does not exist");
        entities[idx] = entities[nb - 1]; // 通过替换值高效删除
        nb--;
    };
    Dynamic::Dynamic(const Dynamic &d) // 通过遍历属性
    {
        entities = new const Entity1 *[d.nbMax];
        nb = d.nb;
        nbMax = d.nbMax;
        for (size_t i = 0; i < d.nb; i++)
            entities[i] = d.entities[i];
    };
    Dynamic &Dynamic::operator=(const Dynamic &d)
    {
        if (this != &d)
        {
            nb = 0;
            for (size_t i = 0; i < d.nb; i++)
                add(*d.entities[i]); // add内部已经更新了nb和nbMax
        }
        return *this;
    }
}
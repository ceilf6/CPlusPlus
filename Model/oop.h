#ifndef OOP_H
#define OOP_H

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

namespace oop
{
    // 注意题目信息：最多实体存储量
    const size_t NbEntity1 = 1024;

    // 异常类维护私有info
    class SetException
    {
        // 私有：信息
    private:
        string info;

        // 暴露：setter 和 getter
    public:
        SetException(const string &infomation) : info(infomation) {}
        string getInfo() const { return info; }
    };

    // 属性枚举
    enum class Attribute1
    {
        enum1,
        enum2,
    };
    enum class Attribute2
    {
        enum1,
        enum2,
    };
    string toString(Attribute1 att1);
    string toString(Attribute2 att2);
    ostream &operator<<(ostream &f, Attribute1 att1);
    ostream &operator<<(ostream &f, Attribute2 att2);
    extern initializer_list<Attribute1> Attribute1s;

    // 业务实体类
    class Entity1
    {
        // 私有: 属性，构造函数(初始化器)，拷贝、赋值、析构函数默认，友元管理类
    private:
        Attribute1 attribute1;
        Attribute2 attribute2;

        Entity1(Attribute1 att1, Attribute2 att2) : attribute1(att1), attribute2(att2) {}
        Entity1(const Entity1 &) = default;
        Entity1 &operator=(const Entity1 &) = default;
        ~Entity1() = default;
        friend class EntityManager;

        // 暴露: 各个属性的getter
    public:
        Attribute1 getAtt1() const { return attribute1; }
        Attribute2 getAtt2() const { return attribute2; }
    };

    // 业务实体类2 - 关联关系 - 拥有指针，但是不是一部分，且不负责生命周期
    class Entity2
    {
    private:
        const Entity1 *relatedEntity;
        const Attribute1 att1;

    public:
        Entity2(const Entity1 *ent1, const Attribute1 attribute1) : relatedEntity(ent1), att1(attribute1) {}

        bool isPaired() const; // 演示一个工厂函数的功能：外面传一个想要的att1，那么生成一个判断ent1实例中att1属性是否为想要的功能函数

        ~Entity2() = default;
    };

    // 业务实体类3 - 聚合关系 - 是一部分，但是不负责其生命周期
    class Entity3
    {
    private:
        const Entity1 **entities1;
        const Attribute2 att2;
        const size_t NbEntities1;

    public:
        Entity3(const Entity1 **ent1s, const Attribute2 attribute2, const size_t Nb) : entities1(ent1s), att2(attribute2), NbEntities1(Nb) {};

        bool anyPaired() const;

        ~Entity3() = default;
    };

    // 实体管理类 - 组合关系 - 拥有实体：构建时创建实体数组，析构时销毁实体数组
    class EntityManager
    {
    private:
        // 私有属性：被管理实体的指针数组
        const Entity1 *Entities[NbEntity1];
        // 要求单例: 删除拷贝函数和赋值运算符，构造私有化，通过静态getter获取唯一实例
        EntityManager(const EntityManager &) = delete;
        EntityManager &operator=(const EntityManager &) = delete;
        EntityManager();
        ~EntityManager(); // 析构函数需要释放管理对象
    public:
        // 暴露：
        // 1. getter - 单例，管理对象，管理对象数
        // 2. 迭代器及其First - 指针版，索引版，const(begin&end)，属性
        static EntityManager &getInstance()
        {
            static EntityManager instance; // 静态存储，不在栈也不在堆上，整个程序生命周期都存在且是同一个
            return instance;
        }
        const Entity1 &getEntity1(size_t index) const;
        size_t getNbEntity1() const { return NbEntity1; }

        class Iterator
        {
            // 私有：当前实体指针，剩余数，构造函数，友元管理类
        private:
            const Entity1 **currentEntity; // 双*拿到对象数组的第一个
            size_t NbLeft;
            Iterator(const Entity1 **ptr, size_t n) : currentEntity(ptr), NbLeft(n) {}
            friend class EntityManager;

            // 暴露：移动，判断完成，当前实体
        public:
            void next()
            {
                currentEntity++;
                NbLeft--;
            }
            bool isDone() const { return NbLeft == 0; }
            const Entity1 &getCurrentItem() const { return **currentEntity; } // 双const保证内部和外部都稳定；双解引用拿到值
        };
        Iterator first()
        {
            const Entity1 **e = &Entities[0]; // 拿第一个实体指针
            return Iterator(e, NbEntity1);
        }

        class IteratorBis
        {
        private:
            EntityManager &instance;
            size_t index;
            IteratorBis(EntityManager &EntityManager, size_t index) : instance(EntityManager), index(index) {}
            friend class EntityManager;

        public:
            void next()
            {
                if (isDone())
                    throw SetException("end of iteration");
                index++;
            }
            bool isDone() const { return index == instance.getNbEntity1(); }
            const Entity1 &getCurrentItem() const
            {
                if (isDone())
                    throw SetException("end of iteration");
                return instance.getEntity1(index);
            }
        };
        IteratorBis firstBis() { return IteratorBis(*this, 0); } // 这里的this就是指向当前Manager的指针

        class const_Iterator
        {
        private:
            const EntityManager &instance;
            size_t index;
            const_Iterator(const EntityManager &EntityManager, size_t index) : instance(EntityManager), index(index) {}
            friend class EntityManager;

        public:
            void operator++() { index++; }
            bool operator!=(const_Iterator other) { return index != other.index; }
            const Entity1 &operator*() const { return instance.getEntity1(index); }
        };
        const_Iterator begin() const { return const_Iterator(*this, 0); }
        const_Iterator end() const { return const_Iterator(*this, NbEntity1); }

        class Attribute1Iterator
        {
        private:
            Attribute1 att1;
            EntityManager &instance;
            size_t index;
            Attribute1Iterator(Attribute1 att1Want, EntityManager &EntityManager, size_t index) : att1(att1Want), instance(EntityManager), index(index) {}
            friend class EntityManager;

        public:
            void next()
            {
                index++;
                while (!isDone() && instance.getEntity1(index).getAtt1() != att1)
                    index++;
            }
            bool isDone() const { return index == instance.getNbEntity1(); }
            const Entity1 &getCurrentItem() const { return instance.getEntity1(index); }
        };
        Attribute1Iterator firstAttribute1(Attribute1 att1W) { return Attribute1Iterator(att1W, *this, 0); }
    };

    // 可扩容管理类 - 组合关系
    class Dynamic
    {
    private:
        const Entity1 **entities;
        size_t nbMax; // 数组最大容量
        size_t nb;    // 已用容量

    public:
        Dynamic()
        {
            entities = new const Entity1 *[5];
            nbMax = 5;
            nb = 0;
        }
        Dynamic(const Dynamic &d);
        ~Dynamic() { delete[] entities; }
        Dynamic &operator=(const Dynamic &d);
        size_t getNbEntities() const { return nb; }
        void add(const Entity1 &ent1);
        void rem(const Entity1 &ent1);
    };
}

#endif
# **医院就诊管理系统（Hospital / Appointment Scheduling）**

**期中复习题**

允许：课程 PPT 打印版本
禁止：练习册
禁止：使用 STL（string、iostream 除外）

---

# **题目背景**

本题描述一个用 C++ 开发的医院就诊管理系统，用于操控与分析医院中所有患者的就诊预约情况。

---

# **重要说明（务必阅读）**

* 所有要求实现的类、模块，必须完整定义所有必要的函数、方法与控制逻辑。
* 除 `string` 与 `iostream` 外，不允许使用 STL 容器。若需要存储对象集合，必须自行设计数组或动态数组，并正确管理内存。
* 本题代码结构分为 `hospital.h` 与 `hospital.cpp`。
  若题目要求提供 C++ 代码，必须标注该代码应写入哪个文件。
* 先通读全题再作答。

---

# **系统中的对象**

医院中的就诊信息涉及五类对象：

* **Doctor**：表示某一位医生
* **AppointmentSlot**：表示某一项医疗活动的时间段
* **Patient**：表示一名患者
* **Room**：表示医疗活动的房间地点
* **HospitalManager**：管理系统中所有对象的生命周期

为符合封装原则，所有类的属性应设置为私有，通过访问器 getter 访问。

---

# **类定义说明**

## **Doctor 类**

每位医生使用唯一的字符串代码标识（例如 `"CARD001"`）。
类提供只读访问器：

```
string getCode() const;
```

---

## **AppointmentSlot 类**

一个预约时段代表某一项医疗活动，具有以下属性：

* `doctor`：`const Doctor*`
  表示执行该活动的医生。

* `title`：`string`
  用于表示预约名称，例如 "Consultation"、"Follow-up"。

* `startTime`：`Horaire`
  表示开始时间（假设已实现，不需开发）。

* `duration`：`Duree`
  表示持续时间（假设已实现，不需开发）。

* `room`：`const Room*`
  表示活动发生的房间。

构造函数以五个 `const` 引用作参数，并提供五个属性的只读访问器。

---

## **Room 类**

房间具有以下属性：

* `code`：`string`
* `capacity`：`size_t`

---

## **Patient 类**

每位患者由以下属性描述：

1. **患者编号：**

   * `id`：`string`

2. **登记医生**

   * `doctors`：`const Doctor* [8]`
     患者最多可登记 **8 位医生**。
   * `nbDoctors`：记录已登记医生数量。

3. **预约记录**

   * `appointments`：`const AppointmentSlot**`（动态数组）
   * `nbAppointmentMax`：当前已分配的数组大小
   * `nbAppointment`：实际已预约的数量

---

## **运算符 << 的重写**


---

## **Patient 的其他要求**

* **构造函数：**
  唯一构造函数，接受 `const string&` 作为患者编号。
  初始无登记医生，也无任何预约。

* **复制机制：**
  患者对象可被复制构造或赋值，复制结果应拥有相同的医生登记与预约记录（深拷贝、独立存储）。

* **禁止 string → Patient 的隐式转换。**

---

## **HospitalManager 类**

系统中所有的：

* Doctor
* Room
* AppointmentSlot

均由 `HospitalManager` 负责构建与销毁，避免出现重复或悬空指针。

Patient 不由 Manager 管理。

此外，系统中必须 **只存在一个唯一的 HospitalManager 对象**。

---

# **第一部分 **


1. 是否需要为 某个类 定义析构函数？请说明理由。
就是看这个类是否管理了其他类的数组等等外部资源
Faut-il définir un destructeur pour la classe A ? Veuillez expliquer la raison.
Oui(Non). Il est nécessaire de libérer les ressources qu’elle gère lors de la destruction de A, prévention des fuites de mémoire, comme(mais) la classe A (ne)gère(pas) un tableau d’instances de la classe B.

2. 为满足题目中的所有约束，某个类 的构造函数及（必要时的）析构函数应具备哪些特点？这些特点将如何体现到代码中？
一般是问管理类：构造阶段需要创建管理数组，析构函数需要清空管理资源；同时为了单例模式需要将构造函数私有化
La classe A possède un tableau d’objets Entity1 et en gère la durée de vie.
Le constructeur(构造) alloue les objets avec new, et le destructeur(析构) les libère avec delete pour éviter les fuites de mémoire.
De plus, pour garantir le pattern Singleton, le constructeur doit être privé.
```
EntityManager::EntityManager()
{
    size_t index = 0;
    for (auto att1 : Attribute1s)
        for (auto att2 : Attribute2s)
            Entities[index++] = new Entity1(att1, att2);
}
EntityManager::~EntityManager()
{
    for (size_t i = 0; i < oop::NbEntity1; i++)
    {
        delete Entities[i];
    }
}
```

3. 如何禁止 类A 的复制构造与赋值操作？ Comment interdire le constructeur de copie et l’opérateur d’assignation de la classe A ?
A(const A &) = delete;
A &operator=(const A&) = delete;

4. 画出 某个类 类的完整 UML。
```
+--------------------------------------+
|           HospitalManager            |
+--------------------------------------+
| - doctors: Doctor**                 |
| - rooms: Room**                     |
| - slots: AppointmentSlot**          |
|                                      |
+--------------------------------------+
| + getInstance(): HospitalManager&    |
| + getDoctor(size_t): const Doctor&   |
| - HospitalManager()                  |
| - ~HospitalManager()                 |
| - HospitalManager(const&)=delete     |
| - operator=(const&)=delete           |
+--------------------------------------+

HospitalManager ◆───* Doctor
HospitalManager ◆───* Room
HospitalManager ◆───* AppointmentSlot
```

5. 实现 某个类 类及其必要函数。
参照 EntityManager 实现，但是 HospitalManager 的实体更多，且内部存在关联关系
```
class HospitalManager
{
private:
    Doctor **doctors;
    size_t nbDoctors;

    Room **rooms;
    size_t nbRooms;

    AppointmentSlot **slots;
    size_t nbSlots;

    HospitalManager();
    ~HospitalManager();

    HospitalManager(const HospitalManager&) = delete;
    HospitalManager& operator=(const HospitalManager&) = delete;

public:
    static HospitalManager& getInstance()
    {
        static HospitalManager instance;
        return instance;
    }

    const Doctor& getDoctor(size_t index) const;
    const Room& getRoom(size_t index) const;
    const AppointmentSlot& getSlot(size_t index) const;

    size_t getNbDoctors() const { return nbDoctors; }
    size_t getNbRooms() const { return nbRooms; }
    size_t getNbSlots() const { return nbSlots; }
};
```

6. 画出本题所有类之间的 UML 结构图（只需包括类之间的关联关系与多重性），并清楚说明每个关联的理由。
```
HospitalManager  ◆───────────────* Doctor
HospitalManager  ◆───────────────* Room
HospitalManager  ◆───────────────* AppointmentSlot

AppointmentSlot ────────────────1──────> Doctor
AppointmentSlot ────────────────1──────> Room

Patient ───────────────0..8────────────> Doctor
Patient ───────────────  * ────────────> AppointmentSlot
```
类A负责类B的生命周期，所以A拥有B，是组合关系
La classe HospitalManager est responsable de la durée de vie de la classe Doctor, Room et AppointmentSlot: il s’agit d’une relation de composition.

类A只保存类B的指针/引用，不负责类B的生命周期，所以他们是关联关系
La classe A référence la classe B au moyen de pointeurs / références, sans en gérer la durée de vie ; il s’agit donc d’une association.

类A拥有类B，语义上B是A的一部分，但是不负责类B的生命周期，所以他们是聚合关系
La classe A agrège des objets de la classe B, mais elle n’en gère pas la durée de vie ; il s’agit donc d’une relation d’agrégation.

---

# **第二部分 **

1. 若你未更换考卷，请解释原因并估计扣分（若已更换，此题可忽略）。 // 没看懂这什么意思
2. 定义一个简单的异常类，用于处理患者登记与预约时的错误情况。
参照Model的 SetException 类
```
    class SetException
    {
    private:
        string info;

    public:
        SetException(const string &infomation) : info(infomation) {}
        string getInfo() const { return info; }
    };
```

5. 假设 `f()` 函数中可能抛出多种异常 (e1, e2, e3)，请写一段代码捕获所有可能类型的异常并处理之。
```
try {
    f();
}
catch (const e1 &err) {
    cout << "exception e1: " << err.getInfo() << endl;
}
catch (const e2 &err) {
    cout << "exception e2: " << err.getInfo() << endl;
}
catch (const e3 &err) {
    cout << "exception e3: " << err.getInfo() << endl;
}
catch (...) {
    cout << "unknown exception" << endl;
}
```

3. 分别说明 某个类 是否需要：
   * 析构函数
   * 复制构造函数
   * 赋值操作符
     并解释原因与应执行的动作。
// 类似于第一部分

4. 按照所有功能与约束，实现 某个类 类的完整定义。
// 参照 oop.hpp 和 oop.cpp

6. 如何确保整个系统中只有一个 某个类 实例？请清楚说明理由。
单例模式：删除拷贝函数和赋值运算符，构造私有化，通过静态getter获取唯一实例
```
Pour garantir qu'il n'existe qu'une seule instance dans tout le système :
- le constructeur est privé pour empêcher toute création externe ;
- une instance unique est stockée sous forme d'objet statique et récupérée via getInstance() (méthode statique) ;
- le constructeur de copie et l’opérateur d’assignation sont supprimés (=delete) pour éviter toute duplication ;
Ainsi, la classe ne peut avoir qu’une seule instance durant toute l’exécution du programme : c’est le pattern Singleton.
```

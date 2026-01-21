1. S - Single 单一职责原则
一个类应该只有一个引起它变化的原因 - 一个类只和一件事绑定
```
class User {
public:
    void doA();
    void doB();
}

// 这是不好的

class User {
public:
    std::string name;
}

class UserA {
public:
    void doA(const User& user);
}

class UserB {
public:
    void print(const User& user);
}
```


2. Open 开闭原则
open to extention, close to modification
增加功能时，尽量新增代码，而不是修改旧代码
```
class Shape {
public:
    enum Type { Circle, Rectangle } type;
};
```
=>
```
class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    double radius;
    double area() const override {
        return 3.14 * radius * radius;
    }
};
```
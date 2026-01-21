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
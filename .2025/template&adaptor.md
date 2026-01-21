模版模式一般是
```
class Base {
public:
    void run() {
        step1();
        step2();
        step3();
    }

protected:
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() = 0;
};
```
算法流程定了，具体方法细节没有固定

所以在面对具体问题时，模版类是无法直接作用的，那么一般就需要适配器去作为胶水粘连

那么这种情况下一般适配器都不需要对外展现基类的算法流程，而是只需要向外展示封装之后的 run 
那么这时候只需要 private 继承即可，例如 
```
class Child : private Base {
public:
    void coverRun() {
        Base::run();   // 或直接 run();
    }

protected:
    void step1() override { // 重写虚函数的都写override，报错能在编译器被救
        // 具体实现
    }
    void step2() override {
        // 具体实现
    }
    void step3() override {
        // 具体实现
    }
};
```
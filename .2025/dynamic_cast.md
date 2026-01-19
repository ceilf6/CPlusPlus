1. 向上转型: 派生类向基类转换、使用
Derived* derived = new Derived();
Base* base = derived; // 向上隐式转换，安全，不需要检查

(*base).attributeFromBase(); // 可以
(*base).attributeFromDerived(); // 不可以，base只能看到 Base 的成员

2. 向下转型: 基类向派生类转换、使用
Base* base = getSomeBase();

Derived* derived = dynamic_cast<Derived*>(base); // 向下转换需要检查，因为派生类可能有基类没有的细节
if (derived != nullptr) {
    (*derived).attributeFromDerived();
}
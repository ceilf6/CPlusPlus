# 函数对象

在 C++ 中，**函数对象（Function Object）**，通常也被称为 **Functor**。简单来说，它是一个重载了括号运算符 `operator()` 的类对象。

当你为一个类定义了 `operator()`，这个类的实例就可以像函数一样被“调用”。

---

## 1. 基本语法

函数对象的核心在于定义 `operator()`。它的结构如下：

```cpp
class MyFunctor {
public:
    // 重载括号运算符
    ReturnType operator()(Args... args) const {
        // 实现逻辑
    }
};

```

---

## 2. 参数传递：从 0 个到多个

函数对象非常灵活，括号运算符可以接受任意数量的参数。

### A. 0 个参数（无参）

通常用于生成某种状态值或执行特定的闭包操作。

```cpp
struct Generator {
    int count = 0;
    int operator()() {
        return ++count;
    }
};

Generator gen;
gen(); // 返回 1
gen(); // 返回 2

```

### B. 1 个或多个参数

这是最常见的用法，常用于算法（如 `std::sort` 或 `std::for_each`）中。

```cpp
struct Adder {
    // 两个参数
    int operator()(int a, int b) const {
        return a + b;
    }
};

Adder add;
int sum = add(10, 20); // 像函数一样调用，返回 30

```

---

## 3. 在 STL 中的应用

STL 算法经常使用函数对象作为“谓词（Predicate）”或“操作符”。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct IsGreater {
    int threshold;
    IsGreater(int t) : threshold(t) {}

    // 带 1 个参数的函数对象
    bool operator()(int n) const {
        return n > threshold;
    }
};

int main() {
    std::vector<int> nums = {1, 5, 8, 10, 2};
    // 查找第一个大于 7 的数
    auto it = std::find_if(nums.begin(), nums.end(), IsGreater(7));
    
    if (it != nums.end()) {
        std::cout << "Found: " << *it << std::endl; // 输出 8
    }
}

```

---

## 4. 函数对象 vs Lambda 表达式

在 C++11 之后，**Lambda 表达式**成为了创建匿名函数对象的捷径。

* **Lambda**：`[](int a, int b) { return a + b; }`
* **本质**：编译器会自动为 Lambda 生成一个匿名的结构体，并重载 `operator()`。

所以，当你写一个 Lambda 时，你实际上就是在创建一个临时的函数对象。






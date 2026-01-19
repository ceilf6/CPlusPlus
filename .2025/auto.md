auto 关键词告诉编译器自动推导变量类型，使用时必修初始化，因为编译器需要从初始值推导类型

像迭代器中不使用 auto 很复杂
```
for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
```

使用后就简化很多，提高了代码阅读性
```
for (auto it = vec.begin(); it!=vec.end(); ++it)
```
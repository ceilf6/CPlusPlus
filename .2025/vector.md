vector 容器常用成员函数
1. 初始化
```
vector<int> v1;              // 空 vector
vector<int> v2(5);           // 5 个元素，默认值为 0
vector<int> v3(5, 10);        // 5 个元素，值为 10
vector<int> v4 = {1, 2, 3};   // 初始化列表
```

2. 访问
v[]
.at()
.front()
.back()
.data()

3. 容量
.size()
.capacity()
.empty()

4. 修改
.push_back()
.pop_back()
.insert()
.erase()
.clear()
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <stdexcept>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

/*
C++异常继承树
std::exception
 ├── std::logic_error
 │    ├── invalid_argument
 │    ├── out_of_range
 ├── std::runtime_error
 │    ├── overflow_error
 │    ├── underflow_error
抛异常时用具体类型，捕获时用基类引用
*/
class GraphException : public exception // 继承 std::exception 这样能被 catch(exception&)
{
    string info;

public:
    GraphException(const string &i) noexcept : info(i) {}
    virtual ~GraphException() noexcept {}
    // virtual: 运行时多态 - 这个函数“可能会被子类重写”，调用时不要偷懒，要等运行时再决定 - 调用函数时通过 vtable 查真实函数
    const char *what() const noexcept { return info.c_str(); }
};

class Graph
{
    vector<list<unsigned int>> adj; // adjacency 邻接
    /*
    std::vector 是 STL 中最常用的顺序容器 - 一个动态数组
    内存连续、支持下标访问、能自动扩容

    此处以 list<unsigned int> 作为数组的元素类型
    其中

    std::list 是标准库的双向链表，支持
    push_back() 尾部插入
    push_front() 头部插入
    pop_back() 尾部删除
    pop_front() 头部删除
    insert(it, x) 在it前插入
    size() 元素个数
    */
    string name;

    void checkVertex(unsigned int i) const;

public:
    Graph(const string &n, size_t nb);

    const string &getName() const;
    size_t getNbVertices() const;
    size_t getNbEdges() const;

    void addEdge(unsigned int i, unsigned int j);
    void removeEdge(unsigned int i, unsigned int j);

    const list<unsigned int> &getSuccessors(unsigned int i) const;
    const list<unsigned int> getPredecessors(unsigned int i) const;
};

ostream &operator<<(ostream &f, const Graph &G);

#endif
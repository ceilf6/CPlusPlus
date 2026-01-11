#include "graph.h"
#include <algorithm>
/*
1. find(begin,end,value): 线形查找
    在 [begin,end) 的范围内找第一个等于 value 的元素的下标
2. lower_bound: 二分查找下界 - 第一个不小于的
*/
#include <sstream>

void Graph::checkVertex(unsigned int i) const // 通过 size 判断是否越界
{
    if (i >= adj.size())
    {
        ostringstream oss;
        oss << "GraphException: invalid vertex " << i;
        throw GraphException(oss.str());
    }
}

Graph::Graph(const string &n, size_t nb) : adj(nb), name(n) {}

const string &Graph::getName() const
{
    return name;
}

size_t Graph::getNbVertices() const
{
    return adj.size();
}

size_t Graph::getNbEdges() const
{
    size_t m = 0;
    for (const auto &lst : adj)
        m += lst.size();
    return m;
}

void Graph::addEdge(unsigned int i, unsigned int j)
{
    // 首先检查两点是否越界
    checkVertex(i);
    checkVertex(j);

    auto &lst = adj[i];
    auto it = find(lst.begin(), lst.end(), j); // STL 基于迭代器的封装算法
    if (it != lst.end())                       // 如果不是 end 说明边已经存在
    {
        ostringstream oss;
        oss << "GraphException: edge (" << i << "," << j << ") already exists";
        throw GraphException(oss.str());
    }

    // 保持有序插入（输出更稳定）
    auto pos = lower_bound(lst.begin(), lst.end(), j);
    lst.insert(pos, j);
}

void Graph::removeEdge(unsigned int i, unsigned int j)
{
    // 同样先检查是否越界、边是否已存在（其实 add 和 remove 最好的方法就是用一个高阶工厂函数，将两个函数的差异也就是 insert 和 erase 作为回调函数传进入）
    checkVertex(i);
    checkVertex(j);

    auto &lst = adj[i];
    auto it = find(lst.begin(), lst.end(), j);
    if (it == lst.end())
    {
        ostringstream oss;
        oss << "GraphException: edge (" << i << "," << j << ") does not exist";
        throw GraphException(oss.str());
    }
    lst.erase(it);
}

const list<unsigned int> &Graph::getSuccessors(unsigned int i) const
{
    checkVertex(i);
    return adj[i];
}

const list<unsigned int> Graph::getPredecessors(unsigned int i) const
{
    checkVertex(i);

    list<unsigned int> pred;
    for (unsigned int u = 0; u < adj.size(); ++u)
    {
        const auto &lst = adj[u];
        if (find(lst.begin(), lst.end(), i) != lst.end())
        {
            pred.push_back(u);
        }
    }
    // u 是递增扫描，因此 pred 天然有序
    return pred;
}

ostream &operator<<(ostream &f, const Graph &G)
{
    f << "graph " << G.getName()
      << " (" << G.getNbVertices() << " vertices and "
      << G.getNbEdges() << " edges)\n";

    for (unsigned int i = 0; i < G.getNbVertices(); ++i)
    {
        f << i << ":";
        const auto &s = G.getSuccessors(i);
        for (auto v : s)
            f << " " << v;
        f << "\n";
    }
    return f;
}
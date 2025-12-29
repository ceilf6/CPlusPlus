#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <stdexcept>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class GraphException : public exception
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
    vector<list<unsigned int>> adj;
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
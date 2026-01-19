/*
目前已经用set维护了关系对，但是想要实现一个迭代器，这样不需要接触底层set<pair<A,B>>的迭代器
    set<pair<A,B>>::const_iterator，支持 ++it、*it、it1==it2 等
    =>
    relation<A,B>::iterator 支持 begin(), end()
*/

/*
1. iterator 肯定是 relation 的内部类
2. iterator begin() 和 end() 必须是 const ，因为这两个成员函数不应该修改属性即couples关系
*/

// 1. 类适配器：通过继承来适配
template <class A, class B>
class relation
{
public:
    /*
    由于这道题目希望 relation的iterator 也是支持 STL迭代器的接口 ++, * 等等，所以是需要向外暴露的
        用了 public 而不是 private
    */
    class iterator : public std::set<std::pair<A, B>>::const_iterator
    {
    public:
        iterator(typename std::set<std::pair<A, B>>::const_iterator it = typename std::set<std::pair<A, B>>::const_iterator())
            // 当 T::value_type x 类型名依赖于模板参数 时：对 std::set<std::pair<A, B>>::const_iterator 加 typename 告诉编译器这是一个类型名
            : std::set<std::pair<A, B>>::const_iterator(it)
        {
        }
    };

    iterator begin() const { return iterator(couples.begin()); }
    iterator end() const { return iterator(couples.end()); }

protected:
    std::set<std::pair<A, B>> couples;
};

// 2. 对象适配器：不继承，而是封装， iterator 内部持有基准 const_iterator current
template <class A, class B>
class relation
{
    class iterator
    {
    public:
        iterator &operator++()
        {
            ++current;
            return *this;
        }
        const std::pair<A, B> &operator*() const { return *current; }
        bool operator==(const iterator &other) const { return current == other.current; }
        bool operator!=(const iterator &other) const { return current != other.current; }

        iterator(typename std::set<std::pair<A, B>>::const_iterator it = typename std::set<std::pair<A, B>>::const_iterator())
            : current(it) {}

    private:
        typename std::set<std::pair<A, B>>::const_iterator current;
    };

    iterator begin() const { return iterator(couples.begin()); }
    iterator end() const { return iterator(couples.end()); }
};
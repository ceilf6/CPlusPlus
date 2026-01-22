#ifndef STAT_COLLECTORS_H
#define STAT_COLLECTORS_H

// ===========================
// 抽象统计器
// ===========================
template<class T>
class StatCollector {
public:
    virtual ~StatCollector() = default;
    virtual void process(T* ptr) = 0;
};

// ============================================
// PredicateCounter
// 使用“谓词对象”的统计器
// ============================================
template<class T, class Predicate>
class PredicateCounter : public StatCollector<T> {
    Predicate pred;
    int count;

public:
    PredicateCounter(const Predicate& p)
        : pred(p), count(0) {}

    void process(T* ptr) override {
        if (pred(ptr)) {   // ⭐ 这里正是 operator()
            ++count;
        }
    }

    int getCount() const {
        return count;
    }
};

#endif

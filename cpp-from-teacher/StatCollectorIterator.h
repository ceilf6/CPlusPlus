#ifndef STATCOLLECTORITERATOR_H
#define STATCOLLECTORITERATOR_H

#include <iterator>

template<class CONTAINER>
class StatCollectorIterator {
    CONTAINER& container;
    typename CONTAINER::iterator it;
public:
    StatCollectorIterator(CONTAINER& c)
        : container(c), it(container.begin()) {}

    template<class Collector>
    void run(Collector& col) {
        for (it = container.begin(); it != container.end(); ++it) {
            col.process(*it);
        }
    }

    bool goodbon() const {
        return it != container.end();
    }
};

#endif

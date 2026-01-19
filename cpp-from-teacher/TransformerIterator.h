#ifndef TRANSFORMER_ITERATOR_H
#define TRANSFORMER_ITERATOR_H

#include <string>

template <class CONTAINER, class Transformer>
class TransformerIterator {
private:
    const CONTAINER& container;
    typename CONTAINER::const_iterator current;
    Transformer transformer;

public:
    TransformerIterator(const CONTAINER& c, Transformer t)
        : container(c), current(container.begin()), transformer(t) {}

    void operator++() {
        ++current;
    }

    bool goodbon() const {
        return current != container.end();
    }

    std::string operator*() const {
        return transformer(*current);
    }
};

#endif


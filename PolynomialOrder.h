#ifndef POLYNOMIALORDER_H
#define POLYNOMIALORDER_H

#include "Polynomial.h"

namespace sa {
    template<typename Cmp>
    class PolynomialOrder {
    public:
        template<typename T>
        bool operator()(const Polynomial<T, Cmp> & lhs,
                        const Polynomial<T, Cmp> & rhs) const;
    };
}

#endif

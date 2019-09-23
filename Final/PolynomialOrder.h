#ifndef POLYNOMIALORDER_H
#define POLYNOMIALORDER_H

#include "Polynomial.h"

namespace sa {
    template < typename Cmp >
    class PolynomialOrder {
    public:
        template < typename T >
        bool operator()(const Polynomial < T, Cmp > & lhs,
                        const Polynomial < T, Cmp > & rhs) const;
    };
}

namespace sa {
    template < typename Cmp >
    template < typename T >
    bool PolynomialOrder < Cmp > ::operator()(const Polynomial < T, Cmp > & lhs,
                                              const Polynomial < T, Cmp > & rhs) const {
        Cmp cmp;
        int_f r = std::min(lhs.terms().size(), rhs.terms().size());
        for (int_f i = 0; i != r; ++i) {
            if (cmp(lhs.monomByPos(i), rhs.monomByPos(i)) || cmp(rhs.monomByPos(i), lhs.monomByPos(i))) {
                return cmp(lhs.monomByPos(i), rhs.monomByPos(i));
            }
        }
        return lhs.terms().size() < rhs.terms().size();
    }
}

#endif
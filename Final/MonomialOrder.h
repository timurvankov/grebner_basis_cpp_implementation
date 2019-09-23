#ifndef MONOMIALORDER_H
#define MONOMIALORDER_H

#include "Monomial.h"

namespace sa {
    class lexCmp {
    public:
        template < typename T >
        bool operator()(const Monomial < T > & lhs,
                        const Monomial < T > & rhs) const;
    };

    class degCmp {
    public:
        template < typename T >
        bool operator()(const Monomial < T > & lhs,
                        const Monomial < T > & rhs) const;
    };

    template < typename TFirst, typename TSecond >
    class cmpSum {
    public:
        template < typename T >
        bool operator()(const Monomial < T > & lhs,
                        const Monomial < T > & rhs) const;
    };

    //удобно использовать для хранения объектов по убыванию внутри класса
    template < typename c >
    class inverseCmp {
    public:
        template < typename T >
        bool operator()(const Monomial < T > & lhs,
                        const Monomial < T > & rhs) const;;
    };
}

namespace sa {
    template < typename T >
    bool lexCmp::operator()(const Monomial < T > & lhs,
                            const Monomial < T > & rhs) const {
        int_f r = std::max(lhs.rvar(), rhs.rvar());
        for (int_f i = 0; i <= r; ++i) {
            if (lhs.degreeOfVar(i) != rhs.degreeOfVar(i)) return lhs.degreeOfVar(i) < rhs.degreeOfVar(i);
        }
        return false;
    }

    template < typename T >
    bool degCmp::operator() (const Monomial < T > & lhs,
                            const Monomial < T > & rhs) const {
        return lhs.degree() < rhs.degree();
    }

    template < typename TFirst, typename TSecond >
    template < typename T >
    bool cmpSum < TFirst, TSecond > ::operator()(const Monomial < T > & lhs,
                                                 const Monomial < T > & rhs) const {
        TFirst fcmp;
        TSecond scmp;
        if ((fcmp(lhs, rhs) == 0) && (fcmp(rhs, lhs) == 0)) return scmp(lhs, rhs);
        else return fcmp(lhs, rhs);
    }

    template < typename c >
    template < typename T >
    bool inverseCmp < c > ::operator()(const Monomial < T > & lhs,
                                       const Monomial < T > & rhs) const {
        c cmp;
        if (lhs != rhs) return !cmp(lhs, rhs);
        else return false;
    }
}

#endif
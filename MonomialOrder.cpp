#include "MonomialOrder.h"

namespace sa {
    template<typename T>
    bool lexCmp::operator()(const Monomial<T> &lhs, const Monomial<T> &rhs) const {
        int_f r = std::max(lhs.rvar(), rhs.rvar());
        for (int_f i = 0; i <= r; ++i) {
            if (lhs.degreeOfVar(i) != rhs.degreeOfVar(i)) return lhs.degreeOfVar(i) < rhs.degreeOfVar(i);
        }
        return false;
    }

    template<typename TFirst, typename TSecond>
    template<typename T>
    bool cmpSum<TFirst, TSecond>::operator()(const Monomial<T> &lhs, const Monomial<T> &rhs) const {
        TFirst fcmp;
        TSecond scmp;
        if ((fcmp(lhs, rhs) == 0) && (fcmp(rhs, lhs) == 0)) return scmp(lhs, rhs);
        else return fcmp(lhs, rhs);
    }


    template<typename c>
    template<typename T>
    bool inverseCmp<c>::operator()(const Monomial<T> &lhs, const Monomial<T> &rhs) const {
        c cmp;
        if (lhs != rhs) return !comparator(lhs, rhs);
        else return false;
    }
}
#ifndef MONOMIALORDER_H
#define MONOMIALORDER_H

#include "Monomial.h"

namespace sa {
    class lexCmp {
    public:
        template<typename T>
        bool operator()(const Monomial<T> &lhs,
                        const Monomial<T> &rhs) const;
    };


    template<typename TFirst, typename TSecond>
    class cmpSum {
    public:
        template<typename T>
        bool operator()(const Monomial<T> &lhs,
                        const Monomial<T> &rhs) const;
    };

//удобно использовать для хранения объектов по убыванию внутри класса
    template<typename c>
    class inverseCmp {
    public:
        template<typename T>
        bool operator()(const Monomial<T> &lhs,
                        const Monomial<T> &rhs) const;;
    };
}

#endif

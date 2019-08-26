#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "MonomialOrder.h"

namespace sa {
    template<typename T, typename Cmp>
    class Polynomial {
    public:

        Polynomial() = default;

        explicit Polynomial(Monomial<T> m);

        Polynomial(const Polynomial<T, Cmp> &p);

        explicit Polynomial(const std::set<Monomial<T>, Cmp> &p);

        const Monomial<T> &monomByPos(const int_f &pos) const;

        Polynomial operator-() const;

        Polynomial &operator+=(const Monomial<T> &t);

        Polynomial<T, Cmp> &operator+=(const Polynomial<T, Cmp> &p);

        friend Polynomial<T, Cmp> operator+(Polynomial<T, Cmp> lhs,
                                            const Polynomial<T, Cmp> &p);

        friend Polynomial<T, Cmp> operator+(Polynomial<T, Cmp> lhs,
                                            const Monomial<T> &p);

        Polynomial<T, Cmp> &operator-=(const Polynomial<T, Cmp> &p);

        Polynomial<T, Cmp> &operator-=(const Monomial<T> &t);

        friend Polynomial<T, Cmp> operator-(Polynomial<T, Cmp> lhs,
                                            const Polynomial<T, Cmp> &p);

        Polynomial<T, Cmp> &operator*=(const Monomial<T> &t);

        friend Polynomial<T, Cmp> operator*(Polynomial<T, Cmp> lhs,
                                            const Monomial<T> &t);

        Polynomial<T, Cmp> &operator*=(const Polynomial<T, Cmp> &p);

        friend Polynomial<T, Cmp> operator*(Polynomial<T, Cmp> lhs,
                                            const Polynomial<T, Cmp> &t);

        friend bool operator==(const Polynomial<T, Cmp> &lhs,
                               const Polynomial<T, Cmp> &rhs);

        friend bool operator!=(const Polynomial<T, Cmp> &lhs,
                               const Polynomial<T, Cmp> &rhs);

        friend std::ostream &operator<<(std::ostream &s,
                                        const Polynomial<T, Cmp> &p);

        friend Polynomial<T, Cmp> sPoly(const Polynomial<T, Cmp> &lhs,
                                        const Polynomial<T, Cmp> &rhs);

        bool redStep(const Polynomial &second);

        const std::set<Monomial<T>, sa::inverseCmp<Cmp >> &terms() const;
    private:
        std::set<Monomial<T>, sa::inverseCmp<Cmp >> _terms;
    };
}

#endif

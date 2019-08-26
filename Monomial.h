#ifndef MONOMIAL_H
#define MONOMIAL_H

#include<iostream>
#include<map>
#include<numeric>
#include<set>
#include<unordered_map>
#include<vector>

typedef int_fast64_t int_f;

namespace sa {
    template<typename T>
    class Monomial {
    public:

        Monomial() = default;;

        explicit Monomial(T c);

        Monomial(T c,
                 const std::unordered_map<int_f, int_f> &degrees);

        Monomial(T c,
                 const std::map<int_f, int_f> &degrees);

        Monomial(T c,
                 const std::vector<int_f> &degrees);

        Monomial<T> &operator*=(const Monomial &rhs);

        Monomial<T> &operator*=(T rhs);

        Monomial<T> &operator/=(const Monomial &rhs);

        Monomial<T> &operator/=(T rhs);

        friend std::ostream &operator<<(std::ostream &s,
                                        const Monomial &m);

        friend bool operator==(const Monomial &lhs,
                               const Monomial &rhs);

        friend bool operator!=(const Monomial &lhs,
                               const Monomial &rhs);

        friend Monomial<T> operator*(Monomial lhs,
                                     const Monomial &rhs);

        friend Monomial<T> operator*(Monomial lhs, T rhs);

        friend Monomial<T> operator/(Monomial lhs,
                                     const Monomial &rhs);

        friend Monomial<T> operator/(Monomial lhs, T rhs);

        Monomial<T> operator-() const;

        [[nodiscard]] int_f degreeOfVar(int_f i) const;

        friend Monomial<T> lcm(const Monomial &lhs,
                               const Monomial &rhs);

        [[nodiscard]] bool onlyCoef() const;

        [[nodiscard]] int_f rvar() const;

        bool divWith(const Monomial<T> &d) const;

        void checkZero();

        [[nodiscard]] const std::map<int_f, int_f> &monom() const;

        const T &coef() const;

    private:
        std::map<int_f, int_f> _monom;
        T _coef;
    };
}
#endif

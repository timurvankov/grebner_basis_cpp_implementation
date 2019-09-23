#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "MonomialOrder.h"

namespace sa {
    template < typename T, typename Cmp >
    class Polynomial {
    public:

        Polynomial() =
        default;

        Polynomial(Monomial < T > m);

        template < typename _Cmp >
        Polynomial(const Polynomial < T, _Cmp > & p);

        Polynomial(const std::set < Monomial < T > , Cmp > & p);

        const Monomial < T > & monomByPos(const int_f & pos) const;

        Polynomial operator - () const;

        Polynomial & operator += (const Monomial < T > & t);

        Polynomial < T, Cmp > & operator += (const Polynomial < T, Cmp > & p);

        friend Polynomial < T, Cmp > operator + (Polynomial < T, Cmp > lhs,
                                                 const Polynomial < T, Cmp > & p) {
            lhs += p;
            return lhs;
        }

        friend Polynomial < T, Cmp > operator + (Polynomial < T, Cmp > lhs,
                                                 const Monomial < T > & p) {
            lhs += p;
            return lhs;
        }

        Polynomial < T, Cmp > & operator -= (const Polynomial < T, Cmp > & p);

        Polynomial < T, Cmp > & operator -= (const Monomial < T > & t);

        friend Polynomial < T, Cmp > operator - (Polynomial < T, Cmp > lhs,
                                                 const Polynomial < T, Cmp > & p) {
            lhs += -p;
            return lhs;
        }

        friend Polynomial < T, Cmp > operator - (Polynomial < T, Cmp > lhs,
                                                 const Monomial < T > & p) {
            lhs += -p;
            return lhs;
        }

        Polynomial < T, Cmp > & operator *= (const Monomial < T > & t);

        friend Polynomial < T, Cmp > operator * (Polynomial < T, Cmp > lhs,
                                                 const Monomial < T > & t) {
            lhs *= t;
            return lhs;
        }

        Polynomial < T, Cmp > & operator *= (const Polynomial < T, Cmp > & p);

        friend Polynomial < T, Cmp > operator * (Polynomial < T, Cmp > lhs,
                                                 const Polynomial < T, Cmp > & t) {
            lhs *= t;
            return lhs;
        }

        Polynomial < T, Cmp > & operator /= (T coef);

        friend Polynomial < T, Cmp > operator / (Polynomial < T, Cmp > lhs,
                                                 T t) {
            lhs /= t;
            return lhs;
        }

        friend bool operator == (const Polynomial < T, Cmp > & lhs,
                                 const Polynomial < T, Cmp > & rhs) {
            return lhs._terms == rhs._terms;
        }

        friend bool operator != (const Polynomial < T, Cmp > & lhs,
                                 const Polynomial < T, Cmp > & rhs) {
            return lhs._terms != rhs._terms;
        }

        template <typename _T, typename _Cmp>
        friend std::ostream & operator << (std::ostream & s,
                                           const Polynomial < _T, _Cmp > & p) {
            if (p == Monomial < _T > (0)) {
                s << 0;
                return s;
            }
            for (const auto & t: p._terms) {
                if (t.coef() > 0 && t != p.monomByPos(0)) s << " + ";
                s << t;
            }
            return s;
        }

        friend Polynomial < T, Cmp > sPoly(const Polynomial < T, Cmp > & lhs,
                                           const Polynomial < T, Cmp > & rhs) {
            const Monomial < T > & _lcm = lcm(lhs.monomByPos(0), rhs.monomByPos(0));
            return lhs * (_lcm / lhs.monomByPos(0)) - rhs * (_lcm / rhs.monomByPos(0));
        }

        bool redStep(const Polynomial & second);

        const std::set < Monomial < T > , sa::inverseCmp < Cmp >> & terms() const;
    private:
        std::set < Monomial < T > , sa::inverseCmp < Cmp >> _terms;
    };
}

namespace sa {
    template < typename T, typename Cmp >
    Polynomial < T, Cmp > ::Polynomial(Monomial < T > m) {
        if (m.coef() != 0) _terms.insert(m);
    }

    template < typename T, typename Cmp >
    template < typename _Cmp >
    Polynomial < T, Cmp > ::Polynomial(const Polynomial < T, _Cmp > & p) {
        for (const auto & m: p.terms()) _terms.insert(m);
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > ::Polynomial(const std::set < Monomial < T > , Cmp > & p) {
        for (const auto & m: p)
            if (m.coef() != 0) _terms.insert(m);
    }

    template < typename T, typename Cmp >
    const Monomial < T > & Polynomial < T, Cmp > ::monomByPos(const int_f & pos) const {
        return *_terms.begin();
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > Polynomial < T, Cmp > ::operator - () const {
        std::set < Monomial < T > , Cmp > terms;
        for (auto & term: _terms) terms.insert(-term);
        return Polynomial(terms);
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator += (const Monomial < T > & t) {
        if (t.coef() == 0) return *this;
        for (auto & _t: terms()) {
            if (t.monom() == _t.monom()) {
                auto scalar = _t.coef() + t.coef();
                _terms.erase(_t);
                if (scalar != 0) _terms.insert(Monomial < T > (scalar, t.monom()));
                return *this;
            }
        }
        _terms.insert(t);
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator += (const Polynomial < T, Cmp > & p) {
        for (auto & term: p._terms) * this += term;
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator -= (const Polynomial < T, Cmp > & p) {
        * this += -p;
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator -= (const Monomial < T > & t) {
        * this += -t;
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator *= (const Monomial < T > & t) {
        Polynomial < T, Cmp > res;
        for (const auto & _t: terms()) res += Polynomial < T, Cmp > (_t * t);
        * this = res;
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator *= (const Polynomial < T, Cmp > & p) {
        Polynomial < T, Cmp > res;
        for (auto & t: terms()) res += p * t;
        * this = res;
        return *this;
    }

    template < typename T, typename Cmp >
    Polynomial < T, Cmp > & Polynomial < T, Cmp > ::operator /= (T coef) {
        Polynomial < T, Cmp > res;
        for (auto & t: terms()) res += t / coef;
        * this = res;
        return *this;
    }

    template < typename T, typename Cmp >
    const std::set < Monomial < T > , sa::inverseCmp < Cmp >> & Polynomial < T, Cmp > ::terms() const {
        return _terms;
    }

    template < typename T, typename Cmp >
    bool Polynomial < T, Cmp > ::redStep(const Polynomial & second) {
        if ( * this == Polynomial < T, Cmp > (Monomial < T > (0)) || second == Polynomial < T, Cmp > (Monomial < T > (0))) return false;
        for (const auto & term: _terms) {
            if (term.divWith(second.monomByPos(0))) {
                * this -= Polynomial < T, Cmp > (term / second.monomByPos(0)) * second;
                return true;
            }
        }
        return false;
    }
}

#endif
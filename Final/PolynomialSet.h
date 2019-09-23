#ifndef POLYNOMIALSET_H
#define POLYNOMIALSET_H

#include "PolynomialOrder.h"

#include <boost/rational.hpp>

namespace sa {
    template < typename T, typename Cmp >
    class PolynomialSet {
    public:
        PolynomialSet();

        template <typename _Cmp>
        PolynomialSet(const PolynomialSet<T, _Cmp>&);

        const std::set < Polynomial < T, Cmp > , PolynomialOrder < Cmp >> & polySet() const;

        bool redStep(Polynomial < T, Cmp > & p) const;

        friend std::vector < Polynomial < T, Cmp >> sPolySet(const PolynomialSet < T, Cmp > & p) {
            PolynomialOrder < Cmp > cmp;
            std::vector < Polynomial < T, Cmp >> sp;
            for (auto & l: p.polySet()) {
                for (auto & r: p.polySet()) {
                    if (cmp(l, r) && l != r) sp.push_back(sPoly(l, r));
                }
            }
            return sp;
        }

        bool redAlgorithm(Polynomial < T, Cmp > & p) const;

        void insertPoly(const Polynomial < T, Cmp > & p);

        friend PolynomialSet < T, Cmp > GroebnerBasis(PolynomialSet < T, Cmp > pol_set) {
            auto sp = sPolySet(pol_set);
            auto sp_size = sp.size();
            for (int i = 0; i < sp_size; i++) {
                pol_set.redAlgorithm(sp[i]);
                if (sp[i] != Polynomial < T, Cmp > (Monomial < T > (0))) {
                    for (const auto & _p: pol_set.polySet()) {
                        sp.push_back(sPoly(_p, sp[i]));
                        sp_size++;
                    }
                    pol_set.insertPoly(sp[i]);
                }
            }
            return pol_set;
        }

        friend PolynomialSet < T, Cmp > reduceBasis(PolynomialSet < T, Cmp > pol_set) {
            PolynomialSet < T, Cmp > ans;
            while (pol_set._polySet.size()) {
                auto p = * pol_set._polySet.begin();
                pol_set._polySet.erase(pol_set._polySet.begin());
                pol_set.redAlgorithm(p);
                ans.redAlgorithm(p);
                if (p != Monomial < T > (0)) ans.insertPoly(p / p.monomByPos(0).coef());
            }
            return ans;
        }

        template < typename _T, typename _Cmp >
        friend std::ostream & operator << (std::ostream & out,
                                           const PolynomialSet < _T, _Cmp > & p) {
            out << "---- SET OF POLY ----\n";
            for (auto elem = p.polySet().begin(); elem != p.polySet().end(); ++elem) {
                if (elem != p.polySet().begin()) out << "\n";
                out << * elem;
            }
            out << "\n---- END OF SET OF POLY ----\n";
            return out;
        }

    private:
        std::set < Polynomial < T, Cmp > , PolynomialOrder < Cmp >> _polySet;
    };
}

namespace sa {
    template < typename T, typename Cmp >
    void PolynomialSet < T, Cmp > ::insertPoly(const Polynomial < T, Cmp > & p) {
        if (p != Monomial < T > (0)) _polySet.insert(p);
    }

    template < typename T, typename Cmp >
    PolynomialSet < T, Cmp > ::PolynomialSet() =
    default;

    template < typename T, typename Cmp >
    const std::set < Polynomial < T, Cmp > , PolynomialOrder < Cmp >> & PolynomialSet < T, Cmp > ::polySet() const {
        return _polySet;
    }

    template < typename T, typename Cmp >
    bool PolynomialSet < T, Cmp > ::redStep(Polynomial < T, Cmp > & p) const {
        bool f = false;
        for (auto & _p: polySet())
            while (p.redStep(_p)) f = true;
        return f;
    }

    template < typename T, typename Cmp >
    bool PolynomialSet < T, Cmp > ::redAlgorithm(Polynomial < T, Cmp > & p) const {
        bool f = false;
        while (redStep(p)) f = true;
        return f;
    }

    template < typename T, typename Cmp >
    template < typename _Cmp >
    PolynomialSet< T, Cmp >::PolynomialSet(const PolynomialSet< T, _Cmp >& other_s) {
        for (const auto& p : other_s.polySet()) insertPoly(p);
    }
}

#endif
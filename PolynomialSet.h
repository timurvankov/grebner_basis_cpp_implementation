#ifndef POLYNOMIALSET_H
#define POLYNOMIALSET_H

#include "PolynomialOrder.h"

namespace sa {
    template<typename T, typename Cmp>
    class PolynomialSet {
    public:
        PolynomialSet();

        explicit PolynomialSet(const Polynomial <T, Cmp> &p);

        explicit PolynomialSet(const PolynomialSet<T, Cmp> &p);

        explicit PolynomialSet(const std::set<Polynomial<T, Cmp>, PolynomialOrder<Cmp >> &p);
        
        const std::set <Polynomial<T, Cmp>, PolynomialOrder<Cmp >> &polySet() const;
        
        bool redStep(Polynomial <T, Cmp>&p) const;

        friend std::vector <Polynomial<T, Cmp >> sPolySet(const PolynomialSet<T, Cmp> &p);

        bool redAlgorithm(Polynomial <T, Cmp>&p) const;
        
        void insertPoly(const Polynomial <T, Cmp> &p);

        PolynomialSet<T, Cmp> &GroebnerBasis();

        bool checkInIdeal(const Polynomial <T, Cmp> &p) const;

        template<typename _T, typename _Cmp>
        friend std::ostream &operator<<(std::ostream &,
                                        const PolynomialSet<_T, _Cmp> &p);

    private:
        std::set <Polynomial<T, Cmp>, PolynomialOrder<Cmp >> _polySet;
    };
}


#endif

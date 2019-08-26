#include "PolynomialSet.h"

namespace sa {
    template<typename T, typename Cmp>
    void PolynomialSet<T, Cmp>::insertPoly(const Polynomial <T, Cmp>& p) {
        if (p != Monomial<T>(0)) _polySet.insert(p);
    }

    template<typename T, typename Cmp>
    PolynomialSet<T, Cmp>::PolynomialSet() = default;

    template<typename T, typename Cmp>
    PolynomialSet<T, Cmp>::PolynomialSet(const Polynomial <T, Cmp> &p) {
        insertPoly(p);
    }

    template<typename T, typename Cmp>
    PolynomialSet<T, Cmp>::PolynomialSet(const std::set <Polynomial<T, Cmp>, PolynomialOrder<Cmp >> &p) {
        for (auto& _p: p) insertPoly(_p);
    }

    template<typename T, typename Cmp>
    PolynomialSet<T, Cmp>::PolynomialSet(const PolynomialSet<T, Cmp> &p) {
        for (auto& _p: p.polySet()) insertPoly(_p);
    }

    template<typename T, typename Cmp>
    std::ostream &operator<<(std::ostream &out,
                             const PolynomialSet<T, Cmp> &p) {
        out << "---- SET OF POLY ----\n";
        for (auto elem = p.polySet().begin(); elem != p.polySet().end(); ++elem) {
            if (elem != p.polySet().begin()) out << "\n";
            out << *elem;
        }
        out << "---- END OF SET OF POLY ----\n";
        return out;
    }

    template<typename T, typename Cmp>
    const std::set <Polynomial<T, Cmp>, PolynomialOrder<Cmp >> &PolynomialSet<T, Cmp>::polySet() const {
        return _polySet;
    }

    template<typename T, typename Cmp>
    bool PolynomialSet<T, Cmp>::redStep(Polynomial <T, Cmp>& p) const {
        bool f = false;
        for (auto &_p: polySet()) while (p.redStep(_p)) f = true;
        return f;
    }

    template<typename T, typename Cmp>
    std::vector <Polynomial<T, Cmp >> sPolySet(const PolynomialSet<T, Cmp>& p) {
        PolynomialOrder <Cmp> cmp;
        std::vector <Polynomial<T, Cmp >> sp;
        for (auto& l: p.polySet()) {
            for (auto& r: p.polySet()) {
                if (cmp(l, r) && l != r) sp.push_back(sPoly(l, r));
            }
        }
        return sp;
    }

    template<typename T, typename Cmp>
    bool PolynomialSet<T, Cmp>::redAlgorithm(Polynomial <T, Cmp>& p) const {
        bool f = false;
        while (redStep(p)) f= true;
        return f;
    }

    template<typename T, typename Cmp>
    PolynomialSet<T, Cmp> &PolynomialSet<T, Cmp>::GroebnerBasis() {
        auto sp = sPolySet(*this);
        for (auto& p: sp) {
            redAlgorithm(p);
            if (p != Monomial< T >(0)) {
                for (const auto& _p: polySet()) sp.push_back(sPoly(p, p));
                insertPoly(p);
            }
        }
        return *this;
    }

    template<typename T, typename Cmp>
    bool PolynomialSet<T, Cmp>::checkInIdeal(const Polynomial <T, Cmp> &p) const {
        auto check_i = *this;
        auto _p = p;
        auto gb = check_i.GroebnerBasis();
        gb.redAlgorithm(_p);
        return _p == Monomial < T > (0);
    }
}
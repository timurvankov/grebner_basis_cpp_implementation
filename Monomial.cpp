#include "Monomial.h"

namespace sa {
    template<typename T>
    void Monomial<T>::checkZero() {
        if (_coef == 0) {
            _monom = std::map<int_f, int_f>();
        }
    }

    template<typename T>
    Monomial<T>::Monomial(T c) {
        _coef = c;
    }

    template<typename T>
    Monomial<T>::Monomial(T c, const std::unordered_map<int_f, int_f> &degrees) {
        _coef = c;
        for (auto elem: degrees) {
            if (elem.second > 0) {
                _monom[elem.first] = elem.second;
            }
        }
        checkZero();
    }

    template<typename T>
    Monomial<T>::Monomial(T c, const std::map<int_f, int_f> &degrees) {
        _coef = c;
        for (auto elem: degrees) {
            if (elem.second > 0) {
                _monom[elem.first] = elem.second;
            }
        }
        checkZero();
    }

    template<typename T>
    Monomial<T>::Monomial(T c, const std::vector<int_f> &degrees) {
        _coef = c;
        for (int_f i = 0; i != int_f(degrees.size()); ++i) {
            if (degrees[i]) {
                _monom[i] = degrees[i];
            }
        }
        checkZero();
    }

    template<typename T>
    int_f Monomial<T>::degreeOfVar(int_f i) const {
        if (_monom.find(i) != _monom.end()) {
            return _monom.at(i);
        } else {
            return 0;
        }
    }

    template<typename T>
    bool Monomial<T>::onlyCoef() const {
        return !(_monom.size());
    }

    template<typename T>
    Monomial<T> &Monomial<T>::operator*=(const Monomial &rhs) {
        for (const auto &elem: rhs._monom) _monom[elem.first] += elem.second;
        _coef *= rhs._coef;
        checkZero();
        return *this;
    }

    template<typename T>
    Monomial<T> &Monomial<T>::operator*=(T rhs) {
        _coef *= rhs;
        checkZero();
        return *this;
    }

    template<typename T>
    Monomial<T> &Monomial<T>::operator/=(const Monomial &rhs) {
        for (const auto &elem: rhs._monom) {
            _monom[elem.first] -= elem.second;
            if (_monom[elem.first] == 0) _monom.erase(elem.first);
        }
        _coef /= rhs._coef;
        checkZero();
        return *this;
    }

    template<typename T>
    Monomial<T> &Monomial<T>::operator/=(T rhs) {
        _coef /= rhs;
        checkZero();
        return *this;
    }

    template<typename T>
    int_f Monomial<T>::rvar() const {
        if (onlyCoef()) return 0;
        else return _monom.crbegin()->first;
    }

    template<typename T>
    bool Monomial<T>::divWith(const Monomial<T> &d) const {
        if (d.coef() == 0) return false;
        for (const auto &elem: d._monom) if (elem.second > degreeOfVar(elem.first)) return false;
        return true;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &s, const Monomial<T> &m) {
        if (m.onlyCoef()) {
            s << m._coef;
            return s;
        }

        s << m._coef << '*';
        for (auto iterator = m._monom.begin(); iterator != m._monom.end(); ++iterator) {
            if (iterator != m._monom.begin()) s << " * ";
            s << "(x_" << iterator->first + 1 << ')' << "^(" << iterator->second << ')';
        }
        return s;
    }

    template<typename T>
    bool operator==(const Monomial<T> &lhs, const Monomial<T> &rhs) {
        return lhs._coef == rhs._coef && lhs._monom == rhs._monom;
    }

    template<typename T>
    bool operator!=(const Monomial<T> &lhs, const Monomial<T> &rhs) {
        return lhs._monom != rhs._monom || lhs._coef != rhs._coef;

    }

    template<typename T>
    Monomial<T> lcm(const Monomial<T> &lhs, const Monomial<T> &rhs) {
        Monomial<T> ans = rhs;
        for (auto elem: lhs._monom) ans._monom[elem.first] = std::max(elem.second, ans._monom[elem.first]);
        ans._coef = lhs.coef() * rhs.coef();
        return ans;
    }

    template<typename T>
    Monomial<T> operator*(Monomial<T> lhs, const Monomial<T> &rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<typename T>
    const T &Monomial<T>::coef() const {
        return _coef;
    }

    template<typename T>
    Monomial<T> Monomial<T>::operator-() const {
        return Monomial<T>(-_coef, _monom);
    }

    template<typename T>
    const std::map<int_f, int_f> &Monomial<T>::monom() const {
        return _monom;
    }

    template<typename T>
    Monomial<T> operator*(Monomial<T> lhs, T rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<typename T>
    Monomial<T> operator/(Monomial<T> lhs, const Monomial<T> &rhs) {
        lhs /= rhs;
        return lhs;
    }


    template<typename T>
    Monomial<T> operator/(Monomial<T> lhs, T rhs) {
        lhs /= rhs;
        return lhs;
    }
}
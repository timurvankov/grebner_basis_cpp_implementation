#include"PolynomialSet.h"
#include <chrono>

using namespace std;
vector<int> degrees;
vector<int> combination;
vector<vector<int>> all_combs;

void go(int offset, int k) {
    if (k == 0) {
        all_combs.push_back(combination);
        return;
    }

    for (int i = offset; i <= degrees.size() - k; ++i) {
        combination.push_back(degrees[i]);
        go(i+1, k-1);
        combination.pop_back();
    }
}

int main() {
    for (int n = 1; n < 10; n++) {
        cout << "Degree " << n << ":\n";
        sa::PolynomialSet<boost::rational<int>, sa::lexCmp> S;
        for (int k = 1; k < n; k++) {
            degrees = vector<int>();
            combination = vector<int>();
            all_combs = vector<vector<int>>();
            for (int i = 0; i < n; ++i) { degrees.push_back(i); }
            go(0, k);
            sa::Polynomial<boost::rational<int>, sa::lexCmp> p;
            for (auto j : all_combs) {
                std::vector<int_f> degs(n);
                for (auto i : j) {
                    degs[i] = 1;
                }
                p += sa::Monomial<boost::rational<int>>(1, degs);
            }
            S.insertPoly(p);
        }
        std::vector<int_f> ones(n, 1);
        sa::Polynomial<boost::rational<int>, sa::lexCmp> p(sa::Monomial<boost::rational<int>> (1, ones));
        int cf = -1;
        for (int _ = 1; _<n;_++) cf *= -1;
        boost::rational<int> _cf = cf;
        p += sa::Monomial<boost::rational<int>> (_cf, vector<int_f>(n));
        S.insertPoly(p);
        cout << "cyclic_n family:\n";
        cout << S;
        cout << "reduced groebner basis:\n";
        auto start = std::chrono::high_resolution_clock::now();
        cout << reduceBasis(GroebnerBasis(S));
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        cout << elapsed.count() << " time elapsed\n";
    }
}
#include <iostream>
#include <tuple>

using CPair = std::pair<int, int>;

class CompareFirst {
public:
  static int cmp(const CPair& first, const CPair& second) {
    return first.first - second.first;
  }
  bool operator() (const CPair& first, const CPair& second) const {
    return cmp(first, second) < 0;
  }
};

class CompareSecond {
public:
  static int cmp(const CPair& first, const CPair& second) {
    return first.second - second.second;
  }
  bool operator() (const CPair& first, const CPair& second) const {
    return cmp(first, second) < 0;
  }
};

template<class TFirst, class TSecond>
class LexSum {
public:
  static int cmp(const CPair& first, const CPair& second) {
    if (TFirst::cmp(first, second) == 0)
      return TSecond::cmp(first, second);
    return TFirst::cmp(first, second);
  }
  bool operator() (const CPair& first, const CPair& second) const {
    return cmp(first, second) < 0;
  }
};

using LexCompare = LexSum<CompareFirst, CompareSecond>;


int main() {
  CPair Pair1(1,1);
  CPair Pair2(2,0);
  CPair Pair3(1,3);
  std::cout << "Pair1 = (" << Pair1.first << ", " << Pair1.second << ")\n"
            << "Pair2 = (" << Pair2.first << ", " << Pair2.second << ")\n"
            << "Pair3 = (" << Pair3.first << ", " << Pair3.second << ")\n";
  std::cout << "CompareFirst(Pair1, Pair2) = "
            << CompareFirst::cmp(Pair1, Pair2)
            << "\nCompareFirst(Pair1, Pair3) = "
            << CompareFirst::cmp(Pair1, Pair3)
            << "\nCompareFirst(Pair2, Pair3) = "
            << CompareFirst::cmp(Pair2, Pair3)
            << std::endl;
  std::cout << "CompareSecond(Pair1, Pair2) = "
            << CompareSecond::cmp(Pair1, Pair2)
            << "\nCompareSecond(Pair1, Pair3) = "
            << CompareSecond::cmp(Pair1, Pair3)
            << "\nCompareSecond(Pair2, Pair3) = "
            << CompareSecond::cmp(Pair2, Pair3)
            << std::endl;
  std::cout << "LexCompare(Pair1, Pair2) = "
            << LexCompare::cmp(Pair1, Pair2)
            << "\nLexCompare(Pair1, Pair3) = "
            << LexCompare::cmp(Pair1, Pair3)
            << "\nLexCompare(Pair2, Pair3) = "
            << LexCompare::cmp(Pair2, Pair3)
            << std::endl;
  LexCompare Comparator;
  std::cout << "isLexLess(Pair1, Pair2) = "
            << Comparator(Pair1, Pair2)
            << "\nisLexLess(Pair1, Pair3) = "
            << Comparator(Pair1, Pair3)
            << "\nisLexLess(Pair2, Pair3) = "
            << Comparator(Pair2, Pair3)
            << std::endl;

  // for windows only
  system("pause");
  return 0;
}
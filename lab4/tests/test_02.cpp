// test_02.cpp - pruebas de recursion (02_recursion.cpp).
#include "../snippets/02_recursion.cpp"
#include <cassert>

int main() {
    assert(factorial(0) == 1 && factorial(5) == 120);

    vector<long long> memo(30, -1);
    assert(fib(0, memo) == 0 && fib(1, memo) == 1 && fib(10, memo) == 55);

    assert(fast_pow(2, 0) == 1 && fast_pow(2, 10) == 1024 && fast_pow(3, 4) == 81);

    assert(gcd_rec(48, 36) == 12 && gcd_rec(17, 5) == 1 && gcd_rec(10, 0) == 10);

    assert(suma_digitos(5) == 5 && suma_digitos(12345) == 15);

    vector<int> a = {1, 3, 5, 7, 9, 11};
    assert(bsearch_rec(a, 0, a.size() - 1, 7) == 3);
    assert(bsearch_rec(a, 0, a.size() - 1, 1) == 0);
    assert(bsearch_rec(a, 0, a.size() - 1, 11) == 5);
    assert(bsearch_rec(a, 0, a.size() - 1, 8) == -1);   // no esta

    vector<pair<char,char>> pasos;
    hanoi(3, 'A', 'C', 'B', pasos);
    assert(pasos.size() == 7);                          // 2^3 - 1
    pasos.clear();
    hanoi(0, 'A', 'C', 'B', pasos);
    assert(pasos.empty());                              // caso base

    string s = "abcde"; reverse_str(s, 0, s.size() - 1);
    assert(s == "edcba");
    string u = "x"; reverse_str(u, 0, u.size() - 1);
    assert(u == "x");                                   // un solo caracter

    printf("test_02 OK\n");
    return 0;
}

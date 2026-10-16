// test_03.cpp - pruebas de backtracking (03_backtracking.cpp).
#include "../snippets/03_backtracking.cpp"
#include <cassert>

int main() {
    vector<int> cur;

    // subconjuntos: 2^n
    vector<int> a = {1, 2, 3};
    vector<vector<int>> subs;
    subconjuntos(0, a, cur, subs);
    assert(subs.size() == 8);
    // n=0 -> solo el subconjunto vacio
    vector<int> vacio; vector<vector<int>> subs0;
    subconjuntos(0, vacio, cur, subs0);
    assert(subs0.size() == 1 && subs0[0].empty());

    // permutaciones: n!
    vector<bool> usado(a.size(), false);
    vector<vector<int>> perms;
    permutaciones(a, cur, usado, perms);
    assert(perms.size() == 6);
    // todas distintas
    set<vector<int>> unicas(perms.begin(), perms.end());
    assert(unicas.size() == 6);

    // combinaciones C(n,k)
    vector<vector<int>> c42; combinaciones(4, 2, 1, cur, c42);
    assert(c42.size() == 6);
    vector<vector<int>> c50; combinaciones(5, 0, 1, cur, c50);
    assert(c50.size() == 1);                 // C(5,0) = 1 (el vacio)

    // parentesis: Catalan(n)
    vector<string> p3; string s;
    parentesis(0, 0, 3, s, p3);
    assert(p3.size() == 5);                  // Catalan(3)
    for (auto& x : p3) assert((int)x.size() == 6);

    // n reinas: valores conocidos
    auto reinas = [](int n) { vector<int> col(n); int sol = 0; n_reinas(0, n, col, sol); return sol; };
    assert(reinas(1) == 1);
    assert(reinas(4) == 2);
    assert(reinas(8) == 92);

    printf("test_03 OK\n");
    return 0;
}

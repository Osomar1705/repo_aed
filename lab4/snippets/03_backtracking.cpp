// backtracking
#include <bits/stdc++.h>
using namespace std;

// O(2^n) - todos los subconjuntos: en cada indice decido incluir o no.
void subconjuntos(int i, const vector<int>& a, vector<int>& actual, vector<vector<int>>& res) {
    if (i == (int)a.size()) { res.push_back(actual); return; } // caso base: decidi todos
    subconjuntos(i + 1, a, actual, res);        // rama: NO incluir a[i]
    actual.push_back(a[i]);                      // ELEGIR: incluir a[i]
    subconjuntos(i + 1, a, actual, res);         // EXPLORAR
    actual.pop_back();                           // DESHACER
}

// O(n * n!) - todas las permutaciones usando un arreglo 'usado'.
void permutaciones(const vector<int>& a, vector<int>& actual, vector<bool>& usado,
                   vector<vector<int>>& res) {
    if (actual.size() == a.size()) { res.push_back(actual); return; } // caso base
    for (int i = 0; i < (int)a.size(); ++i) {
        if (usado[i]) continue;                  // poda: ya esta en la permutacion
        usado[i] = true; actual.push_back(a[i]); // ELEGIR
        permutaciones(a, actual, usado, res);    // EXPLORAR
        actual.pop_back(); usado[i] = false;     // DESHACER
    }
}

// O(C(n,k)) - elegir k de {1..n}; 'inicio' evita repetir y fija orden creciente.
void combinaciones(int n, int k, int inicio, vector<int>& actual, vector<vector<int>>& res) {
    if ((int)actual.size() == k) { res.push_back(actual); return; } // caso base
    for (int v = inicio; v <= n; ++v) {
        actual.push_back(v);                     // ELEGIR
        combinaciones(n, k, v + 1, actual, res); // EXPLORAR (desde v+1)
        actual.pop_back();                       // DESHACER
    }
}

// O(Catalan(n)) - genera todas las combinaciones validas de n pares de parentesis.
// Poda: solo abro si quedan '(', solo cierro si hay '(' sin cerrar (cerrar<abrir).
void parentesis(int abrir, int cerrar, int n, string& s, vector<string>& res) {
    if ((int)s.size() == 2 * n) { res.push_back(s); return; } // caso base
    if (abrir < n)      { s.push_back('('); parentesis(abrir + 1, cerrar, n, s, res); s.pop_back(); }
    if (cerrar < abrir) { s.push_back(')'); parentesis(abrir, cerrar + 1, n, s, res); s.pop_back(); }
}

// O(n!) aprox - coloca n reinas sin que se ataquen; cuenta soluciones.
// 'col[f]' = columna de la reina en la fila f. Poda por columna y diagonales.
bool seguro(int fila, int c, const vector<int>& col) {
    for (int f = 0; f < fila; ++f) {
        if (col[f] == c) return false;                       // misma columna
        if (abs(col[f] - c) == abs(f - fila)) return false;  // misma diagonal
    }
    return true;
}
void n_reinas(int fila, int n, vector<int>& col, int& soluciones) {
    if (fila == n) { ++soluciones; return; }                 // caso base: todas colocadas
    for (int c = 0; c < n; ++c) {
        if (!seguro(fila, c, col)) continue;                 // poda
        col[fila] = c;                                       // ELEGIR
        n_reinas(fila + 1, n, col, soluciones);              // EXPLORAR
        // DESHACER implicito: la proxima c sobrescribe col[fila]
    }
}

#ifdef LOCAL_MAIN
int main() {
    vector<int> a = {1, 2, 3};

    vector<vector<int>> subs; vector<int> cur;
    subconjuntos(0, a, cur, subs);
    cout << "subconjuntos: " << subs.size() << '\n';          // 8

    vector<vector<int>> perms; vector<bool> usado(a.size(), false);
    permutaciones(a, cur, usado, perms);
    cout << "permutaciones: " << perms.size() << '\n';        // 6

    vector<vector<int>> combs;
    combinaciones(4, 2, 1, cur, combs);
    cout << "combinaciones C(4,2): " << combs.size() << '\n'; // 6

    vector<string> par; string s;
    parentesis(0, 0, 3, s, par);
    cout << "parentesis n=3: " << par.size() << '\n';         // 5

    vector<int> col(8); int sol = 0;
    n_reinas(0, 8, col, sol);
    cout << "8 reinas: " << sol << " soluciones\n";           // 92
    return 0;
}
#endif

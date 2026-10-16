// Patrones de recursion. Compila SOLO. En cada una: caso base + paso recursivo.
// Regla de oro: define el caso base ANTES de llamar, o entras en recursion infinita.
#include <bits/stdc++.h>
using namespace std;

// O(n) - factorial. Caso base: 0! = 1.
long long factorial(int n) {
    if (n <= 1) return 1;            // caso base
    return (long long)n * factorial(n - 1);
}

// O(n) - fibonacci con memo (sin memo seria O(2^n)).
long long fib(int n, vector<long long>& memo) {
    if (n <= 1) return n;            // caso base: fib(0)=0, fib(1)=1
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
}

// O(log b) - exponenciacion rapida: b^e partiendo el exponente en mitades.
long long fast_pow(long long b, long long e) {
    if (e == 0) return 1;            // caso base: b^0 = 1
    long long mitad = fast_pow(b, e / 2);
    if (e % 2 == 0) return mitad * mitad;
    return mitad * mitad * b;
}

// O(log min) - maximo comun divisor (Euclides). Caso base: gcd(a,0)=a.
long long gcd_rec(long long a, long long b) {
    if (b == 0) return a;
    return gcd_rec(b, a % b);
}

// O(d) - suma de digitos de n (d = cantidad de digitos).
int suma_digitos(int n) {
    if (n < 10) return n;            // caso base: un solo digito
    return n % 10 + suma_digitos(n / 10);
}

// O(log n) - busqueda binaria recursiva en [lo, hi]. Devuelve indice o -1.
int bsearch_rec(const vector<int>& a, int lo, int hi, int x) {
    if (lo > hi) return -1;          // caso base: rango vacio
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] < x) return bsearch_rec(a, mid + 1, hi, x);
    return bsearch_rec(a, lo, mid - 1, x);
}

// O(2^n) movimientos - Torres de Hanoi: mueve n discos de 'desde' a 'hacia'.
// Idea: mueve n-1 al auxiliar, mueve el grande, y pon los n-1 encima.
void hanoi(int n, char desde, char hacia, char aux, vector<pair<char,char>>& pasos) {
    if (n == 0) return;              // caso base: nada que mover
    hanoi(n - 1, desde, aux, hacia, pasos);
    pasos.push_back({desde, hacia}); // mueve el disco n
    hanoi(n - 1, aux, hacia, desde, pasos);
}

// O(n) - invertir un string in-place con dos indices que se acercan.
void reverse_str(string& s, int i, int j) {
    if (i >= j) return;              // caso base: indices se cruzaron
    swap(s[i], s[j]);
    reverse_str(s, i + 1, j - 1);
}

#ifdef LOCAL_MAIN
int main() {
    cout << factorial(5) << '\n';                 // 120
    vector<long long> memo(20, -1);
    cout << fib(10, memo) << '\n';                 // 55
    cout << fast_pow(2, 10) << '\n';               // 1024
    cout << gcd_rec(48, 36) << '\n';               // 12
    cout << suma_digitos(12345) << '\n';           // 15
    vector<int> a = {1, 3, 5, 7, 9};
    cout << bsearch_rec(a, 0, a.size() - 1, 7) << '\n'; // 3
    vector<pair<char,char>> pasos;
    hanoi(3, 'A', 'C', 'B', pasos);
    cout << "hanoi 3 discos: " << pasos.size() << " pasos\n"; // 7
    string s = "abcde"; reverse_str(s, 0, s.size() - 1);
    cout << s << '\n';                             // edcba
    return 0;
}
#endif

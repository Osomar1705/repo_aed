// 01_vector.cpp - Vector<T> con crecimiento por duplicacion (arreglo dinamico).
// Compila SOLO. Prohibido usar std::vector en la implementacion.
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Vector {
    T* a;          // arreglo crudo
    int n;         // cantidad de elementos
    int cap;       // capacidad reservada

    // O(1) - arranco vacio, sin reservar memoria todavia.
    Vector() : a(nullptr), n(0), cap(0) {}

    // O(n) - libero el bloque crudo al destruir.
    ~Vector() { delete[] a; }

    // O(1) - cantidad actual de elementos.
    int size() const { return n; }
    // O(1) - capacidad reservada, no la cantidad usada.
    int capacity() const { return cap; }
    // O(1) - true si no hay elementos.
    bool empty() const { return n == 0; }

    // O(n) - reservo nuevo bloque y copio; solo crece, nunca encoge aqui.
    void reserve(int c) {
        if (c <= cap) return;
        T* b = new T[c];
        for (int i = 0; i < n; i++) b[i] = a[i];
        delete[] a;
        a = b;
        cap = c;
    }

    // O(1) amortizado - si esta lleno duplico capacidad, luego escribo al final.
    void push_back(const T& x) {
        if (n == cap) reserve(cap ? cap * 2 : 1);
        a[n++] = x;
    }

    // O(1) - solo bajo el contador; no reduzco capacidad.
    void pop_back() {
        if (n > 0) n--;
    }

    // O(n) - corro a la derecha desde el final para abrir hueco en pos.
    void insert(int pos, const T& x) {
        if (pos < 0 || pos > n) return;
        if (n == cap) reserve(cap ? cap * 2 : 1);
        for (int i = n; i > pos; i--) a[i] = a[i - 1];
        a[pos] = x;
        n++;
    }

    // O(n) - corro a la izquierda para tapar el hueco en pos.
    void erase(int pos) {
        if (pos < 0 || pos >= n) return;
        for (int i = pos; i + 1 < n; i++) a[i] = a[i + 1];
        n--;
    }

    // O(1) - acceso directo por indice, sin chequeo.
    T& operator[](int i) { return a[i]; }
    const T& operator[](int i) const { return a[i]; }

    // O(1) - acceso con chequeo; lanza si el indice se sale.
    T& at(int i) {
        if (i < 0 || i >= n) throw out_of_range("Vector::at");
        return a[i];
    }

    // O(1) - vacio logicamente; conservo el bloque para reusar capacidad.
    void clear() { n = 0; }

    // O(n) - ajusto tamaño; si crece, reservo y relleno con def.
    void resize(int m, const T& def = T()) {
        if (m > cap) reserve(m);
        for (int i = n; i < m; i++) a[i] = def;
        n = m;
    }
};

#ifdef LOCAL_MAIN
int main() {
    Vector<int> v;
    for (int i = 0; i < 5; i++) v.push_back(i);
    v.insert(0, -1);
    v.erase(3);
    for (int i = 0; i < v.size(); i++) cout << v[i] << " \n"[i + 1 == v.size()];
    return 0;
}
#endif

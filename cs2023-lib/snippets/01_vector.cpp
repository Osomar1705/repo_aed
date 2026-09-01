// 01_vector.cpp - Vector<T> dinamico, estilo del curso (sz/cap/data, resize con shifts).
// Base: semana2/vector.cpp del profe. Compila SOLO. Prohibido std::vector adentro.
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Vector {
    int sz;      // cantidad de elementos
    int cap;     // capacidad reservada
    T* data;     // bloque crudo

    // O(1) - arranco con capacidad 1, como en clase.
    Vector() { sz = 0; cap = 1; data = new T[1]; }

    // O(n) - libero el bloque.
    ~Vector() { delete[] data; }

    // O(1) - cantidad de elementos.
    int size() const { return sz; }
    // O(1) - capacidad reservada.
    int capacity() const { return cap; }
    // O(1) - true si esta vacio.
    bool empty() const { return sz == 0; }

    // O(n) - reservo la potencia de 2 justa para 'len' (crece o decrece) y copio.
    void resize(int len) {
        int new_cap = cap;
        while (new_cap < len) new_cap <<= 1;                       // crecer
        while (new_cap >= 2 && (new_cap >> 1) >= len) new_cap >>= 1; // decrecer
        if (new_cap == cap) return;
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) new_data[i] = data[i];
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    // O(1) amortizado - si esta lleno duplico y luego escribo al final.
    void push_back(T value) {
        if (sz == cap) resize(2 * cap);
        data[sz++] = value;
    }

    // O(1) amortizado - bajo el contador; encojo si quedo muy vacio (cap/4).
    void pop_back() {
        if (sz == 0) return;
        --sz;
        if (cap > 1 && sz <= cap / 4) resize(cap / 2);
    }

    // O(n) - corro a la derecha para abrir hueco en pos.
    void insert(int pos, T value) {
        if (pos < 0 || pos > sz) return;
        if (sz == cap) resize(2 * cap);
        for (int i = sz; i > pos; --i) data[i] = data[i - 1];
        data[pos] = value;
        ++sz;
    }

    // O(n) - corro a la izquierda para tapar el hueco en pos.
    void erase(int pos) {
        if (pos < 0 || pos >= sz) return;
        for (int i = pos; i + 1 < sz; ++i) data[i] = data[i + 1];
        --sz;
    }

    // O(1) - acceso directo por indice, sin chequeo.
    T& operator[](const int& idx) const { return data[idx]; }

    // O(1) - acceso con chequeo; lanza si se sale.
    T& at(int idx) {
        if (idx < 0 || idx >= sz) throw out_of_range("Vector::at");
        return data[idx];
    }

    // O(1) - vacio logicamente (conservo el bloque).
    void clear() { sz = 0; }
};

// O(n) - imprime separado por espacios y salto final (truco " \n"[...] del curso).
void print(Vector<int>& a) {
    for (int i = 0; i < a.size(); ++i) cout << a[i] << " \n"[i + 1 == a.size()];
}

#ifdef LOCAL_MAIN
int main() {
    cin.tie(0)->sync_with_stdio(false);
    Vector<int> a;
    for (int i = 0; i < 5; ++i) a.push_back(i);
    a.insert(0, -1);
    a.erase(3);
    print(a);
    return 0;
}
#endif

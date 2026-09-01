// 06_io_listas.cpp - utilidades de entrada/salida sobre Nodo. Compila SOLO.
#include <bits/stdc++.h>
using namespace std;

struct Nodo {
    int val;
    Nodo* next;
    Nodo(int v) : val(v), next(nullptr) {}
};

// O(n) - leo n enteros de cin y construyo la lista en orden de lectura.
// Ojo: uso tail para pegar en O(1); si n==0 devuelvo nullptr.
Nodo* leer_lista(int n) {
    Nodo dummy(0);
    Nodo* t = &dummy;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        t->next = new Nodo(x);
        t = t->next;
    }
    return dummy.next;
}

// O(n) - construyo la lista a partir de un vector, mismo orden.
Nodo* desde_vector(const vector<int>& v) {
    Nodo dummy(0);
    Nodo* t = &dummy;
    for (int x : v) { t->next = new Nodo(x); t = t->next; }
    return dummy.next;
}

// O(n) - imprimo separada por espacios y salto de linea final.
void imprimir(Nodo* head) {
    bool first = true;
    for (Nodo* p = head; p; p = p->next) {
        if (!first) cout << ' ';
        cout << p->val;
        first = false;
    }
    cout << '\n';
}

// O(n) - vuelco la lista a un vector para procesar comodo.
vector<int> a_vector(Nodo* head) {
    vector<int> r;
    for (Nodo* p = head; p; p = p->next) r.push_back(p->val);
    return r;
}

// O(n) - libero la lista (util para no dejar fugas en pruebas locales).
void liberar(Nodo* head) {
    while (head) { Nodo* nx = head->next; delete head; head = nx; }
}

#ifdef LOCAL_MAIN
int main() {
    Nodo* h = desde_vector({5, 4, 3});
    imprimir(h);
    for (int x : a_vector(h)) cout << x << '_';
    cout << '\n';
    liberar(h);
    return 0;
}
#endif

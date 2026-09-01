// 04_lista_circular.cpp - lista circular simple (el ultimo apunta al primero).
// Compila SOLO. Guardo solo 'tail'; tail->next es el head. Ideal round-robin.
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct ListaCircular {
    struct Nodo {
        T val;
        Nodo* next;
        Nodo(const T& v) : val(v), next(nullptr) {}
    };
    Nodo* tail;   // el ultimo; tail->next == head
    int n;

    // O(1) - lista vacia.
    ListaCircular() : tail(nullptr), n(0) {}
    // O(n) - libero todo.
    ~ListaCircular() { clear(); }

    // O(1) - cantidad de elementos.
    int size() const { return n; }
    // O(1) - true si esta vacia.
    bool empty() const { return n == 0; }
    // O(1) - el primer nodo (o nullptr).
    Nodo* head() const { return tail ? tail->next : nullptr; }

    // O(1) - inserto al frente; si vacia, el nodo se apunta a si mismo.
    void push_front(const T& v) {
        Nodo* p = new Nodo(v);
        if (!tail) { p->next = p; tail = p; }
        else { p->next = tail->next; tail->next = p; }
        n++;
    }

    // O(1) - push_front y luego avanzo tail: el nuevo queda al final.
    void push_back(const T& v) {
        push_front(v);
        tail = tail->next;   // el recien insertado (head) pasa a ser tail
    }

    // O(n) - busco el valor con puntero previo dando una vuelta; reconecto.
    void erase(const T& v) {
        if (!tail) return;
        Nodo* prev = tail;
        Nodo* cur = tail->next;
        for (int i = 0; i < n; i++) {
            if (cur->val == v) {
                if (cur == tail && cur == tail->next) { // unico nodo
                    tail = nullptr;
                } else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                }
                delete cur;
                n--;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    // O(n) - primer nodo con ese valor dando una sola vuelta, o nullptr.
    Nodo* buscar(const T& v) {
        if (!tail) return nullptr;
        Nodo* p = tail->next;
        for (int i = 0; i < n; i++) {
            if (p->val == v) return p;
            p = p->next;
        }
        return nullptr;
    }

    // O(k mod n) - avanzo k pasos desde p para round-robin (turnos).
    Nodo* avanzar(Nodo* p, int k) {
        if (!p || n == 0) return p;
        k %= n;
        while (k--) p = p->next;
        return p;
    }

    // O(n) - recorro exactamente una vuelta (n pasos), sin bucle infinito.
    vector<T> una_vuelta() {
        vector<T> r;
        if (!tail) return r;
        Nodo* p = tail->next;
        for (int i = 0; i < n; i++) { r.push_back(p->val); p = p->next; }
        return r;
    }

    // O(n) - guardo head, rompo el circulo, y libero linealmente; sin loop infinito.
    void clear() {
        if (!tail) return;
        Nodo* p = tail->next;      // head
        tail->next = nullptr;      // rompo el circulo antes de recorrer
        while (p) { Nodo* nx = p->next; delete p; p = nx; }
        tail = nullptr;
        n = 0;
    }
};

#ifdef LOCAL_MAIN
int main() {
    ListaCircular<int> C;
    C.push_back(1); C.push_back(2); C.push_back(3);
    for (int x : C.una_vuelta()) cout << x << ' ';
    cout << '\n';
    C.erase(2);
    for (int x : C.una_vuelta()) cout << x << ' ';
    cout << '\n';
    return 0;
}
#endif

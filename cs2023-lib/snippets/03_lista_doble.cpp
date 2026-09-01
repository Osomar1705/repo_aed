// 03_lista_doble.cpp - lista doblemente enlazada. Compila SOLO.
// Ventaja clave: erase(Nodo*) en O(1) real, y recorrido en ambos sentidos.
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct ListaDoble {
    struct Nodo {
        T val;
        Nodo* prev;
        Nodo* next;
        Nodo(const T& v) : val(v), prev(nullptr), next(nullptr) {}
    };
    Nodo* head;
    Nodo* tail;
    int n;

    // O(1) - lista vacia.
    ListaDoble() : head(nullptr), tail(nullptr), n(0) {}
    // O(n) - libero todo.
    ~ListaDoble() { clear(); }

    // O(1) - cantidad de elementos.
    int size() const { return n; }
    // O(1) - true si esta vacia.
    bool empty() const { return n == 0; }

    // O(1) - nuevo nodo al frente, enlazando prev/next.
    void push_front(const T& v) {
        Nodo* p = new Nodo(v);
        p->next = head;
        if (head) head->prev = p;
        else tail = p;
        head = p;
        n++;
    }

    // O(1) - nuevo nodo al final usando tail.
    void push_back(const T& v) {
        Nodo* p = new Nodo(v);
        p->prev = tail;
        if (tail) tail->next = p;
        else head = p;
        tail = p;
        n++;
    }

    // O(1) - saco la cabeza y reengancho.
    void pop_front() {
        if (!head) return;
        Nodo* p = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete p;
        n--;
    }

    // O(1) - saco la cola y reengancho.
    void pop_back() {
        if (!tail) return;
        Nodo* p = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete p;
        n--;
    }

    // O(1) - inserto un valor justo antes de p; caso borde: p == head.
    void insert_before(Nodo* p, const T& v) {
        if (!p) return;
        Nodo* q = new Nodo(v);
        q->next = p;
        q->prev = p->prev;
        if (p->prev) p->prev->next = q;
        else head = q;
        p->prev = q;
        n++;
    }

    // O(1) - inserto un valor justo despues de p; caso borde: p == tail.
    void insert_after(Nodo* p, const T& v) {
        if (!p) return;
        Nodo* q = new Nodo(v);
        q->prev = p;
        q->next = p->next;
        if (p->next) p->next->prev = q;
        else tail = q;
        p->next = q;
        n++;
    }

    // O(1) real - con prev y next reconecto sin recorrer nada.
    void erase(Nodo* p) {
        if (!p) return;
        if (p->prev) p->prev->next = p->next;
        else head = p->next;
        if (p->next) p->next->prev = p->prev;
        else tail = p->prev;
        delete p;
        n--;
    }

    // O(n) - primer nodo con ese valor, o nullptr.
    Nodo* buscar(const T& v) {
        for (Nodo* p = head; p; p = p->next)
            if (p->val == v) return p;
        return nullptr;
    }

    // O(k) - nodo en posicion k (0-indexado); arranco por el lado mas cercano.
    Nodo* at(int k) {
        if (k < 0 || k >= n) return nullptr;
        if (k <= n / 2) {
            Nodo* p = head;
            while (k--) p = p->next;
            return p;
        }
        Nodo* p = tail;
        int j = n - 1 - k;
        while (j--) p = p->prev;
        return p;
    }

    // O(n) - vuelco a un std::vector recorriendo de head a tail.
    vector<T> hacia_adelante() {
        vector<T> r;
        for (Nodo* p = head; p; p = p->next) r.push_back(p->val);
        return r;
    }

    // O(n) - vuelco recorriendo de tail a head (orden inverso).
    vector<T> hacia_atras() {
        vector<T> r;
        for (Nodo* p = tail; p; p = p->prev) r.push_back(p->val);
        return r;
    }

    // O(n) - libero nodo por nodo; queda vacia y reusable.
    void clear() {
        Nodo* p = head;
        while (p) { Nodo* nx = p->next; delete p; p = nx; }
        head = tail = nullptr;
        n = 0;
    }
};

#ifdef LOCAL_MAIN
int main() {
    ListaDoble<int> L;
    L.push_back(1); L.push_back(2); L.push_back(3);
    auto* m = L.at(1);
    L.erase(m);                 // borro el 2 en O(1)
    for (int x : L.hacia_adelante()) cout << x << ' ';
    cout << '\n';
    return 0;
}
#endif

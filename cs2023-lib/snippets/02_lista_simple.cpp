// 02_lista_simple.cpp - lista enlazada simple. Dos versiones separadas.
// Compila SOLO. Prohibido std::list / std::forward_list.
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// (a) ListaSimple<T> completa, con head y tail.
// ============================================================
template <class T>
struct ListaSimple {
    struct Nodo {
        T val;
        Nodo* next;
        Nodo(const T& v) : val(v), next(nullptr) {}
    };
    Nodo* head;
    Nodo* tail;
    int n;

    // O(1) - lista vacia.
    ListaSimple() : head(nullptr), tail(nullptr), n(0) {}
    // O(n) - libero todos los nodos.
    ~ListaSimple() { clear(); }

    // O(1) - cantidad de elementos.
    int size() const { return n; }
    // O(1) - true si esta vacia.
    bool empty() const { return n == 0; }

    // O(1) - nuevo nodo al frente; actualizo tail si estaba vacia.
    void push_front(const T& v) {
        Nodo* p = new Nodo(v);
        p->next = head;
        head = p;
        if (!tail) tail = p;
        n++;
    }

    // O(1) - engancho al final usando tail; sin recorrer.
    void push_back(const T& v) {
        Nodo* p = new Nodo(v);
        if (!tail) head = tail = p;
        else { tail->next = p; tail = p; }
        n++;
    }

    // O(1) - saco la cabeza; si queda vacia, tail a nullptr.
    void pop_front() {
        if (!head) return;
        Nodo* p = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete p;
        n--;
    }

    // O(1) - inserto despues de p (p != nullptr); actualizo tail si p era el ultimo.
    void insert_after(Nodo* p, const T& v) {
        if (!p) return;
        Nodo* q = new Nodo(v);
        q->next = p->next;
        p->next = q;
        if (tail == p) tail = q;
        n++;
    }

    // O(1) - borro el nodo siguiente a p; reconecto y ajusto tail.
    void erase_after(Nodo* p) {
        if (!p || !p->next) return;
        Nodo* q = p->next;
        p->next = q->next;
        if (tail == q) tail = p;
        delete q;
        n--;
    }

    // O(n) - busco el primer nodo con ese valor y lo saco; uso puntero previo.
    void erase(const T& v) {
        Nodo* prev = nullptr;
        Nodo* cur = head;
        while (cur && cur->val != v) { prev = cur; cur = cur->next; }
        if (!cur) return;
        if (!prev) head = cur->next;          // era la cabeza
        else prev->next = cur->next;
        if (tail == cur) tail = prev;          // era la cola
        delete cur;
        n--;
    }

    // O(n) - primer nodo con ese valor, o nullptr.
    Nodo* buscar(const T& v) {
        for (Nodo* p = head; p; p = p->next)
            if (p->val == v) return p;
        return nullptr;
    }

    // O(k) - nodo en la posicion k (0-indexado), o nullptr si se sale.
    Nodo* at(int k) {
        if (k < 0 || k >= n) return nullptr;
        Nodo* p = head;
        while (k--) p = p->next;
        return p;
    }

    // O(n) - invierto punteros in-place; tail pasa a ser el viejo head.
    void reverse() {
        Nodo* prev = nullptr;
        Nodo* cur = head;
        tail = head;
        while (cur) {
            Nodo* nx = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nx;
        }
        head = prev;
    }

    // O(n) - libero nodo por nodo y dejo la lista vacia y reusable.
    void clear() {
        Nodo* p = head;
        while (p) { Nodo* nx = p->next; delete p; p = nx; }
        head = tail = nullptr;
        n = 0;
    }
};

// ============================================================
// (b) Nodo suelto, para problemas de Codeforces.
//     Construye a mano y usa las funciones de 05_patrones_lista.cpp.
// ============================================================
struct Nodo {
    int val;
    Nodo* next;
    Nodo(int v) : val(v), next(nullptr) {}
};

#ifdef LOCAL_MAIN
int main() {
    ListaSimple<int> L;
    L.push_back(1); L.push_back(2); L.push_front(0);
    L.reverse();
    for (auto p = L.head; p; p = p->next) cout << p->val << ' ';
    cout << '\n';
    return 0;
}
#endif

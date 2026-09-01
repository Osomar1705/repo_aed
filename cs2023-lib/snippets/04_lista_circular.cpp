// 04_lista_circular.cpp - lista circular simple (el ultimo apunta al primero).
// Estilo del curso. Compila SOLO. Guardo solo 'tail'; tail->next es el head.
#include <bits/stdc++.h>
using namespace std;

template <typename data_type>
struct CListNode {
    data_type data;
    CListNode* next;
    CListNode(data_type data) : data(data), next(nullptr) {}
};

template <typename data_type>
struct CircularLinkedList {
    CListNode<data_type>* tail;   // el ultimo; tail->next == head
    int sz;

    // O(1) - lista vacia.
    CircularLinkedList() { tail = nullptr; sz = 0; }
    // O(n) - libero todo.
    ~CircularLinkedList() { clear(); }

    // O(1) - cantidad de elementos.
    int size() const { return sz; }
    // O(1) - true si esta vacia.
    bool empty() const { return tail == nullptr; }
    // O(1) - el primer nodo (o nullptr).
    CListNode<data_type>* head() const { return tail ? tail->next : nullptr; }

    // O(1) - inserto al frente; si vacia, el nodo se apunta a si mismo.
    void push_front(data_type value) {
        CListNode<data_type>* new_node = new CListNode<data_type>(value);
        if (!tail) { new_node->next = new_node; tail = new_node; }
        else { new_node->next = tail->next; tail->next = new_node; }
        ++sz;
    }

    // O(1) - push_front y avanzo tail: el nuevo queda al final.
    void push_back(data_type value) {
        push_front(value);
        tail = tail->next;
    }

    // O(n) - busco el valor con puntero previo dando una vuelta; reconecto.
    void erase(data_type value) {
        if (!tail) return;
        CListNode<data_type>* prev = tail;
        CListNode<data_type>* current = tail->next;
        for (int i = 0; i < sz; ++i) {
            if (current->data == value) {
                if (current == tail && current == tail->next) tail = nullptr; // unico
                else {
                    prev->next = current->next;
                    if (current == tail) tail = prev;
                }
                delete current;
                --sz;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // O(n) - primer nodo con ese valor dando una sola vuelta, o nullptr.
    CListNode<data_type>* buscar(data_type value) {
        if (!tail) return nullptr;
        CListNode<data_type>* p = tail->next;
        for (int i = 0; i < sz; ++i) {
            if (p->data == value) return p;
            p = p->next;
        }
        return nullptr;
    }

    // O(k mod sz) - avanzo k pasos desde p para round-robin (turnos).
    CListNode<data_type>* avanzar(CListNode<data_type>* p, int k) {
        if (!p || sz == 0) return p;
        k %= sz;
        while (k--) p = p->next;
        return p;
    }

    // O(n) - recorro exactamente una vuelta (sz pasos), sin bucle infinito.
    vector<data_type> una_vuelta() {
        vector<data_type> r;
        if (!tail) return r;
        CListNode<data_type>* p = tail->next;
        for (int i = 0; i < sz; ++i) { r.push_back(p->data); p = p->next; }
        return r;
    }

    // O(n) - guardo head, rompo el circulo y libero lineal; sin loop infinito.
    void clear() {
        if (!tail) return;
        CListNode<data_type>* p = tail->next;  // head
        tail->next = nullptr;                  // rompo el circulo antes de recorrer
        while (p) { CListNode<data_type>* nx = p->next; delete p; p = nx; }
        tail = nullptr;
        sz = 0;
    }
};

#ifdef LOCAL_MAIN
int main() {
    CircularLinkedList<int> C;
    C.push_back(1); C.push_back(2); C.push_back(3);
    for (int x : C.una_vuelta()) cout << x << ' ';
    cout << '\n';
    C.erase(2);
    for (int x : C.una_vuelta()) cout << x << ' ';
    cout << '\n';
    return 0;
}
#endif

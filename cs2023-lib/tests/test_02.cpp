// test_02.cpp - pruebas de ListaSimple<T> (02_lista_simple.cpp).
#include "../snippets/02_lista_simple.cpp"
#include <cassert>

static vector<int> vol(ListaSimple<int>& L) {
    vector<int> r;
    for (auto p = L.head; p; p = p->next) r.push_back(p->val);
    return r;
}

int main() {
    ListaSimple<int> L;
    assert(L.empty());

    // un solo elemento: head == tail
    L.push_back(10);
    assert(L.size() == 1 && L.head == L.tail && L.head->val == 10);

    L.push_front(5);        // 5 10
    L.push_back(20);        // 5 10 20
    assert((vol(L) == vector<int>{5, 10, 20}));
    assert(L.tail->val == 20);

    // pop_front hasta vaciar y verificar tail
    L.pop_front();          // 10 20
    assert(L.head->val == 10);

    // insert_after y erase_after
    L.insert_after(L.head, 15);   // 10 15 20
    assert((vol(L) == vector<int>{10, 15, 20}));
    L.erase_after(L.head);        // 10 20
    assert((vol(L) == vector<int>{10, 20}));

    // erase por valor: cabeza, cola, inexistente
    L.push_back(30);              // 10 20 30
    L.erase(10);                  // 20 30  (borra cabeza)
    assert(L.head->val == 20);
    L.erase(30);                  // 20     (borra cola)
    assert(L.tail->val == 20 && L.size() == 1);
    L.erase(999);                 // no existe, sin cambios
    assert(L.size() == 1);

    // buscar y at(k)
    L.push_back(40); L.push_back(50);   // 20 40 50
    assert(L.buscar(40) && L.buscar(40)->val == 40);
    assert(L.buscar(7) == nullptr);
    assert(L.at(0)->val == 20 && L.at(2)->val == 50);
    assert(L.at(3) == nullptr);         // fuera de rango
    assert(L.at(-1) == nullptr);

    // reverse
    L.reverse();                        // 50 40 20
    assert((vol(L) == vector<int>{50, 40, 20}));
    assert(L.tail->val == 20 && L.head->val == 50);

    // clear y reusar
    L.clear();
    assert(L.empty() && L.head == nullptr && L.tail == nullptr);
    L.push_back(1);
    assert(L.size() == 1);

    // version (b): Nodo suelto existe y enlaza
    Nodo* a = new Nodo(1); a->next = new Nodo(2);
    assert(a->next->val == 2);
    delete a->next; delete a;

    printf("test_02 OK\n");
    return 0;
}

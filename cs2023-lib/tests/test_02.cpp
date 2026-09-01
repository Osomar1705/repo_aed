// test_02.cpp - pruebas de LinkedList<T> (02_lista_simple.cpp).
#include "../snippets/02_lista_simple.cpp"
#include <cassert>

static vector<int> vol(LinkedList<int>& L) {
    vector<int> r;
    for (auto p = L.head; p; p = p->next) r.push_back(p->data);
    return r;
}

int main() {
    LinkedList<int> L;
    assert(L.empty());

    // un solo elemento: head == tail
    L.push_back(10);
    assert(L.size() == 1 && L.head == L.tail && L.head->data == 10);

    L.push_front(5);        // 5 10
    L.push_back(20);        // 5 10 20
    assert((vol(L) == vector<int>{5, 10, 20}));
    assert(L.tail->data == 20);

    // pop_front y verificar tail
    L.pop_front();          // 10 20
    assert(L.head->data == 10);

    // insert(node,v) inserta DESPUES; erase(node) borra el SIGUIENTE
    L.insert(L.head, 15);   // 10 15 20
    assert((vol(L) == vector<int>{10, 15, 20}));
    L.erase(L.head);        // 10 20  (borra el 15, que es el siguiente al head)
    assert((vol(L) == vector<int>{10, 20}));

    // insert(k,v) y erase(k) por indice 0-indexed
    L.insert(0, 5);         // 5 10 20
    L.insert(2, 15);        // 5 10 15 20
    assert((vol(L) == vector<int>{5, 10, 15, 20}));
    L.erase(1);             // 5 15 20  (borra el indice 1)
    assert((vol(L) == vector<int>{5, 15, 20}));

    // erase_value: cabeza, cola, inexistente
    L.push_back(30);              // 5 15 20 30
    L.erase_value(5);             // 15 20 30 (borra cabeza)
    assert(L.head->data == 15);
    L.erase_value(30);            // 15 20    (borra cola)
    assert(L.tail->data == 20 && L.size() == 2);
    L.erase_value(999);           // no existe, sin cambios
    assert(L.size() == 2);

    // buscar y at(k)
    L.push_back(40); L.push_back(50);   // 15 20 40 50
    assert(L.buscar(40) && L.buscar(40)->data == 40);
    assert(L.buscar(7) == nullptr);
    assert(L.at(0)->data == 15 && L.at(3)->data == 50);
    assert(L.at(4) == nullptr && L.at(-1) == nullptr);

    // reverse
    L.reverse();                        // 50 40 20 15
    assert((vol(L) == vector<int>{50, 40, 20, 15}));
    assert(L.tail->data == 15 && L.head->data == 50);

    // clear y reusar
    L.clear();
    assert(L.empty() && L.head == nullptr && L.tail == nullptr);
    L.push_back(1);
    assert(L.size() == 1);

    // version (b): ListNode suelto existe y enlaza
    ListNode* a = new ListNode(1); a->next = new ListNode(2);
    assert(a->next->val == 2);
    delete a->next; delete a;

    printf("test_02 OK\n");
    return 0;
}

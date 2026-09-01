// test_03.cpp - pruebas de DoublyLinkedList<T> (03_lista_doble.cpp).
#include "../snippets/03_lista_doble.cpp"
#include <cassert>

int main() {
    DoublyLinkedList<int> L;
    assert(L.empty());

    // un solo elemento: head == tail y sus prev/next nulos
    L.push_back(10);
    assert(L.head == L.tail && !L.head->prev && !L.head->next);

    L.push_front(5);    // 5 10
    L.push_back(20);    // 5 10 20
    assert((L.hacia_adelante() == vector<int>{5, 10, 20}));
    assert((L.hacia_atras() == vector<int>{20, 10, 5}));

    // pop_front y pop_back
    L.pop_front();      // 10 20
    assert(L.head->data == 10 && !L.head->prev);
    L.pop_back();       // 10
    assert(L.tail->data == 10 && !L.tail->next && L.size() == 1);

    // insert_before / insert_after incluyendo bordes head y tail
    L.insert_before(L.head, 7);   // 7 10
    assert(L.head->data == 7);
    L.insert_after(L.tail, 12);   // 7 10 12
    assert(L.tail->data == 12);
    auto* mid = L.at(1);          // 10
    L.insert_before(mid, 8);      // 7 8 10 12
    L.insert_after(mid, 11);      // 7 8 10 11 12
    assert((L.hacia_adelante() == vector<int>{7, 8, 10, 11, 12}));

    // erase(node) en O(1): medio, cabeza y cola
    L.erase(mid);                 // 7 8 11 12
    assert((L.hacia_adelante() == vector<int>{7, 8, 11, 12}));
    L.erase(L.head);              // 8 11 12
    assert(L.head->data == 8 && !L.head->prev);
    L.erase(L.tail);              // 8 11
    assert(L.tail->data == 11 && !L.tail->next);

    // buscar y at desde ambos lados
    assert(L.buscar(11)->data == 11 && L.buscar(999) == nullptr);
    assert(L.at(0)->data == 8 && L.at(1)->data == 11);
    assert(L.at(5) == nullptr && L.at(-1) == nullptr);

    // clear y reusar
    L.clear();
    assert(L.empty() && !L.head && !L.tail);
    L.push_front(1); L.push_back(2);
    assert((L.hacia_adelante() == vector<int>{1, 2}));

    printf("test_03 OK\n");
    return 0;
}

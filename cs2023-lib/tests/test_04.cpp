// test_04.cpp - pruebas de CircularLinkedList<T> (04_lista_circular.cpp).
#include "../snippets/04_lista_circular.cpp"
#include <cassert>

int main() {
    CircularLinkedList<int> C;
    assert(C.empty() && C.head() == nullptr);

    // un solo elemento apunta a si mismo
    C.push_back(1);
    assert(C.size() == 1 && C.tail->next == C.tail);

    C.push_back(2); C.push_back(3);   // 1 2 3
    assert((C.una_vuelta() == vector<int>{1, 2, 3}));
    C.push_front(0);                   // 0 1 2 3
    assert((C.una_vuelta() == vector<int>{0, 1, 2, 3}));
    assert(C.tail->data == 3);

    // buscar
    assert(C.buscar(2) && C.buscar(2)->data == 2);
    assert(C.buscar(99) == nullptr);

    // avanzar (round-robin) da la vuelta correctamente
    {
        auto* p = C.head();            // 0
        p = C.avanzar(p, 1);           // 1
        assert(p->data == 1);
        p = C.avanzar(p, 5);           // 5 mod 4 = 1 -> 2
        assert(p->data == 2);
    }

    // erase: medio, cola, cabeza, inexistente
    C.erase(2);                        // 0 1 3
    assert((C.una_vuelta() == vector<int>{0, 1, 3}));
    C.erase(3);                        // 0 1  (borra tail)
    assert(C.tail->data == 1 && (C.una_vuelta() == vector<int>{0, 1}));
    C.erase(0);                        // 1    (borra head)
    assert((C.una_vuelta() == vector<int>{1}) && C.tail->next == C.tail);
    C.erase(999);                      // sin cambios
    assert(C.size() == 1);

    // borrar el unico nodo deja vacia
    C.erase(1);
    assert(C.empty() && C.tail == nullptr);

    // clear y reusar (sin bucle infinito)
    C.push_back(7); C.push_back(8);
    C.clear();
    assert(C.empty() && C.tail == nullptr);
    C.push_back(9);
    assert((C.una_vuelta() == vector<int>{9}));

    printf("test_04 OK\n");
    return 0;
}

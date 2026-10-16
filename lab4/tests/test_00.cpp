// test_00.cpp - pruebas del BST (00_bst.cpp).
#include "../snippets/00_bst.cpp"
#include <cassert>

int main() {
    bst<int> t;
    // arbol vacio
    assert(!t.search(5));

    for (int x : {10, 5, 15, 3, 7, 12, 20}) t.insertar(x);
    assert((t.inorder_vec() == vector<int>{3, 5, 7, 10, 12, 15, 20}));
    assert(t.search(7) && !t.search(99));
    assert(t.min_element() == 3 && t.max_element() == 20);

    // duplicado: no cambia nada
    t.insertar(10);
    assert((int)t.inorder_vec().size() == 7);

    // borrar hoja, nodo con 1 hijo, nodo con 2 hijos
    t.erase(3);                                   // hoja
    assert((t.inorder_vec() == vector<int>{5, 7, 10, 12, 15, 20}));
    t.erase(15);                                  // 1 hijo (20)
    assert((t.inorder_vec() == vector<int>{5, 7, 10, 12, 20}));
    t.erase(10);                                  // 2 hijos (raiz)
    assert((t.inorder_vec() == vector<int>{5, 7, 12, 20}));

    // borrar inexistente
    t.erase(999);
    assert((int)t.inorder_vec().size() == 4);

    printf("test_00 OK\n");
    return 0;
}

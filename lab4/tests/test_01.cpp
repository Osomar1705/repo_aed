// test_01.cpp - pruebas del AVL/BBST (01_avl.cpp).
#include "../snippets/01_avl.cpp"
#include <cassert>

int main() {
    AVL<int> t;
    assert(t.is_avl());                 // vacio es AVL

    // insertar 1..10 ordenado: un BST degeneraria, el AVL se mantiene balanceado
    for (int i = 1; i <= 10; ++i) t.insert(i);
    assert((t.inorder_vec() == vector<int>{1,2,3,4,5,6,7,8,9,10}));
    assert(t.is_avl());
    assert(t.root->height <= 3);         // log2(10) ~ 3.3, altura chica

    assert(t.search(7) && !t.search(99));
    assert(t.min_element()->data == 1 && t.max_element()->data == 10);

    t.erase(4); t.erase(8);
    assert((t.inorder_vec() == vector<int>{1,2,3,5,6,7,9,10}));
    assert(t.is_avl());

    // ejemplo de clase: 10 20 30 40 50 25
    AVL<int> e;
    for (int x : {10, 20, 30, 40, 50, 25}) e.insert(x);
    assert((e.inorder_vec() == vector<int>{10,20,25,30,40,50}));
    assert(e.is_avl());

    // prueba aleatoria contra std::set
    AVL<int> a; set<int> s;
    mt19937 rng(12345);
    for (int i = 0; i < 5000; ++i) {
        int v = rng() % 200;
        if (rng() % 2) { a.insert(v); s.insert(v); }
        else { a.erase(v); s.erase(v); }
        assert(a.is_avl());
    }
    assert(a.inorder_vec() == vector<int>(s.begin(), s.end()));

    printf("test_01 OK\n");
    return 0;
}

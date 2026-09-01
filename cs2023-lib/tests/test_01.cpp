// test_01.cpp - pruebas de Vector<T> (01_vector.cpp).
#include "../snippets/01_vector.cpp"
#include <cassert>

int main() {
    Vector<int> v;
    assert(v.empty() && v.size() == 0);

    // push/pop y crecimiento
    for (int i = 0; i < 5; i++) v.push_back(i);   // 0 1 2 3 4
    assert(v.size() == 5);
    assert(v.capacity() >= 5);
    v.pop_back();                                 // 0 1 2 3
    assert(v.size() == 4 && v[3] == 3);

    // insertar en posicion 0 y en medio
    v.insert(0, -1);                              // -1 0 1 2 3
    assert(v[0] == -1 && v.size() == 5);
    v.insert(2, 99);                              // -1 0 99 1 2 3
    assert(v[2] == 99 && v.size() == 6);

    // erase cabeza y cola logica
    v.erase(0);                                   // 0 99 1 2 3
    assert(v[0] == 0);
    v.erase(v.size() - 1);                        // 0 99 1 2
    assert(v.size() == 4 && v[3] == 2);

    // at fuera de rango lanza
    bool lanzo = false;
    try { v.at(100); } catch (const std::out_of_range&) { lanzo = true; }
    assert(lanzo);

    // resize crece y encoge
    v.resize(6, 7);                               // ... 7 7
    assert(v.size() == 6 && v[5] == 7 && v[4] == 7);
    v.resize(2);
    assert(v.size() == 2);

    // clear y reusar
    v.clear();
    assert(v.empty());
    v.push_back(42);
    assert(v.size() == 1 && v[0] == 42);

    printf("test_01 OK\n");
    return 0;
}

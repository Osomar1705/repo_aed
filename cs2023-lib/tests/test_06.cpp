// test_06.cpp - pruebas de la hash table con chaining (07_hash_table.cpp).
#include "../snippets/07_hash_table.cpp"
#include <cassert>

int main() {
    // [OP-BRACKET] insertar, leer y sobrescribir
    {
        my_map<int, int> M(8);
        assert(M.empty());
        M[5] = 50;
        M[7] = 70;
        assert(M[5] == 50 && M[7] == 70);
        M[5] = 99;                                  // sobrescribe, no duplica
        assert(M[5] == 99 && M.size() == 2);
    }

    // [OP-BRACKET] la llave nueva entra con el valor por defecto (0)
    {
        my_map<int, int> M(8);
        assert(M[123] == 0);
        assert(M.size() == 1);                      // ojo: consultarla la inserto
        ++M[123]; ++M[123];
        assert(M[123] == 2);
    }

    // m=1: TODO cae al mismo cajon (peor caso), igual debe funcionar
    {
        my_map<int, int> M(1);
        for (int i = 0; i < 50; ++i) M[i] = i * i;
        assert(M.size() == 50);
        for (int i = 0; i < 50; ++i) assert(M[i] == i * i);
    }

    // [HAS-KEY] no debe insertar al consultar
    {
        my_map<int, int> M(8);
        assert(!M.has_key(42));
        assert(M.size() == 0);
        M[42] = 1;
        assert(M.has_key(42) && M.size() == 1);
    }

    // [ERASE] borrar existente, inexistente y volver a insertar
    {
        my_map<int, int> M(4);
        for (int i = 1; i <= 10; ++i) M[i] = i;
        M.erase(5);
        assert(!M.has_key(5) && M.size() == 9);
        M.erase(5);                                 // borrar dos veces no rompe
        assert(M.size() == 9);
        M.erase(999);                               // borrar lo que nunca estuvo
        assert(M.size() == 9);
        M[5] = 55;                                  // reinsertar
        assert(M[5] == 55 && M.size() == 10);
        for (int i = 1; i <= 10; ++i) if (i != 5) assert(M[i] == i);  // no se perdio nada
    }

    // [HASH-INT] siempre dentro de rango, y misma llave -> mismo cajon
    {
        my_map<int, int> M(13);
        for (int i = 0; i < 1000; ++i) {
            int b = M._hash(i);
            assert(b >= 0 && b < 13);
            assert(b == M._hash(i));                // determinista
        }
    }

    // [HASH-STR] llaves string
    {
        my_map<string, int> M(16);
        for (const string s : {"pan", "pan", "sol", "luna", "sol"}) ++M[s];
        assert(M["pan"] == 2 && M["sol"] == 2 && M["luna"] == 1);
        assert(M.size() == 3);
        assert(!M.has_key("mar"));
        M.erase("sol");
        assert(!M.has_key("sol") && M.size() == 2);
    }

    // valores long long y llaves grandes
    {
        my_map<long long, long long> M(32);
        M[1000000007ll] = 1ll << 40;
        assert(M[1000000007ll] == (1ll << 40));
    }

    cout << "test_06 OK\n";
    return 0;
}

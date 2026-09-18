// test_07.cpp - pruebas de los patrones con hash table (08_patrones_hash.cpp).
#include "../snippets/08_patrones_hash.cpp"
#include <cassert>

int main() {
    // [FREQ]
    {
        vector<int> a = {1, 2, 2, 3, 10, 2};
        auto f = frecuencias(a);
        assert(veces(f, 2) == 3);
        assert(veces(f, 1) == 1);
        assert(veces(f, 5) == 0);                   // ausente -> 0, sin insertar
        assert(f.size() == 4);
    }

    // [DISTINTOS] incluye vacio y todos iguales
    {
        assert(contar_distintos({1, 2, 2, 3, 1}) == 3);
        assert(contar_distintos({}) == 0);
        assert(contar_distintos({7, 7, 7, 7}) == 1);
    }

    // [PERMUT]
    {
        assert(es_permutacion({1, 2, 2}, {2, 1, 2}));
        assert(!es_permutacion({1, 2, 2}, {2, 1, 3}));
        assert(!es_permutacion({1, 2}, {1, 2, 2}));         // distinto tamanho
        assert(!es_permutacion({1, 1, 2}, {1, 2, 2}));      // misma llave, otra cuenta
        assert(es_permutacion({}, {}));
    }

    // [TWO-SUM] con negativos, que es donde se cae sin OFFSET
    {
        assert(hay_par_que_suma({2, 7, 11, 15}, 9));
        assert(!hay_par_que_suma({2, 7, 11, 15}, 100));
        assert(hay_par_que_suma({-5, -95, 2}, -100));
        assert(hay_par_que_suma({-5, 3, 5, 9}, 0));
        assert(hay_par_que_suma({2, 2}, 4));                // dos copias del mismo valor
        assert(!hay_par_que_suma({2}, 4));                  // no reusa el mismo elemento
        assert(!hay_par_que_suma({}, 0));
    }

    // [MAS-REPE] el empate lo gana la que aparecio primero
    {
        auto r = mas_repetida({"pan", "pan", "sol", "luna", "sol"});
        assert(r.first == "pan" && r.second == 2);
        auto r2 = mas_repetida({"sol", "pan", "pan", "sol"});
        assert(r2.first == "sol" && r2.second == 2);
    }

    // [SUBARR-SUMA]
    {
        assert(subarreglos_que_suman({1, 1, 1}, 2) == 2);
        assert(subarreglos_que_suman({3, 4, 7, 2, -3, 1, 4, 2}, 7) == 4);
        assert(subarreglos_que_suman({1, 2, 3}, 3) == 2);   // {1,2} y {3}
        assert(subarreglos_que_suman({0, 0}, 0) == 3);      // cuenta prefijo vacio
        assert(subarreglos_que_suman({1, 2}, 10) == 0);
    }

    cout << "test_07 OK\n";
    return 0;
}

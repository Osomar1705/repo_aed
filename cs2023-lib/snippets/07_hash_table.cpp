// mi hash table con encadenamiento (chaining), la de clase pero limpia
#include <bits/stdc++.h>
using namespace std;

// Idea: m "cajones". _hash(llave) decide en cual cae cada llave.
// Si dos llaves caen en el mismo cajon (colision) se guardan en lista
// -> eso es chaining. Buscar = ir al cajon y recorrer solo esa lista.
// Costos: O(1) promedio. Peor caso O(n) si todo cae al mismo cajon.
// Elegir m: m ~= 2*n. Cajones de mas no cuestan, de menos = TLE.
template <typename key_type, typename value_type>
struct my_map {
    int m;                                                   // cajones
    int _size;                                               // pares guardados
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) { chains.resize(m); }

    // [FIND-POS]
    // Cuando: posicion de la llave dentro de su cajon; todo lo demas se
    // apoya en esto (si no, repites el mismo while en 4 metodos).
    // Ojo: si no esta devuelve chains[b].size(), o sea "no encontrado".
    size_t _find_pos(int b, const key_type& key) const {
        size_t at = 0;                                       // O(largo del cajon)
        while (at < chains[b].size() && chains[b][at].first != key) ++at;
        return at;
    }

    // [OP-BRACKET]
    // Cuando: leer o escribir el valor de una llave, igual que unordered_map.
    // Ojo: si la llave NO existe la INSERTA con valor por defecto (0 en int),
    // por eso ++M[x] cuenta. Y devuelve referencia, por eso se puede asignar.
    value_type& operator[](const key_type& key) {
        int b = _hash(key);                                  // O(1) promedio
        size_t at = _find_pos(b, key);
        if (at == chains[b].size()) {
            chains[b].emplace_back(key, value_type());       // at ya apunta aqui
            ++_size;
        }
        return chains[b][at].second;
    }

    // [HAS-KEY]
    // Cuando: solo preguntar "existe?" sin insertar nada.
    // Ojo: usarlo antes de M[x] si no quieres ensuciar la tabla con ceros.
    bool has_key(const key_type& key) const {
        int b = _hash(key);                                  // O(1) promedio
        return _find_pos(b, key) != chains[b].size();
    }

    // [ERASE]
    // Cuando: borrar una llave.
    // Ojo: cambio el elemento con el ultimo y pop_back -> O(1). Se puede
    // porque dentro del cajon el orden no importa.
    void erase(const key_type& key) {
        int b = _hash(key);                                  // O(1) promedio
        size_t at = _find_pos(b, key);
        if (at == chains[b].size()) return;                  // no estaba
        swap(chains[b][at], chains[b].back());
        chains[b].pop_back();
        --_size;
    }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    // [HASH-INT]
    // Cuando: llaves enteras. Hash polinomial sobre los digitos.
    // Ojo: 1ll* o se desborda el int; +1 al digito para que el 0 no se
    // pierda; y con key <= 0 el while no entra -> todos los negativos
    // caen al cajon 0, ahi necesitas un OFFSET (ver 08_patrones_hash).
    int _hash(long long key) const {
        const int B = 311;                                   // O(digitos)
        const int MOD = 1e9 + 7;
        int h = 0;
        while (key > 0) {
            int d = key % 10;
            h = (1ll * h * B + (d + 1)) % MOD;
            key /= 10;
        }
        return h % m;
    }

    // [HASH-STR]
    // Cuando: llaves string. Mismo polinomio pero sobre los caracteres.
    // Ojo: c - 'a' + 1 asume minusculas; con texto mixto usa (unsigned char)c.
    int _hash(const string& key) const {
        const int B = 311;                                   // O(largo)
        const int MOD = 1e9 + 7;
        int h = 0;
        for (char c : key) h = (1ll * h * B + (c - 'a' + 1)) % MOD;
        return h % m;
    }

    // [PRINT]
    // Cuando: depurar. Si un cajon tiene 50 y los demas 0 -> m chico o mal hash.
    void print() const {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& e : chains[i]) cout << "(" << e.first << " -> " << e.second << ") ";
            cout << '\n';
        }
    }
};

// SIN_MAIN lo define 08_patrones_hash.cpp cuando incluye este archivo
#if defined(LOCAL_MAIN) && !defined(SIN_MAIN)
int main() {
    my_map<int, int> f(20);
    for (int x : {1, 2, 2, 3, 10, 2}) ++f[x];
    cout << f[2] << ' ' << f.size() << '\n';   // 3 4
    return 0;
}
#endif

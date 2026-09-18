// hash table con encadenamiento: m cajones, colisiones en lista. la de clase
#include <bits/stdc++.h>
using namespace std;

// m ~= 2*n cajones. si m es chico las listas crecen y el O(1) se vuelve O(n).
template <typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) { chains.resize(m); }

    // [FIND-POS]
    // Posicion de la llave en su cajon; si no esta devuelve el size del cajon.
    size_t _find_pos(int b, const key_type& key) const {
        size_t at = 0;                                    // O(largo del cajon)
        while (at < chains[b].size() && chains[b][at].first != key) ++at;
        return at;
    }

    // [OP-BRACKET]
    // Ojo: si la llave no existe la INSERTA con valor por defecto. por eso ++M[x] cuenta.
    value_type& operator[](const key_type& key) {
        int b = _hash(key);                               // O(1) promedio
        size_t at = _find_pos(b, key);
        if (at == chains[b].size()) {
            chains[b].emplace_back(key, value_type());    // at ya apunta aqui
            ++_size;
        }
        return chains[b][at].second;
    }

    // [HAS-KEY]
    // Preguntar sin insertar. usarlo antes de M[x] si no quiero ensuciar la tabla.
    bool has_key(const key_type& key) const {
        int b = _hash(key);                               // O(1) promedio
        return _find_pos(b, key) != chains[b].size();
    }

    // [ERASE]
    // Swap con el ultimo y pop_back: dentro del cajon el orden no importa.
    void erase(const key_type& key) {
        int b = _hash(key);                               // O(1) promedio
        size_t at = _find_pos(b, key);
        if (at == chains[b].size()) return;
        swap(chains[b][at], chains[b].back());
        chains[b].pop_back();
        --_size;
    }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    // [HASH-INT]
    // Polinomial sobre los digitos. el 1ll* es obligatorio o se desborda el int.
    // Con key <= 0 el while no entra: los negativos necesitan OFFSET (ver 08).
    int _hash(long long key) const {
        const int B = 311;                                // O(digitos)
        const int MOD = 1e9 + 7;
        int h = 0;
        while (key > 0) {
            int d = key % 10;
            h = (1ll * h * B + (d + 1)) % MOD;            // +1 para que el 0 no se pierda
            key /= 10;
        }
        return h % m;
    }

    // [HASH-STR]
    // Lo mismo sobre los caracteres. asume minusculas.
    int _hash(const string& key) const {
        const int B = 311;                                // O(largo)
        const int MOD = 1e9 + 7;
        int h = 0;
        for (char c : key) h = (1ll * h * B + (c - 'a' + 1)) % MOD;
        return h % m;
    }

    // [PRINT]
    // Depurar: si un cajon tiene 50 y los demas 0, m es chico o el hash es malo.
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

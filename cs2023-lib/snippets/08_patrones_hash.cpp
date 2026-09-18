// mis patrones con hash table para CF: busco por [TAG] con Ctrl+F. necesita el 07
#define SIN_MAIN
#include "07_hash_table.cpp"

// El hash solo entra con llaves > 0. el OFFSET va al guardar Y al consultar.
const long long OFFSET = 2e9;

// [FREQ]
// Contar y responder consultas. sin tabla seria O(n*q), asi O(n+q).
my_map<int, int> frecuencias(const vector<int>& a) {
    my_map<int, int> f(2 * (int)a.size() + 1);            // O(n)
    for (int x : a) ++f[x];
    return f;
}
int veces(my_map<int, int>& f, int x) {
    return f.has_key(x) ? f[x] : 0;                       // O(1), f[x] solo insertaria
}

// [DISTINTOS]
// La tabla como set: solo mencionar s[x] ya lo inserta.
int contar_distintos(const vector<int>& a) {
    my_map<int, int> s(2 * (int)a.size() + 1);            // O(n)
    for (int x : a) s[x];
    return s.size();
}

// [PERMUT]
// Cuento con a y descuento con b. el tamanho es el filtro gratis.
bool es_permutacion(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;               // O(n)
    my_map<int, int> f(2 * (int)a.size() + 1);
    for (int x : a) ++f[x];
    for (int x : b) {
        if (!f.has_key(x) || f[x] == 0) return false;
        --f[x];
    }
    return true;
}

// [TWO-SUM]
// Pregunto por el complemento ANTES de insertar x, si no uso el mismo dos veces.
bool hay_par_que_suma(const vector<long long>& a, long long S) {
    my_map<long long, int> vistos(2 * (int)a.size() + 1); // O(n)
    for (long long x : a) {
        if (vistos.has_key(S - x + OFFSET)) return true;
        vistos[x + OFFSET] = 1;
    }
    return false;
}

// [MAS-REPE]
// La tabla no tiene orden, por eso guardo el orden de aparicion aparte.
pair<string, int> mas_repetida(const vector<string>& v) {
    my_map<string, int> f(2 * (int)v.size() + 1);         // O(total de letras)
    vector<string> orden;
    for (const string& s : v) {
        if (!f.has_key(s)) orden.push_back(s);
        ++f[s];
    }
    string mejor; int maximo = 0;
    for (const string& s : orden)
        if (f[s] > maximo) { maximo = f[s]; mejor = s; }  // > estricto: gana la primera
    return {mejor, maximo};
}

// [SUBARR-SUMA]
// pre[i] - pre[j] == S, o sea busco pre[j] = pre[i] - S.
// El cnt[0] = 1 inicial cubre los subarreglos que empiezan en el indice 0.
long long subarreglos_que_suman(const vector<long long>& a, long long S) {
    my_map<long long, long long> cnt(2 * (int)a.size() + 1);  // O(n)
    cnt[0 + OFFSET] = 1;
    long long suma = 0, total = 0;
    for (long long x : a) {
        suma += x;
        long long buscado = suma - S + OFFSET;
        if (cnt.has_key(buscado)) total += cnt[buscado];
        ++cnt[suma + OFFSET];
    }
    return total;
}

#ifdef LOCAL_MAIN
int main() {
    vector<int> a = {1, 2, 2, 3, 10, 2};
    auto f = frecuencias(a);
    cout << veces(f, 2) << ' ' << contar_distintos(a) << '\n';   // 3 4
    cout << hay_par_que_suma({2, 7, 11, 15}, 9) << '\n';         // 1
    cout << subarreglos_que_suman({1, 1, 1}, 2) << '\n';         // 2
    return 0;
}
#endif

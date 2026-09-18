// mis patrones de hash table para CF: cada funcion es suelta, busco por [TAG] con Ctrl+F
// Unico snippet que depende de otro: necesita my_map de 07_hash_table.cpp.
#define SIN_MAIN
#include "07_hash_table.cpp"

// El _hash solo entra con llaves > 0, asi que para negativos empujo todo
// al lado positivo. Regla: el OFFSET se suma al guardar Y al consultar,
// si lo olvidas en un lado nunca coinciden (asi perdi un contest).
const long long OFFSET = 2e9;

// [FREQ]
// Cuando: contar ocurrencias y luego responder consultas "cuantas veces sale x".
// Ojo: sin hash table serian O(n*q); asi es O(n+q). Consulta con has_key,
// porque M[x] a secas insertaria la llave con 0.
my_map<int, int> frecuencias(const vector<int>& a) {
    my_map<int, int> f(2 * (int)a.size() + 1);        // O(n)
    for (int x : a) ++f[x];
    return f;
}
int veces(my_map<int, int>& f, int x) {
    return f.has_key(x) ? f[x] : 0;                   // O(1)
}

// [DISTINTOS]
// Cuando: cuantos valores distintos hay. La uso como SET: la llave es el dato
// y el valor no importa.
// Ojo: solo mencionar M[x] ya lo inserta, por eso size() es la respuesta.
int contar_distintos(const vector<int>& a) {
    my_map<int, int> s(2 * (int)a.size() + 1);        // O(n)
    for (int x : a) s[x];
    return s.size();
}

// [PERMUT]
// Cuando: b es una reordenacion de a? (anagrama de multiconjuntos)
// Ojo: primer filtro gratis es el tamanho; luego cuento con a y descuento con b.
bool es_permutacion(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;           // O(n)
    my_map<int, int> f(2 * (int)a.size() + 1);
    for (int x : a) ++f[x];
    for (int x : b) {
        if (!f.has_key(x) || f[x] == 0) return false; // sobra algo que no estaba
        --f[x];
    }
    return true;
}

// [TWO-SUM]
// Cuando: existen dos elementos que sumen S.
// Ojo: pregunto por el complemento ANTES de insertar x, asi no uso el mismo
// elemento dos veces. Y el OFFSET va en los dos lados.
bool hay_par_que_suma(const vector<long long>& a, long long S) {
    my_map<long long, int> vistos(2 * (int)a.size() + 1);  // O(n)
    for (long long x : a) {
        if (vistos.has_key(S - x + OFFSET)) return true;
        vistos[x + OFFSET] = 1;
    }
    return false;
}

// [MAS-REPE]
// Cuando: la palabra que mas se repite; si empatan, la que aparecio primero.
// Ojo: guardo el orden de aparicion aparte, porque la hash table NO tiene orden.
// El > estricto es lo que hace que gane la primera.
pair<string, int> mas_repetida(const vector<string>& v) {
    my_map<string, int> f(2 * (int)v.size() + 1);     // O(total de letras)
    vector<string> orden;
    for (const string& s : v) {
        if (!f.has_key(s)) orden.push_back(s);
        ++f[s];
    }
    string mejor; int maximo = 0;
    for (const string& s : orden)
        if (f[s] > maximo) { maximo = f[s]; mejor = s; }
    return {mejor, maximo};
}

// [SUBARR-SUMA]
// Cuando: cuantos subarreglos suman exactamente S.
// Ojo: prefijo[i] - prefijo[j] == S  <=>  busco prefijo[j] = prefijo[i] - S.
// Arranco con la suma 0 vista una vez, si no pierdo los subarreglos que
// empiezan en el indice 0.
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

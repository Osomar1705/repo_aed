// 05_patrones_lista.cpp - EL ARCHIVO CLAVE. Funciones sueltas sobre Nodo.
// Cada una es autocontenida y lista para pegar. Compila SOLO.
// Convencion: 'val' int, listas terminadas en nullptr (salvo las de ciclo).
#include <bits/stdc++.h>
using namespace std;

struct Nodo {
    int val;
    Nodo* next;
    Nodo(int v) : val(v), next(nullptr) {}
};

// [REVERSE-IT]
// Cuando: invertir toda la lista in-place, la version que siempre uso.
// Ojo: guarda next ANTES de reasignar cur->next o pierdes el resto.
Nodo* reverse_it(Nodo* head) {
    Nodo* prev = nullptr;
    while (head) {                 // O(n) - una pasada reasignando punteros
        Nodo* nx = head->next;
        head->next = prev;
        prev = head;
        head = nx;
    }
    return prev;                   // nuevo head
}

// [REVERSE-REC]
// Cuando: piden reverse recursivo, o para entender la recursion.
// Ojo: el caso base devuelve el nuevo head; head->next->next = head es el truco.
Nodo* reverse_rec(Nodo* head) {
    if (!head || !head->next) return head;          // O(n) tiempo, O(n) pila
    Nodo* nh = reverse_rec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return nh;
}

// [REVERSE-MN]
// Cuando: invertir solo el segmento entre posiciones m..n (1-indexado).
// Ojo: usa dummy para el caso m==1; conecta bien los tres tramos.
Nodo* reverse_between(Nodo* head, int m, int n) {
    Nodo dummy(0); dummy.next = head;               // O(n) - una pasada
    Nodo* pre = &dummy;
    for (int i = 1; i < m; i++) pre = pre->next;     // nodo antes del tramo
    Nodo* cur = pre->next;                           // primero del tramo
    for (int i = 0; i < n - m; i++) {                // muevo cur->next al frente
        Nodo* mov = cur->next;
        cur->next = mov->next;
        mov->next = pre->next;
        pre->next = mov;
    }
    return dummy.next;
}

// [MERGE]
// Cuando: fusionar dos listas YA ordenadas en una sola ordenada.
// Ojo: dummy head evita casos especiales; al final pega la cola restante.
Nodo* merge_ordenadas(Nodo* a, Nodo* b) {
    Nodo dummy(0);                                   // O(n+m)
    Nodo* t = &dummy;
    while (a && b) {
        if (a->val <= b->val) { t->next = a; a = a->next; }
        else { t->next = b; b = b->next; }
        t = t->next;
    }
    t->next = a ? a : b;                              // lo que sobre
    return dummy.next;
}

// [DEDUP]
// Cuando: eliminar duplicados de una lista YA ordenada, dejando uno de cada.
// Ojo: al borrar, libera el nodo y NO avances cur; compara cur con cur->next.
Nodo* dedup_ordenada(Nodo* head) {
    Nodo* cur = head;
    while (cur && cur->next) {                        // O(n)
        if (cur->val == cur->next->val) {
            Nodo* dup = cur->next;
            cur->next = dup->next;
            delete dup;
        } else {
            cur = cur->next;
        }
    }
    return head;
}

// [MEDIO]
// Cuando: hallar el nodo medio (en n par, devuelve el segundo del medio).
// Ojo: condicion fast && fast->next; leer fast->next->next sin chequear peta.
Nodo* nodo_medio(Nodo* head) {
    Nodo* slow = head;                                // O(n)
    Nodo* fast = head;
    while (fast && fast->next) {                      // slow avanza 1, fast 2
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// [CICLO]
// Cuando: detectar si la lista tiene ciclo (Floyd, tortuga y liebre).
// Ojo: compara punteros, no valores; arranca ambos en head.
bool tiene_ciclo(Nodo* head) {
    Nodo* slow = head;                                // O(n), O(1) memoria
    Nodo* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;                // se encontraron
    }
    return false;
}

// [CICLO-INI]
// Cuando: hallar el nodo donde empieza el ciclo (o nullptr si no hay).
// Ojo: tras el encuentro, reinicia uno en head y avanza ambos de a 1.
Nodo* inicio_ciclo(Nodo* head) {
    Nodo* slow = head;                                // O(n)
    Nodo* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                           // hay ciclo
            Nodo* p = head;
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;                                 // inicio del ciclo
        }
    }
    return nullptr;
}

// [KTH-FIN]
// Cuando: eliminar el k-esimo nodo desde el final en UNA sola pasada.
// Ojo: dummy cubre borrar el head; adelanta fast k pasos y off-by-one.
Nodo* eliminar_kth_desde_fin(Nodo* head, int k) {
    Nodo dummy(0); dummy.next = head;                 // O(n)
    Nodo* fast = &dummy;
    Nodo* slow = &dummy;
    for (int i = 0; i < k; i++) {                     // separa fast k pasos
        if (!fast->next) return head;                 // k > n: no hago nada
        fast = fast->next;
    }
    while (fast->next) { fast = fast->next; slow = slow->next; }
    Nodo* del = slow->next;
    slow->next = del->next;
    delete del;
    return dummy.next;
}

// [ROTAR]
// Cuando: rotar la lista k posiciones a la derecha.
// Ojo: k %= n; cierra el circulo, avanza n-k%n y corta ahi.
Nodo* rotar_derecha(Nodo* head, int k) {
    if (!head || !head->next) return head;            // O(n)
    int n = 1;
    Nodo* tail = head;
    while (tail->next) { tail = tail->next; n++; }
    k %= n;
    if (k == 0) return head;
    tail->next = head;                                // cierro circulo
    int pasos = n - k;                                // nuevo tail queda aqui
    Nodo* nt = head;
    for (int i = 1; i < pasos; i++) nt = nt->next;
    Nodo* nh = nt->next;
    nt->next = nullptr;                               // corto
    return nh;
}

// [PARTIR]
// Cuando: particionar por x: menores que x antes, resto despues, orden estable.
// Ojo: usa dos dummies (menores y >=); no olvides cerrar la cola con nullptr.
Nodo* particionar(Nodo* head, int x) {
    Nodo dmen(0), dmay(0);                            // O(n)
    Nodo* men = &dmen;
    Nodo* may = &dmay;
    for (Nodo* p = head; p; p = p->next) {
        if (p->val < x) { men->next = p; men = p; }
        else { may->next = p; may = p; }
    }
    may->next = nullptr;                              // cierro la segunda mitad
    men->next = dmay.next;                            // enlazo mitades
    return dmen.next;
}

// [MSORT]
// Cuando: ordenar una lista enlazada en O(n log n) sin arreglos auxiliares.
// Ojo: parte por el medio (cuidado n=1), ordena mitades y usa [MERGE].
Nodo* merge_sort(Nodo* head) {
    if (!head || !head->next) return head;            // O(n log n)
    // parto: slow queda en el fin de la primera mitad
    Nodo* slow = head;
    Nodo* fast = head->next;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    Nodo* mid = slow->next;
    slow->next = nullptr;                             // corto en dos
    Nodo* a = merge_sort(head);
    Nodo* b = merge_sort(mid);
    return merge_ordenadas(a, b);                     // reuso [MERGE]
}

#ifdef LOCAL_MAIN
int main() {
    // construyo 3 2 1 y ordeno
    Nodo* h = new Nodo(3); h->next = new Nodo(2); h->next->next = new Nodo(1);
    h = merge_sort(h);
    for (Nodo* p = h; p; p = p->next) cout << p->val << ' ';
    cout << '\n';
    return 0;
}
#endif

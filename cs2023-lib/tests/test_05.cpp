// test_05.cpp - pruebas de los patrones sobre ListNode (05_patrones_lista.cpp).
#include "../snippets/05_patrones_lista.cpp"
#include <cassert>

// helpers locales (no chocan con las funciones del snippet)
static ListNode* build(const vector<int>& v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
static vector<int> dump(ListNode* h) {
    vector<int> r;
    for (ListNode* p = h; p; p = p->next) r.push_back(p->val);
    return r;
}
static void freelist(ListNode* h) {
    while (h) { ListNode* nx = h->next; delete h; h = nx; }
}

int main() {
    // [REVERSE-IT] n=0, n=1, n=3
    assert(reverse_it(nullptr) == nullptr);
    { ListNode* h = build({1}); h = reverse_it(h); assert((dump(h) == vector<int>{1})); freelist(h); }
    { ListNode* h = build({1,2,3}); h = reverse_it(h); assert((dump(h) == vector<int>{3,2,1})); freelist(h); }

    // [REVERSE-REC]
    { ListNode* h = build({1,2,3,4}); h = reverse_rec(h); assert((dump(h) == vector<int>{4,3,2,1})); freelist(h); }

    // [REVERSE-MN] invertir 2..4 de 1 2 3 4 5 -> 1 4 3 2 5
    { ListNode* h = build({1,2,3,4,5}); h = reverse_between(h,2,4);
      assert((dump(h) == vector<int>{1,4,3,2,5})); freelist(h); }
    // m==1 (incluye head): invertir 1..3 de 1 2 3 4 -> 3 2 1 4
    { ListNode* h = build({1,2,3,4}); h = reverse_between(h,1,3);
      assert((dump(h) == vector<int>{3,2,1,4})); freelist(h); }

    // [MERGE] incluye una lista vacia
    { ListNode* a = build({1,3,5}); ListNode* b = build({2,4,6});
      ListNode* m = merge_ordenadas(a,b); assert((dump(m) == vector<int>{1,2,3,4,5,6})); freelist(m); }
    { ListNode* a = build({}); ListNode* b = build({2,4});
      ListNode* m = merge_ordenadas(a,b); assert((dump(m) == vector<int>{2,4})); freelist(m); }

    // [DEDUP]
    { ListNode* h = build({1,1,2,3,3,3}); h = dedup_ordenada(h);
      assert((dump(h) == vector<int>{1,2,3})); freelist(h); }
    { ListNode* h = build({1}); h = dedup_ordenada(h); assert((dump(h) == vector<int>{1})); freelist(h); }

    // [MEDIO] n par -> segundo del medio; n impar -> el central
    { ListNode* h = build({1,2,3,4}); assert(nodo_medio(h)->val == 3); freelist(h); }
    { ListNode* h = build({1,2,3,4,5}); assert(nodo_medio(h)->val == 3); freelist(h); }
    { ListNode* h = build({1}); assert(nodo_medio(h)->val == 1); freelist(h); }

    // [CICLO] y [CICLO-INI] con y sin ciclo
    { ListNode* h = build({1,2,3,4}); assert(!tiene_ciclo(h) && inicio_ciclo(h) == nullptr); freelist(h); }
    {
        ListNode* a = new ListNode(1), *b = new ListNode(2), *c = new ListNode(3), *d = new ListNode(4);
        a->next=b; b->next=c; c->next=d; d->next=b;   // ciclo empieza en b
        assert(tiene_ciclo(a));
        assert(inicio_ciclo(a) == b);
        d->next = nullptr;                            // rompo para liberar
        freelist(a);
    }

    // [KTH-FIN] k=1 (ultimo), k=n (primero), k>n (sin cambios)
    { ListNode* h = build({1,2,3,4,5}); h = eliminar_kth_desde_fin(h,1);
      assert((dump(h) == vector<int>{1,2,3,4})); freelist(h); }
    { ListNode* h = build({1,2,3,4,5}); h = eliminar_kth_desde_fin(h,5);
      assert((dump(h) == vector<int>{2,3,4,5})); freelist(h); }
    { ListNode* h = build({1,2}); h = eliminar_kth_desde_fin(h,9);
      assert((dump(h) == vector<int>{1,2})); freelist(h); }

    // [ROTAR] k>n y k multiplo de n
    { ListNode* h = build({1,2,3,4,5}); h = rotar_derecha(h,2);
      assert((dump(h) == vector<int>{4,5,1,2,3})); freelist(h); }
    { ListNode* h = build({1,2,3}); h = rotar_derecha(h,7);   // 7%3=1
      assert((dump(h) == vector<int>{3,1,2})); freelist(h); }
    { ListNode* h = build({1,2,3}); h = rotar_derecha(h,3);   // vuelta completa
      assert((dump(h) == vector<int>{1,2,3})); freelist(h); }

    // [PARTIR] orden relativo estable
    { ListNode* h = build({3,1,4,2,5,2}); h = particionar(h,3);
      assert((dump(h) == vector<int>{1,2,2,3,4,5})); freelist(h); }

    // [MSORT] ya ordenada, al reves, con repetidos, n=2
    { ListNode* h = build({1,2,3,4}); h = merge_sort(h); assert((dump(h) == vector<int>{1,2,3,4})); freelist(h); }
    { ListNode* h = build({4,3,2,1}); h = merge_sort(h); assert((dump(h) == vector<int>{1,2,3,4})); freelist(h); }
    { ListNode* h = build({3,1,2,3,1}); h = merge_sort(h); assert((dump(h) == vector<int>{1,1,2,3,3})); freelist(h); }
    { ListNode* h = build({2,1}); h = merge_sort(h); assert((dump(h) == vector<int>{1,2})); freelist(h); }
    assert(merge_sort(nullptr) == nullptr);

    printf("test_05 OK\n");
    return 0;
}

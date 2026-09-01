// utilidades para leer, imprimir y convertir listas (sobre ListNode)
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

// O(n)
// Ojo: uso tail para pegar en O(1); si n==0 devuelvo nullptr.
ListNode* leer_lista(int n) {
    ListNode dummy(0);
    ListNode* t = &dummy;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        t->next = new ListNode(x);
        t = t->next;
    }
    return dummy.next;
}

// O(n)
ListNode* desde_vector(const vector<int>& v) {
    ListNode dummy(0);
    ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}

// O(n)
void imprimir(ListNode* head) {
    bool first = true;
    for (ListNode* p = head; p; p = p->next) {
        if (!first) cout << ' ';
        cout << p->val;
        first = false;
    }
    cout << '\n';
}

// O(n)
vector<int> a_vector(ListNode* head) {
    vector<int> r;
    for (ListNode* p = head; p; p = p->next) r.push_back(p->val);
    return r;
}

// O(n)
void liberar(ListNode* head) {
    while (head) { ListNode* nx = head->next; delete head; head = nx; }
}

#ifdef LOCAL_MAIN
int main() {
    ListNode* h = desde_vector({5, 4, 3});
    imprimir(h);
    for (int x : a_vector(h)) cout << x << '_';
    cout << '\n';
    liberar(h);
    return 0;
}
#endif

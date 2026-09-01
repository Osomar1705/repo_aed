// lista simple: LinkedList completa + ListNode suelto para CF. sin std::list
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// (a) LinkedList<data_type> completa, con head y tail (como en clase).
//     Convencion del profe: insert(node,v) inserta DESPUES de node;
//     erase(node) elimina el nodo SIGUIENTE a node.
// ============================================================
template <typename data_type>
struct LinkedNode {
    data_type data;
    LinkedNode* next;
    LinkedNode() { next = nullptr; }
    LinkedNode(data_type data, LinkedNode<data_type>* next = nullptr) : data(data), next(next) {}
};

template <typename data_type>
struct LinkedList {
    LinkedNode<data_type>* head;
    LinkedNode<data_type>* tail;
    int sz;

    // O(1)
    LinkedList() { head = tail = nullptr; sz = 0; }
    // O(n)
    ~LinkedList() { clear(); }

    // O(1)
    int size() const { return sz; }
    // O(1)
    bool empty() const { return head == nullptr; }

    // O(1)
    void push_front(data_type value) {
        LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, head);
        if (head == nullptr) tail = new_node;
        head = new_node;
        ++sz;
    }

    // O(1)
    void push_back(data_type value) {
        if (tail == nullptr) head = tail = new LinkedNode<data_type>(value);
        else { tail->next = new LinkedNode<data_type>(value); tail = tail->next; }
        ++sz;
    }

    // O(1)
    void insert(LinkedNode<data_type>* node, data_type value) {
        LinkedNode<data_type>* new_node = new LinkedNode<data_type>(value, node->next);
        if (node == tail) tail = new_node;
        node->next = new_node;
        ++sz;
    }

    // O(k)
    void insert(int k, data_type value) {
        if (k == 0) { push_front(value); return; }
        LinkedNode<data_type>* current = head;
        for (int i = 1; i <= k - 1; ++i) current = current->next;
        insert(current, value);
    }

    // O(1)
    void pop_front() {
        if (!head) return;
        LinkedNode<data_type>* current = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete current;
        --sz;
    }

    // O(1)
    void erase(LinkedNode<data_type>* node) {
        if (node && node->next) {
            LinkedNode<data_type>* current = node->next;
            if (node->next == tail) tail = node;
            node->next = node->next->next;
            delete current;
            --sz;
        }
    }

    // O(k)
    void erase(int k) {
        if (k == 0) { pop_front(); return; }
        LinkedNode<data_type>* current = head;
        for (int i = 1; i <= k - 1; ++i) current = current->next;
        erase(current);
    }

    // O(n)
    void erase_value(data_type value) {
        LinkedNode<data_type>* prev = nullptr;
        LinkedNode<data_type>* current = head;
        while (current && current->data != value) { prev = current; current = current->next; }
        if (!current) return;
        if (!prev) head = current->next;        // era la cabeza
        else prev->next = current->next;
        if (current == tail) tail = prev;        // era la cola
        delete current;
        --sz;
    }

    // O(n)
    LinkedNode<data_type>* buscar(data_type value) {
        for (LinkedNode<data_type>* p = head; p; p = p->next)
            if (p->data == value) return p;
        return nullptr;
    }

    // O(k)
    LinkedNode<data_type>* at(int k) {
        if (k < 0 || k >= sz) return nullptr;
        LinkedNode<data_type>* current = head;
        while (k--) current = current->next;
        return current;
    }

    // O(n)
    void reverse() {
        LinkedNode<data_type>* prev = nullptr;
        LinkedNode<data_type>* current = head;
        tail = head;
        while (current) {
            LinkedNode<data_type>* nx = current->next;
            current->next = prev;
            prev = current;
            current = nx;
        }
        head = prev;
    }

    // O(n)
    void print() {
        LinkedNode<data_type>* current = head;
        while (current != nullptr) { cout << current->data << " "; current = current->next; }
        cout << '\n';
    }

    // O(n)
    void clear() {
        LinkedNode<data_type>* current = head;
        while (current) { LinkedNode<data_type>* nx = current->next; delete current; current = nx; }
        head = tail = nullptr;
        sz = 0;
    }
};

// ============================================================
// (b) ListNode suelto (estilo LeetCode/CF, como en merge_two_lab2.cpp).
//     Construye a mano y usa las funciones de 05_patrones_lista.cpp.
// ============================================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#ifdef LOCAL_MAIN
int main() {
    LinkedList<int> L;
    L.push_back(1); L.push_back(2); L.push_front(0);  // 0 1 2
    L.reverse();                                       // 2 1 0
    L.print();
    return 0;
}
#endif

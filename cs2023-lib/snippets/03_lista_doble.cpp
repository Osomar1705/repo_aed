// lista doble; lo bueno es borrar por puntero en O(1) y recorrer al reves
#include <bits/stdc++.h>
using namespace std;

template <typename data_type>
struct DListNode {
    data_type data;
    DListNode* prev;
    DListNode* next;
    DListNode(data_type data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename data_type>
struct DoublyLinkedList {
    DListNode<data_type>* head;
    DListNode<data_type>* tail;
    int sz;

    // O(1)
    DoublyLinkedList() { head = tail = nullptr; sz = 0; }
    // O(n)
    ~DoublyLinkedList() { clear(); }

    // O(1)
    int size() const { return sz; }
    // O(1)
    bool empty() const { return head == nullptr; }

    // O(1)
    void push_front(data_type value) {
        DListNode<data_type>* new_node = new DListNode<data_type>(value);
        new_node->next = head;
        if (head) head->prev = new_node;
        else tail = new_node;
        head = new_node;
        ++sz;
    }

    // O(1)
    void push_back(data_type value) {
        DListNode<data_type>* new_node = new DListNode<data_type>(value);
        new_node->prev = tail;
        if (tail) tail->next = new_node;
        else head = new_node;
        tail = new_node;
        ++sz;
    }

    // O(1)
    void pop_front() {
        if (!head) return;
        DListNode<data_type>* current = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete current;
        --sz;
    }

    // O(1)
    void pop_back() {
        if (!tail) return;
        DListNode<data_type>* current = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete current;
        --sz;
    }

    // O(1)
    void insert_before(DListNode<data_type>* node, data_type value) {
        if (!node) return;
        DListNode<data_type>* new_node = new DListNode<data_type>(value);
        new_node->next = node;
        new_node->prev = node->prev;
        if (node->prev) node->prev->next = new_node;
        else head = new_node;
        node->prev = new_node;
        ++sz;
    }

    // O(1)
    void insert_after(DListNode<data_type>* node, data_type value) {
        if (!node) return;
        DListNode<data_type>* new_node = new DListNode<data_type>(value);
        new_node->prev = node;
        new_node->next = node->next;
        if (node->next) node->next->prev = new_node;
        else tail = new_node;
        node->next = new_node;
        ++sz;
    }

    // O(1) real
    void erase(DListNode<data_type>* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        else head = node->next;
        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;
        delete node;
        --sz;
    }

    // O(n)
    DListNode<data_type>* buscar(data_type value) {
        for (DListNode<data_type>* p = head; p; p = p->next)
            if (p->data == value) return p;
        return nullptr;
    }

    // O(k)
    DListNode<data_type>* at(int k) {
        if (k < 0 || k >= sz) return nullptr;
        if (k <= sz / 2) {
            DListNode<data_type>* p = head;
            while (k--) p = p->next;
            return p;
        }
        DListNode<data_type>* p = tail;
        int j = sz - 1 - k;
        while (j--) p = p->prev;
        return p;
    }

    // O(n)
    vector<data_type> hacia_adelante() {
        vector<data_type> r;
        for (DListNode<data_type>* p = head; p; p = p->next) r.push_back(p->data);
        return r;
    }

    // O(n)
    vector<data_type> hacia_atras() {
        vector<data_type> r;
        for (DListNode<data_type>* p = tail; p; p = p->prev) r.push_back(p->data);
        return r;
    }

    // O(n)
    void clear() {
        DListNode<data_type>* current = head;
        while (current) { DListNode<data_type>* nx = current->next; delete current; current = nx; }
        head = tail = nullptr;
        sz = 0;
    }
};

#ifdef LOCAL_MAIN
int main() {
    DoublyLinkedList<int> L;
    L.push_back(1); L.push_back(2); L.push_back(3);
    L.erase(L.at(1));                 // borro el 2 en O(1)
    for (int x : L.hacia_adelante()) cout << x << ' ';
    cout << '\n';
    return 0;
}
#endif

// BST: insertar, buscar, borrar, recorridos
#include <bits/stdc++.h>
using namespace std;

template <typename data_type>
struct Treenode {
    data_type data;
    Treenode* left;
    Treenode* right;
    Treenode* parent;
    Treenode(data_type data = data_type(), Treenode* left = nullptr,
             Treenode* right = nullptr, Treenode* parent = nullptr)
        : data(data), left(left), right(right), parent(parent) {}
};

template <typename data_type>
struct bst {
    Treenode<data_type>* root;

    bst() : root(nullptr) {}
    ~bst() { destroy(root); }

    // O(altura) - bajo a izquierda/derecha comparando con la clave.
    bool search(data_type key) const {
        Treenode<data_type>* current = root;
        while (current != nullptr) {
            if (current->data == key) return true;
            if (key > current->data) current = current->right;
            else current = current->left;
        }
        return false;
    }

    // O(altura) - el minimo es el nodo mas a la izquierda.
    data_type min_element() const {
        Treenode<data_type>* current = root;
        while (current->left != nullptr) current = current->left;
        return current->data;
    }

    // O(altura) - el maximo es el nodo mas a la derecha.
    data_type max_element() const {
        Treenode<data_type>* current = root;
        while (current->right != nullptr) current = current->right;
        return current->data;
    }

    // O(altura) - bajo con puntero a puntero y cuelgo el nuevo nodo donde quede nulo.
    void insertar(data_type value) {
        Treenode<data_type>** current = &root;
        Treenode<data_type>* padre = nullptr;
        while (*current != nullptr) {
            padre = *current;
            if (value < (*current)->data) current = &((*current)->left);
            else if (value > (*current)->data) current = &((*current)->right);
            else return; // sin duplicados
        }
        *current = new Treenode<data_type>(value, nullptr, nullptr, padre);
    }

    // O(altura) - 3 casos: 0/1 hijo se reemplaza por el hijo; 2 hijos usa el sucesor.
    void erase(data_type value) { root = erase(root, value); }

    // O(n) - recorrido inorden (da los valores ordenados).
    void printInOrder() const { inorder(root); cout << '\n'; }

    // O(n) - vuelco inorden a un vector (util para verificar).
    vector<data_type> inorder_vec() const {
        vector<data_type> r;
        inorder_vec(root, r);
        return r;
    }

private:
    Treenode<data_type>* erase(Treenode<data_type>* u, data_type value) {
        if (u == nullptr) return nullptr;
        if (value < u->data) {
            u->left = erase(u->left, value);
            if (u->left) u->left->parent = u;
        } else if (value > u->data) {
            u->right = erase(u->right, value);
            if (u->right) u->right->parent = u;
        } else {
            if (u->left == nullptr || u->right == nullptr) {
                Treenode<data_type>* child = u->left ? u->left : u->right;
                if (child) child->parent = u->parent;
                delete u;
                return child;
            }
            // 2 hijos: copio el sucesor (minimo del subarbol derecho) y lo borro
            Treenode<data_type>* succ = u->right;
            while (succ->left) succ = succ->left;
            u->data = succ->data;
            u->right = erase(u->right, succ->data);
            if (u->right) u->right->parent = u;
        }
        return u;
    }
    void inorder(Treenode<data_type>* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void inorder_vec(Treenode<data_type>* node, vector<data_type>& r) const {
        if (!node) return;
        inorder_vec(node->left, r);
        r.push_back(node->data);
        inorder_vec(node->right, r);
    }
    void destroy(Treenode<data_type>* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

#ifdef LOCAL_MAIN
int main() {
    bst<int> arbol;
    for (int x : {10, 5, 15, 3, 7}) arbol.insertar(x);
    cout << "busqueda 7: " << arbol.search(7) << '\n';
    cout << "min: " << arbol.min_element() << " max: " << arbol.max_element() << '\n';
    arbol.erase(5);
    cout << "inorden tras borrar 5: "; arbol.printInOrder();
    return 0;
}
#endif

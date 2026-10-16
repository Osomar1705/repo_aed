// AVL = BST balanceado (BBST). Base: semana9/AVL.cpp. Compila SOLO.
// Mantiene |FB(v)| <= 1 en todo nodo, asi la altura es O(log n) garantizado.
#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int height; // altura del subarbol de este nodo (hoja = 0)
        TreeNode(data_type data = data_type(),
                 TreeNode* left = nullptr, TreeNode* right = nullptr,
                 TreeNode* parent = nullptr) :
                 data(data), left(left), right(right), parent(parent), height(0) {}
    };

    TreeNode* root;
    AVL() { root = nullptr; }
    ~AVL() { destroy(root); }

    // h(nulo) = -1, como en la definicion de la clase
    int height(TreeNode* u) { return u == nullptr ? -1 : u->height; }

    // recalcula la altura de u con las alturas de sus hijos
    void update(TreeNode* u) { u->height = 1 + max(height(u->left), height(u->right)); }

    // FB(v) = h(v.izq) - h(v.der); es AVL si |FB(v)| <= 1 en todo nodo
    int balance_factor(TreeNode* u) {
        return u == nullptr ? 0 : height(u->left) - height(u->right);
    }

    // v (hijo derecho de u) sube, u baja a la izquierda de v.
    // Devuelve v: quien la llame debe enlazarlo donde estaba u.
    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;
        u->right = v->left;
        if (u->right != nullptr) u->right->parent = u;
        v->left = u;
        v->parent = u->parent;
        u->parent = v;
        update(u); // u quedo abajo, se actualiza primero
        update(v);
        return v;
    }

    // v (hijo izquierdo de u) sube, u baja a la derecha de v.
    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;
        u->left = v->right;
        if (u->left != nullptr) u->left->parent = u;
        v->right = u;
        v->parent = u->parent;
        u->parent = v;
        update(u);
        update(v);
        return v;
    }

    // Actualiza altura de u y, si |FB(u)| = 2, aplica uno de los 4 casos.
    //  FB(u) = +2 y FB(izq) >= 0 : LL -> rotacion derecha en u
    //  FB(u) = +2 y FB(izq) <  0 : LR -> izquierda en hijo izq, luego derecha en u
    //  FB(u) = -2 y FB(der) <= 0 : RR -> rotacion izquierda en u
    //  FB(u) = -2 y FB(der) >  0 : RL -> derecha en hijo der, luego izquierda en u
    TreeNode* rebalance(TreeNode* u) {
        update(u);
        int bf = balance_factor(u);
        if (bf > 1) {
            if (balance_factor(u->left) < 0) u->left = rotate_left(u->left);
            return rotate_right(u);
        }
        if (bf < -1) {
            if (balance_factor(u->right) > 0) u->right = rotate_right(u->right);
            return rotate_left(u);
        }
        return u;
    }

    // O(log n) - busqueda iterativa, igual que en un BST.
    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) return true;
            if (current->data > key) current = current->left;
            else current = current->right;
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u->left != nullptr) u = u->left;
        return u;
    }
    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u->right != nullptr) u = u->right;
        return u;
    }
    TreeNode* min_element() { return min_element(root); }
    TreeNode* max_element() { return max_element(root); }

    // Insercion recursiva: baja hasta el lugar y al regresar cada ancestro
    // se rebalancea y devuelve la raiz de su subarbol (puede cambiar por rotacion).
    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value);
        if (value < u->data) { u->left = insert(u->left, value); u->left->parent = u; }
        else if (value > u->data) { u->right = insert(u->right, value); u->right->parent = u; }
        else return u; // sin duplicados
        return rebalance(u);
    }
    void insert(data_type value) {
        root = insert(root, value);
        root->parent = nullptr;
    }

    // Eliminacion recursiva, mismo esquema que insert.
    TreeNode* erase(TreeNode* u, data_type value) {
        if (u == nullptr) return nullptr;
        if (value < u->data) {
            u->left = erase(u->left, value);
            if (u->left != nullptr) u->left->parent = u;
        } else if (value > u->data) {
            u->right = erase(u->right, value);
            if (u->right != nullptr) u->right->parent = u;
        } else {
            if (u->left == nullptr or u->right == nullptr) {
                // 0 o 1 hijo: el hijo (o nullptr) ocupa su lugar
                TreeNode* child = (u->left != nullptr) ? u->left : u->right;
                if (child != nullptr) child->parent = u->parent;
                delete u;
                return child;
            }
            // 2 hijos: copiar el sucesor y borrarlo del subarbol derecho
            TreeNode* succ = min_element(u->right);
            u->data = succ->data;
            u->right = erase(u->right, succ->data);
            if (u->right != nullptr) u->right->parent = u;
        }
        return rebalance(u);
    }
    void erase(data_type value) {
        root = erase(root, value);
        if (root != nullptr) root->parent = nullptr;
    }

    // O(n) - recorridos recursivos.
    void inorder(TreeNode* u, vector<data_type>& r) {
        if (!u) return;
        inorder(u->left, r); r.push_back(u->data); inorder(u->right, r);
    }
    vector<data_type> inorder_vec() { vector<data_type> r; inorder(root, r); return r; }

    // devuelve la altura real (nulo = -1), o -2 si hay balance/altura/parent incorrecto
    int check(TreeNode* u, TreeNode* expected_parent) {
        if (u == nullptr) return -1;
        if (u->parent != expected_parent) return -2;
        int hl = check(u->left, u), hr = check(u->right, u);
        if (hl == -2 or hr == -2) return -2;
        if (abs(hl - hr) > 1) return -2;
        if (u->height != 1 + max(hl, hr)) return -2;
        return 1 + max(hl, hr);
    }
    bool is_avl() { return check(root, nullptr) != -2; }

private:
    void destroy(TreeNode* u) {
        if (!u) return;
        destroy(u->left); destroy(u->right); delete u;
    }
};

#ifdef LOCAL_MAIN
int main() {
    // ejemplo de clase: insertar 10 20 30 40 50 25
    AVL<int> e;
    for (int x : {10, 20, 30, 40, 50, 25}) e.insert(x);
    cout << "preorder esperado 30 20 10 25 40 50, inorder: ";
    for (int x : e.inorder_vec()) cout << x << ' ';
    cout << "\nes AVL: " << e.is_avl() << '\n';
    return 0;
}
#endif

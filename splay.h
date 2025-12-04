#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
    T value;
    Node *left, *right, *parent;

    Node<T>* succesor();
    Node<T>* rot_right(Node<T>*);
    Node<T>* rot_left(Node<T>*);
    Node<T>* splay(Node<T>*, Node<T>*);

public:
    Node(T);
    Node(T, Node<T>*, Node<T>*, Node<T>*);
    Node<T>* add(T);
    Node<T>* find(T);
    Node<T>* remove(T);
    void inorder(std::stringstream&) const;
    void preorder(std::stringstream&) const;

    friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
    : value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            return left->add(val);
        } else {
            left = new Node<T>(val);
            left->parent = this;
            return left;
        }
    } else {
        if (right != 0) {
            return right->add(val);
        } else {
            right = new Node<T>(val);
            right->parent = this;
            return right;
        }
    }
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    } else if (val < value) {
        if (left != 0)
            return left->find(val);
        else
            return this;
    } else {
        if (right != 0)
            return right->find(val);
        else
            return this;
    }
}

template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *p = this;
    Node<T> *c = this->right;

    if (c == 0) {
        return 0;
    }

    if (c->left == 0) {
        this->right = c->right;
        if (c->right) {
            c->right->parent = this;
        }
        c->right = 0;
        c->parent = 0;
        return c;
    }

    while (c->left != 0) {
        p = c;
        c = c->left;
    }
    p->left = c->right;
    if (p->left != 0) {
        p->left->parent = p;
    }
    c->right = 0;
    c->parent = 0;
    return c;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x) {
    Node<T> *y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->right = x;
    y->parent = x->parent;
    x->parent = y;
    if (y->parent) {
        if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->left = x;
    y->parent = x->parent;
    x->parent = y;
    if (y->parent) {
        if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x) {
    if (x == 0) return root;

    while (x->parent != 0) {
        if (x->parent->parent == 0) {
            if (x->parent->left == x) {
                rot_right(x->parent);
            } else {
                rot_left(x->parent);
            }
        } else {
            Node<T> *p = x->parent;
            Node<T> *g = p->parent;

            if (p->left == x && g->left == p) {
                rot_right(g);
                rot_right(p);
            } else if (p->right == x && g->right == p) {
                rot_left(g);
                rot_left(p);
            } else if (p->left == x && g->right == p) {
                rot_right(p);
                rot_left(g);
            } else {
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return x;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
    Node<T> *p = 0;
    if (val < value) {
        if (left != 0) {
            if (left->value == val) {
                Node<T> *old = left;
                p = this;

                if (old->left == 0 || old->right == 0) {
                    Node<T> *child = (old->left != 0) ? old->left : old->right;
                    left = child;
                    if (child) child->parent = this;
                } else {
                    Node<T> *succ = old->succesor(); 
                    left = succ;
                    succ->left = old->left;
                    if (succ->left) succ->left->parent = succ;
                    succ->right = old->right;
                    if (succ->right) succ->right->parent = succ;
                    succ->parent = this;
                    p = succ;
                }

                delete old;
                return p;
            } else {
                return left->remove(val);
            }
        }
    } else if (val > value) {
        if (right != 0) {
            if (right->value == val) {
                Node<T> *old = right;
                p = this;

                if (old->left == 0 || old->right == 0) {
                    Node<T> *child = (old->left != 0) ? old->left : old->right;
                    right = child;
                    if (child) child->parent = this;
                } else {
                    Node<T> *succ = old->succesor();
                    right = succ;
                    succ->left = old->left;
                    if (succ->left) succ->left->parent = succ;
                    succ->right = old->right;
                    if (succ->right) succ->right->parent = succ;
                    succ->parent = this;
                    p = succ;
                }

                delete old;
                return p;
            } else {
                return right->remove(val);
            }
        }
    }
    return this;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        aux << " ";
        right->inorder(aux);
    }
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
class SplayTree {
private:
    Node<T> *root;

public:
    SplayTree();
    ~SplayTree();
    bool empty() const;
    void add(T);
    bool find(T);
    void remove(T);
    std::string inorder() const;
    std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
}

template <class T>
bool SplayTree<T>::empty() const {
    return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {
    if (root != 0) {
        Node<T>* added = root->add(val);
        root = root->splay(root, added);
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
bool SplayTree<T>::find(T val) {
    if (root != 0) {
        Node<T>* found = root->find(val);
        root = root->splay(root, found);
        return (root->value == val);
    } else {
        return false;
    }
}

template <class T>
void SplayTree<T>::remove(T val) {
    if (root != 0) {
        if (val == root->value) {
            Node<T> *old = root;
            Node<T> *succ = root->succesor(); 

            if (succ != 0) {
                succ->left = old->left;
                if (succ->left)
                    succ->left->parent = succ;

                succ->right = old->right;
                if (old->right == succ) { 
                } else if (succ->right) {
                    succ->right->parent = succ;
                } else {
                    succ->right = old->right;
                    if (succ->right)
                        succ->right->parent = succ;
                }

                succ->parent = 0;
            } else if (root->left) { 
                succ = root->left;
                succ->parent = 0;
            }

            delete old;
            root = succ;

        } else {
            Node<T>* p = root->remove(val);
            
            if (p != root) { 
                root = root->splay(root, p);
            }
        }
    }
}

template <class T>
std::string SplayTree<T>::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif /* SPLAY_H_ */

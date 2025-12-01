#include <vector>
#include <string>
#include <sstream>

#include <iostream>
using namespace std;

/* QUEUE*/

template <class T>
class Queue {
public:
	virtual void enqueue(T) = 0;
	virtual void dequeue()  = 0 ;
	virtual T front() const  = 0 ;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
};

template <class T>
class QueueVector : public Queue<T> {
private:
	vector<T> data;

public:
    QueueVector();
	QueueVector(int);
	~QueueVector();
	void enqueue(T) ;
	void dequeue() ;
	T front() const ;
	bool empty() const;
	bool full() const;
	void clear();
};

template <class T>
QueueVector<T>::QueueVector() : data(0) {}
/* if (data == 0){
    OutOfMemory();
} */

template <class T>
QueueVector<T>::QueueVector(int sze) : data(sze) {}

template <class T>
QueueVector<T>::~QueueVector() {
	clear();
}

template <class T>
bool QueueVector<T>::empty() const {
    return (data.empty())? true : false;
}

template <class T>
bool QueueVector<T>::full() const {
    return false;
}

template <class T>
void QueueVector<T>::enqueue(T val)  {
    /* if(full()){
       throw Overflow();
    } */
    data.push_back(val);
}

template <class T>
T QueueVector<T>::front() const  {
	/* if(empty()){throw NoSuchElement();} */
    return data.front();
}

template <class T>
void QueueVector<T>::dequeue()  {
    /* if(empty()){
        throw NoSuchElement();
    } */
    data.erase(data.begin()); 
}

template <class T>
void QueueVector<T>::clear() {
    data.clear();
}

/* QUEUE*/


template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode<T> *left, *right;

	TreeNode<T>* predecesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T val);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(stringstream &aux) const;
	void preorder(stringstream &aux) const;
    void postorder(stringstream &aux) const;
    void levbylev(std::stringstream &aux, QueueVector<TreeNode<T>*>* q) const;
    int height();
    string ancestors(stringstream &aux, T val);
    int whatlevelamI(T val);

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) {
	value = val;
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) {
	value = val;
	left = le;
	right = ri;
}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
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
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
    if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

template <class T>
void TreeNode<T>::levbylev(std::stringstream &aux, QueueVector<TreeNode<T>*>* q) const{
    while (q->empty() != true){
        TreeNode<T>* val = q->front();
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << val->value;
        q->dequeue();
        if (val->left != 0){
            q->enqueue(val->left);
        }
        if (val->right != 0){
            q->enqueue(val->right);
        }
    }
    return;
}

template<class T>
int TreeNode<T>::height(){
    int izq;
    int der;
    if (this->left != 0){
        izq = this->left->height();
    }
    else {izq = 0;}
    if (this->right != 0){
        der = this->right->height();
    }
    else {der = 0;}
    if (der > izq){
        return 1 + der;
    }
    return 1 + izq;
}

template<class T>
string TreeNode<T>::ancestors(stringstream &aux, T val){
    if (this->value == val){
        return aux.str();
    }
    else if(this->value > val && this->left != 0){
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << this->value;
        return this->left->ancestors(aux, val);
    }
    else if (this->value < val && this->right != 0) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << this->value;
        return this->right->ancestors(aux, val);
    }
    aux.str("");
    return aux.str();
}

template<class T>
int TreeNode<T>::whatlevelamI(T val){
    int izq;
    int der;
    if (this->value == val){
        return 1;
    }
    else if (val < this->value && this->left != 0){
        int lev = this->left->whatlevelamI(val);
        return (lev != -1) ? (1 + lev) : -1;
    }
    else if (val > this->value && this->right != 0){
        int lev = this->right->whatlevelamI(val);
        return (lev != -1) ? (1 + lev) : -1;
    }
    return -1;
}

template <class T>
class BST{
    private:
        TreeNode<T>* root;

        string inorder() const;
        string preorder() const;
        string postorder() const;
        string levbylev() const;

    public:
        BST ();
        void add(T val);
        string visit();
        int height();
        string ancestors(T val);
        int whatlevelamI(T val);
        bool empty() const;
};

template <class T>
BST<T>::BST(){
    root = NULL;
}
template <class T>
bool BST<T>::empty() const{
    if (root == 0){
        return true;
    }
    return false;
}

template<class T>
void BST<T>::add(T val){
    TreeNode<T>* p = new TreeNode<T>(val);
    /* if (p == 0){
        throw OutOfMemory();
    } */
    if (this->empty() != true){
        root->add(val);
    }
    else{
        root = p;
    }
    return;
}

template<class T>
string BST<T>::visit(){
    stringstream aux;

    aux << this->preorder() << "\n";
    aux << this->inorder() << "\n";
    aux << this->postorder() << "\n";
    aux << this->levbylev();
    

    return aux.str();
}

template<class T>
int BST<T>::height(){
    if (!empty()){
        return root->height();
    }
    return -1;
}

template<class T>
string BST<T>::ancestors(T val){
    stringstream aux;

	aux << "[";
	if (!empty()) {
		root->ancestors(aux, val);
	}
    if (aux.str() != ""){
	    aux << "]";
    }
    else{
        aux.str("[]");
    }
	return aux.str();
}

template<class T>
int BST<T>::whatlevelamI(T val){
    if (!empty()){
        return root->whatlevelamI(val);
    }
    return -1;
}

template <class T>
string BST<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::postorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::levbylev() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
        QueueVector<TreeNode<T>*>* q = new QueueVector<TreeNode<T>*>();
        q->enqueue(root);
		root->levbylev(aux, q);
        delete q;
	}
	aux << "]";
	return aux.str();
}

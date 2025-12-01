#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) {
	value = val;
}

template <class T>
Link<T>::Link(T val, Link* nxt) {
	value = val;
	next = nxt;
}

template <class T>
Link<T>::Link(const Link<T> &source) {
	value = source(value);
	next = source(next);
}


template <class T>
class List{
    private:
        Link<T> *head;
	    int 	size;
    public:
        List();
        List(const List<T>&);
        ~List();
        void clear();

        string toString() const;
        bool empty() const;
        void insertion(T val);
        int search(T val);
        void update(int index, T val);
        T deleteAt(int index);
};

template <class T>
List<T>::List(){
	head = NULL;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
List<T>::List(const List<T> &source)  {
    head = source.head;
    size = source.size;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
bool List<T>::empty() const {
	if (size == 0){
		return true;
	}
	return false;
}

template <class T>
void List<T>::insertion(T val){
    Link<T> *newLink, *p;

	newLink = new Link<T>(val, NULL);
	//if (newLink == 0){
	//	throw OutOfMemory();
	//}

    if (empty()){
        head = newLink;
    }
    else{
        p = head;
        while (p->next != NULL){
            p = p->next;
        }

        p->next = newLink;
    }

	size = size + 1;
	return;
}

template <class T>
int List<T>::search(T val){
    Link<T>* p = head;
    for (int i = 1; i <= size; i++){
        if (p->value == val){
            return i - 1;
        }
        p = p->next;
    }
    return -1;
}

template <class T>
void List<T>::update(int index, T val){
    if (index < 0 || index > size -1){
        return;
    }
    Link<T>* p = head;
    for (int i = 1; i <= index; i++){
        p = p->next;
    }
    p->value = val;
    return;
}

template <class T>
T List<T>::deleteAt(int index){
    //if (index < 0 || index > size -1){
    //    throw std::out_of_range;
    //}
    int v;
    Link<T>* t;
    if (index == 0){
        v = head->value;
        t = head->next;
        head->next = NULL;
        delete head;
        head = t;
    }
    else{
        Link<T>* p = head;
        for (int i = 0; i <= index-2; i++){
            p = p->next;
        }
        v = p->next->value;
        t = p->next->next;
        p->next->next = NULL;
        delete p->next;
        p->next = t;
    }
    size = size -1;

    return v;
}

template <class T>
void List<T>::clear() {
    if (empty()){
        return;
    }

    Link<T>* p = head;
    Link<T>* t;
	for (int i = 0; i <size; i++){
        t = p->next;
        p->next = NULL;
        delete p;
        p = t;
	}
	
	head = NULL;
	size = 0;
    return;	
}

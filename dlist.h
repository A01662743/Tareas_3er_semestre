#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

template <class T> class DList;

template<class T>
class DLink {
    private:
        T value;
        DLink<T>* previous;
        DLink<T>* next;

        friend class DList<T>;
    public:
        DLink(T val);
        DLink(T val, DLink<T>* prev, DLink<T>* nxt);
};

template<class T>
DLink<T>::DLink(T val){
    value = val;
    previous = 0;
    next = 0;
}

template<class T>
DLink<T>::DLink(T val, DLink<T>* prev, DLink<T>* nxt){
    value = val;
    previous = prev;
    next = nxt;
}

template<class T>
class DList{
    private:
        DLink<T>* head;
        DLink<T>* tail;
        int size;
    public:
        DList();
        DList(const DList& source);
        ~DList();
        string toStringForward() const;
        string toStringBackward() const;
        void insertion(int val);
        int search(T val);
        void update(int idx, T val);
        void deleteAt(int idx);
        void clear();
        bool empty() const;
};

template<class T>
DList<T>::DList(){
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source)  {
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		/*if (head == 0) {
			throw OutOfMemory();
		}*/
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			/*if (q->next == 0) {
				throw OutOfMemory();
			}*/
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template<class T>
DList<T>::~DList(){
    clear();
}

template <class T>
string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

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
string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template<class T>
void DList<T>::insertion(int val){
    DLink<T>* p = new DLink<T>(val);
    /*if (p == 0){
        throw OutOfMemory();
    }*/
    if (empty()){
        head = p;
        tail = p;
    }
    else{
        tail->next = p;
        p->previous = tail;
        tail = p;
    }
    size++;
}

template<class T>
int DList<T>::search(T val){
    if (empty()){
        return -1;
    }
    DLink<T>* p = head;
    for(int i = 0; i < size; i++){
        if(p->value == val){
            return i;
        }
        p = p->next;
    }
    return -1;
}

template<class T>
void DList<T>::update(int idx, T val){
    /*if (idx < 0 || idx >= size){
        IndexOutOfRange();
    }*/
    DLink<T>* q;
    /*if (q == 0){
        throw OutOfMemory();
    }*/
    if (idx <= (size-1)/2){
        q = head;
        for (int i = 1; i <= idx; i++){
            q = q->next;
        }
    }
    else{
        q = tail;
        for (int i = size-1-1; i >= idx; i--){
            q = q->previous;
        }
    }
    q->value = val;
}

template<class T>
void DList<T>::deleteAt(int idx){
    /*if (idx >= size || idx < 0){
        throw IndexOutOfRange();
    }*/
    DLink<T>* q;
    if (idx <= (size-1)/2){
        q = head;
        for (int i = 1; i <= idx; i++){
            q = q->next;
        }
        if (q->next != 0){
            q->next->previous = q->previous;
        }
        else{
            tail = q->previous;
        }
        if (q->previous != 0){
            q->previous->next = q->next;
        }
        else{
            head = q->next;
        }
    }
    else{
        q = tail;
        for (int i = size-1; i > idx; i--){
            q = q->previous;
        }
        if (q->next != 0){
            q->next->previous = q->previous;
        }
        else{
            tail = q->previous;
        }
        if (q->previous != 0){
            q->previous->next = q->next;
        }
        else{
            head = q->next;
        }
    }
    delete q;
    size--;
}

template <class T>
bool DList<T>::empty() const {
	if (size == 0){
		return true;
	}
	return false;
}

template<class T>
void DList<T>::clear() {
    if (empty()){
        return;
    }

    DLink<T>* p = head;
    DLink<T>* t;
	for (int i = 0; i <size; i++){
        t = p->next;
        p->next = NULL;
        delete p;
        p = t;
	}
	
	head = NULL;
    tail = NULL;
	size = 0;
    return;	
}

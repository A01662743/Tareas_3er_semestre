#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template <class T>
class Heap {
    private:
        T* data;
        int count;
        int tamano;

        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);

    public:
        Heap(int);
        void push(T);
        string toString() const;
        T pop();
        T top();
        bool empty();
        int size();
};

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const{
	return (pos/2);
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const{
    return (pos*2);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const{
    return (pos*2 + 1);
}

template <class T>
void Heap<T>::swap(unsigned int pos1, unsigned int pos2){
    T val = data[pos1];
    data[pos1] = data[pos2];
    data[pos2] = val;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]){
		min = le;
	}
	if (ri <= count && data[ri] < data[min]){
		min = ri;
	}
	if (min != pos){
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
Heap<T>::Heap(int sze){
    data = new T[sze+1];
    //if (data != 0){
        //throw OutOfSpace();
    //}
    tamano = sze;
    count = 0;
}

template <class T>
void Heap<T>::push(T val){
    if (empty()){
        data[1] = val;
        count++;
    }
    else if (count+1 < tamano){
        count++;
        data[count] = val;
        int i = count;
        while (i != 1 && val < data[parent(i)]){
            swap(i, parent(i));
            i = parent(i);
        }
    }
}

template <class T>
bool Heap<T>::empty(){
    return (count == 0);
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (unsigned int i = 1; i <= count; i++) {
		if (i != 1) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

template <class T>
T Heap<T>::pop(){
	T aux;
	if (!empty()){
		aux = data[1];
		data[1] = data[count--];
		int i = 1;
		T val = data[1];
		while (i < count && (val > data[left(i)] || val > data[right(i)])){
			if (val > data[left(i)]){
				swap(i, left(i));
				i = left(i);
			}
			else if (val > data[right(i)]){
				swap(i, right(i));
				i = right(i);
			}
		}
		return aux;
	}
	//else{
		//throw NoSuchElement();
	//}
    return aux;
}

template <class T>
T Heap<T>::top(){
    //if (empty()){
        //throw NoSuchElement();
    //}
    return data[1];
}

template <class T>
int Heap<T>::size(){
    return count;
}

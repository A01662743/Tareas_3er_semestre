#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

template <typename T>
void print(vector<T> vec){
for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

template <typename T>
class Sorts{
    public:
    void ordenaSeleccion(vector<T>& vec);
    void ordenaBurbuja(vector<T>& vec);
    void ordenaMerge(vector<T>& vec);
    int busqSecuencial(vector<T>& vec, int res);
    int busqBinaria(vector<T>& vec, int res);

    private:
    int mergeSort (const vector<T>& vec, vector<T>& vec2, int low, int mid, int high);
    void mergeSplit (vector<T>& vec, vector<T>& vec2, int low, int high);
    void copy(vector<T>& vec, const vector<T>& vec2, int low, int high);
};

template <typename T>
void Sorts<T>::ordenaSeleccion(vector<T>& vec){
    int pos;
    int size = vec.size()-1;
    for (int i = 0; i <= size-1; i++){
        pos = i;
        for (int j = i+1; j <= size; j++){
            if (vec[pos] > vec[j]){
                pos = j;
            }
        }
        if (pos != i){
            swap(vec[i], vec[pos]);
        }
    }
    return;
}

template <typename T>
void Sorts<T>::ordenaBurbuja(vector<T>& vec){
    int size = vec.size()-1;
    for (int j = size; j > 0; j--){
        for (int i = 0; i <= j-1; i++){
            if (vec[i] > vec[i+1]){
                swap(vec[i], vec[i+1]);
            }
        }
    }
}

template<typename T>
void Sorts<T>::copy(vector<T>& vec, const vector<T>& vec2, int low, int high){
    for (int i = low; i<=high; i++){
        vec[i] = vec2[i];
    }
}

template <typename T>
int Sorts<T>::mergeSort(const vector<T>& vec, vector<T>& vec2, int low, int mid, int high){
    int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid &&j <= high) {
		if (vec[i] < vec[j]) {
			vec2[k] = vec[i];
			i++;
		} else {
			vec2[k] = vec[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			vec2[k] = vec[j];
            k++;
		}
	} else {
		for (; i <= mid; i++) {
			vec2[k] = vec[i];
            k++;
		}
	}
    return 1;
}

template <typename T>
void Sorts<T>::mergeSplit (vector<T>& vec, vector<T>& vec2, int low, int high){
    if (low >= high){
        return;
    }
    int mid = (low + high)/2;
    mergeSplit (vec, vec2, low, mid);
    mergeSplit (vec, vec2, mid+1, high);
    mergeSort (vec, vec2, low, mid, high);
    copy(vec, vec2, low, high);
}

template <typename T>
void Sorts<T>::ordenaMerge(vector<T>& vec){
    vector<T> vec2(vec.size());
    mergeSplit (vec, vec2, 0, vec.size()-1);
    return;
}

template <typename T>
int Sorts<T>::busqSecuencial(vector<T>& vec, int res){
    int size = vec.size()-1;
	for (int i=0; i<=size; i++) {
		if (vec[i] == res) return i;
	}
	return -1;
}

template <typename T>
int Sorts<T>::busqBinaria(vector<T>& vec, int res){
    int sup = vec.size()-1;
    int inf = 0;
    while (sup >= inf){
        int mid = (sup+inf)/2;
        if (res < vec[mid]){
            sup = mid - 1;
        }
        else if (res > vec[mid]){
            inf = mid + 1;
        }
        else{ return mid; }
    }
    return -1;
}

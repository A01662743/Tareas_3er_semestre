#include <iostream>

class Funciones {
public:
    int sumaIterativa (int n){
        int sum = 0;
        for (int i = 0; i <=n; i++) {
            sum = sum + i;
        }
        return sum;
    }

    int sumaRecursiva (int n) {
        if (n == 0) {
            return 0;
        }
        else {
            return n + sumaRecursiva(n-1);
        }
    }

    int sumaDirecta (int n) {
        return n * (n + 1) / 2;
    }
};

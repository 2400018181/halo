
#include <iostream>
using namespace std;

#define MAKS 10

class Array1D {
public:
    char A[MAKS];

   
    Array1D() {
        for (int i = 0; i < MAKS; i++) {
            A[i] = 'A' + i; 
        }
    }

    void cetak() {
        for (int i = 0; i < MAKS; i++)
            cout << A[i] << " ";
        cout << endl;
    }

    void geserKanan() {
        char temp = A[MAKS - 1]; 
        for (int i = MAKS - 1; i > 0; i--) {
            A[i] = A[i - 1]; 
        }
        A[0] = temp; 
    }

   void geserKiri() {
        char temp = A[0];
        for (int i = 0; i < MAKS - 1; i++)
            A[i] = A[i + 1];
        A[MAKS - 1] = temp;
    }
};

int main() {
    Array1D array;

    cout << "Isi awal array: ";
    array.cetak();

    array.geserKanan();
    cout << "Setelah digeser ke kanan: ";
    array.cetak();

    array.geserKiri();
    cout << "Setelah digeser ke kiri: ";
    array.cetak();

    return 0;
}


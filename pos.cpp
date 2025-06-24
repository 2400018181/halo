#include <iostream>
using namespace std;

class ArrayProcessor {
private:
    int matrix[3][3];
    int array1D[9];
    
public:
    void inputMatrix() {
        cout << "Masukkan elemen matrix 3x3:" << endl;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << "Elemen[" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
        }
    }
    
    void displayMatrix() {
        cout << "\nMatrix 3x3:" << endl;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void convertTo1D() {
        int index = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                array1D[index] = matrix[i][j];
                index++;
            }
        }
    }
    
    void display1D() {
        cout << "\nArray 1D setelah diurutkan: ";
        for(int i = 0; i < 9; i++) {
            cout << array1D[i] << " ";
        }
        cout << endl;
    }
    
    void bubbleSortDescending() {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8 - i; j++) {
                if(array1D[j] < array1D[j + 1]) {
                    int temp = array1D[j];
                    array1D[j] = array1D[j + 1];
                    array1D[j + 1] = temp;
                }
            }
        }
    }
    

    void displaySorted() {
        cout << "\nArray setelah diurutkan pake descending: ";
        for(int i = 0; i < 9; i++) {
            cout << array1D[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ArrayProcessor processor;
    
    processor.inputMatrix();

    processor.displayMatrix();
    
    processor.convertTo1D();

    processor.display1D();
    
    processor.bubbleSortDescending();
    
    processor.displaySorted();
    
    return 0;
}


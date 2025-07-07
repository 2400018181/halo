#include <iostream>
#include <string>
using namespace std;

const int MAKS_DATA = 100;

class DataManager {
private:
    int data[MAKS_DATA];
    int jumlah;

public:
    DataManager() {
        jumlah = 0;
    }

    void inputData(int n) {
        if (n > MAKS_DATA) n = MAKS_DATA;
        jumlah = n;
        for (int i = 0; i < jumlah; i++) {
            cout << "Data ke-" << i + 1 << ": ";
            cin >> data[i];
        }
    }

    void tampilkanData() {
        cout << "Data saat ini: ";
        for (int i = 0; i < jumlah; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void bubbleSort() {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
        cout << "Data berhasil diurutkan.\n";
    }

    void cariData(int target) {
        bool ditemukan = false;
        for (int i = 0; i < jumlah; i++) {
            if (data[i] == target) {
                cout << "Data ditemukan di indeks ke-" << i << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan.\n";
        }
    }
};

bool login() {
    string username;
    cout << "===== LOGIN =====\n";
    cout << "Masukkan username: ";
    cin >> username;
    
    if (username == "admin") {
        cout << "Login berhasil.\n\n";
        return true;
    } else {
        cout << "Login gagal. Username salah.\n";
        return false;
    }
}

int main() {
    if (!login()) return 0;

    DataManager manager;
    int pilihan;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Urutkan Data (Bubble Sort)\n";
        cout << "4. Cari Data\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            int n;
            cout << "Jumlah data yang ingin dimasukkan: ";
            cin >> n;
            manager.inputData(n);
            break;
        case 2:
            manager.tampilkanData();
            break;
        case 3:
            manager.bubbleSort();
            break;
        case 4:
            int target;
            cout << "Masukkan nilai yang ingin dicari: ";
            cin >> target;
            manager.cariData(target);
            break;
        case 5:
            cout << "Terima kasih!\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);

    return 0;
}


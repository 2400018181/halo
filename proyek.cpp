#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Mahasiswa {
public:
    string nim;
    string nama;
    string prodi;
    string noHp;
    
    Mahasiswa(string n, string nm, string pr, string hp) 
        : nim(n), nama(nm), prodi(pr), noHp(hp) {}
    
    Mahasiswa() {}
    
    void display() const {
        cout << "NIM: " << nim << " | Nama: " << nama 
             << " | Prodi: " << prodi << " | No.HP: " << noHp << endl;
    }
};

class SistemMahasiswa {
private:
    vector<Mahasiswa> dataMahasiswa;
    
public:
    void tambahMahasiswa() {
        string nim, nama, prodi, noHp;
        cout << "\n=== Tambah Data Mahasiswa ===" << endl;
        cout << "Masukkan NIM: ";
        cin >> nim;
        cin.ignore(); 
        cout << "Masukkan Nama: ";
        getline(cin, nama);
        cout << "Masukkan Prodi: ";
        getline(cin, prodi);
        cout << "Masukkan No.HP: ";
        getline(cin, noHp);
        
        dataMahasiswa.push_back(Mahasiswa(nim, nama, prodi, noHp));
        cout << "Data mahasiswa berhasil ditambahkan!" << endl;
    }
    
    int cariMahasiswaByNIM(const string& nim) {
        vector<pair<string, int>> nimIndex;
        for (int i = 0; i < dataMahasiswa.size(); i++) {
            nimIndex.push_back({dataMahasiswa[i].nim, i});
        }
        sort(nimIndex.begin(), nimIndex.end());
        
        int left = 0, right = nimIndex.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nimIndex[mid].first == nim) {
                return nimIndex[mid].second; 
            }
            if (nimIndex[mid].first < nim) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; 
    }
    
    void cariMahasiswa() {
        if (dataMahasiswa.empty()) {
            cout << "Belum ada data mahasiswa!" << endl;
            return;
        }
        
        string nim;
        cout << "\n=== Cari Mahasiswa ===" << endl;
        cout << "Masukkan NIM yang dicari: ";
        cin >> nim;
        
        int index = cariMahasiswaByNIM(nim);
        if (index != -1) {
            cout << "\nMahasiswa ditemukan:" << endl;
            dataMahasiswa[index].display();
        } else {
            cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
        }
    }
    
    void urutkanAscending() {
        if (dataMahasiswa.empty()) {
            cout << "Belum ada data mahasiswa!" << endl;
            return;
        }
        
        for (int i = 0; i < dataMahasiswa.size() - 1; i++) {
            for (int j = 0; j < dataMahasiswa.size() - i - 1; j++) {
                if (dataMahasiswa[j].nim > dataMahasiswa[j + 1].nim) {
                    Mahasiswa temp = dataMahasiswa[j];
                    dataMahasiswa[j] = dataMahasiswa[j + 1];
                    dataMahasiswa[j + 1] = temp;
                }
            }
        }
        
        cout << "\nData berhasil diurutkan secara ascending berdasarkan NIM:" << endl;
        tampilkanSemuaData();
    }
    
    void urutkanDescending() {
        if (dataMahasiswa.empty()) {
            cout << "Belum ada data mahasiswa!" << endl;
            return;
        }
        
        for (int i = 0; i < dataMahasiswa.size() - 1; i++) {
            for (int j = 0; j < dataMahasiswa.size() - i - 1; j++) {
                if (dataMahasiswa[j].nim < dataMahasiswa[j + 1].nim) {
                    Mahasiswa temp = dataMahasiswa[j];
                    dataMahasiswa[j] = dataMahasiswa[j + 1];
                    dataMahasiswa[j + 1] = temp;
                }
            }
        }
        
        cout << "\nData berhasil diurutkan secara descending berdasarkan NIM:" << endl;
        tampilkanSemuaData();
    }
    
    void tampilkanSemuaData() {
        if (dataMahasiswa.empty()) {
            cout << "Belum ada data mahasiswa!" << endl;
            return;
        }
        
        cout << "\n=== Data Semua Mahasiswa ===" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < dataMahasiswa.size(); i++) {
            cout << (i + 1) << ". ";
            dataMahasiswa[i].display();
        }
        cout << "----------------------------------------" << endl;
        cout << "Total: " << dataMahasiswa.size() << " mahasiswa" << endl;
    }
    

};

int main() {
    SistemMahasiswa sistem;
    int pilihan;
    
    cout << "=== SISTEM PENGELOLAAN DATA MAHASISWA ===" << endl;
    cout << "=========================================" << endl;
    
    do {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Tambah Data Mahasiswa" << endl;
        cout << "2. Cari Mahasiswa (berdasarkan NIM)" << endl;
        cout << "3. Tampilkan Semua Data" << endl;
        cout << "4. Urutkan Ascending" << endl;
        cout << "5. Urutkan Descending" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                sistem.tambahMahasiswa();
                system("pause");
            	system("cls");
                break;
            case 2:
                sistem.cariMahasiswa();
                system("pause");
            	system("cls");
                break;
            case 3:
                sistem.tampilkanSemuaData();
                system("pause");
            	system("cls");
                break;
            case 4:
                sistem.urutkanAscending();
                system("pause");
            	system("cls");
                break;
            case 5:
                sistem.urutkanDescending();
                system("pause");
            	system("cls");
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                system("pause");
            	system("cls");
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
            	system("cls");
        }
    } while (pilihan != 0);
    
    return 0;
}


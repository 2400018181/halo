#ifndef KTP_LOGIN_H
#define KTP_LOGIN_H

#include <iostream>
#include <string>
using namespace std;

// ===== STRUKTUR DATA KTP UNTUK LOGIN =====
struct Tanggal {
    int hari;
    int bulan;
    int tahun;
};

struct KTP {
    string nik;                  // NIK sebagai username
    string nama;
    string tempat_lahir;
    Tanggal tgl_lahir;
    bool jenis_kelamin;          // 1 = Laki-laki, 0 = Perempuan
    string gol_darah;
    string alamat;
    string rt;
    string rw;
    string kel_desa;
    string kecamatan;
    string agama;
    bool status_perkawinan;      // 1 = Sudah, 0 = Belum
    string pekerjaan;
    bool kewarganegaraan;        // 1 = WNI, 0 = WNA
    string berlaku_hingga;
    string password;             // Password untuk login
    string role;                 // "Admin" atau "Kasir"
};

// ===== ARRAY 1D UNTUK USER =====
const int MAX_USER = 100;
KTP arrUser[MAX_USER];
int userCount = 0;

// ===== LINKED LIST UNTUK USER =====
struct NodeKTP {
    KTP data;
    NodeKTP* next;
};
NodeKTP* headUser = nullptr;

// ===== VARIABEL GLOBAL USER SESSION =====
string currentUserNIK = "";
string currentUserName = "";
string currentUserRole = "";

// ===== FUNGSI UNTUK ARRAY =====
void addUserArray(KTP data) {
    if (userCount < MAX_USER) {
        arrUser[userCount] = data;
        userCount++;
    }
}

// ===== FUNGSI UNTUK LINKED LIST =====
void addUserLinkedList(KTP data) {
    NodeKTP* newNode = new NodeKTP;
    newNode->data = data;
    newNode->next = nullptr;

    if (headUser == nullptr) {
        headUser = newNode;
    } else {
        NodeKTP* temp = headUser;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }
}

// ===== INISIALISASI USER DEFAULT =====
void initializeDefaultUser() {
    KTP admin;
    admin.nik = "admin";
    admin.nama = "Administrator";
    admin.tempat_lahir = "Jakarta";
    admin.tgl_lahir.hari = 1;
    admin.tgl_lahir.bulan = 1;
    admin.tgl_lahir.tahun = 1990;
    admin.jenis_kelamin = 1;
    admin.gol_darah = "O";
    admin.alamat = "Jl. Admin No. 1";
    admin.rt = "001";
    admin.rw = "001";
    admin.kel_desa = "Admin";
    admin.kecamatan = "Pusat";
    admin.agama = "Islam";
    admin.status_perkawinan = 1;
    admin.pekerjaan = "Administrator";
    admin.kewarganegaraan = 1;
    admin.berlaku_hingga = "SEUMUR HIDUP";
    admin.password = "admin123";
    admin.role = "Admin";
    
    addUserArray(admin);
    addUserLinkedList(admin);
    
    KTP kasir;
    kasir.nik = "kasir";
    kasir.nama = "Kasir Laundry";
    kasir.tempat_lahir = "Bandung";
    kasir.tgl_lahir.hari = 15;
    kasir.tgl_lahir.bulan = 6;
    kasir.tgl_lahir.tahun = 1995;
    kasir.jenis_kelamin = 0;
    kasir.gol_darah = "A";
    kasir.alamat = "Jl. Kasir No. 2";
    kasir.rt = "002";
    kasir.rw = "002";
    kasir.kel_desa = "Kasir";
    kasir.kecamatan = "Utara";
    kasir.agama = "Kristen";
    kasir.status_perkawinan = 0;
    kasir.pekerjaan = "Kasir";
    kasir.kewarganegaraan = 1;
    kasir.berlaku_hingga = "SEUMUR HIDUP";
    kasir.password = "kasir123";
    kasir.role = "Kasir";
    
    addUserArray(kasir);
    addUserLinkedList(kasir);
}

// ===== REGISTRASI USER BARU =====
void registerUser() {
    system("cls");
    cout << "		REGISTRASI USER BARU (Data KTP)		\n\n" << endl;
    if (userCount >= MAX_USER) {
        cout << "Kapasitas user penuh!\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }
    
    KTP newUser;
    cin.ignore(10000, '\n');
    
    cout << "NIK (sebagai username)                      : ";
    getline(cin, newUser.nik);
    
    for (int i = 0; i < userCount; i++) {
        if (arrUser[i].nik == newUser.nik) {
            cout << "\n✗ NIK sudah terdaftar! Gunakan NIK lain.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.get();
            return;
        }
    }
    
    cout << "Nama                                        : ";
    getline(cin, newUser.nama);
    cout << "Tempat Lahir                                : ";
    getline(cin, newUser.tempat_lahir);
    cout << "Tanggal Lahir (hari bulan tahun)            : ";
    cin >> newUser.tgl_lahir.hari >> newUser.tgl_lahir.bulan >> newUser.tgl_lahir.tahun;
    cin.ignore();
    cout << "Jenis Kelamin (1=Laki-laki, 0=Perempuan)    : ";
    cin >> newUser.jenis_kelamin;
    cin.ignore();
    cout << "Golongan Darah                              : ";
    getline(cin, newUser.gol_darah);
    cout << "Alamat                                      : ";
    getline(cin, newUser.alamat);
    cout << "RT                                          : ";
    getline(cin, newUser.rt);
    cout << "RW                                          : ";
    getline(cin, newUser.rw);
    cout << "Kel/Desa                                    : ";
    getline(cin, newUser.kel_desa);
    cout << "Kecamatan                                   : ";
    getline(cin, newUser.kecamatan);
    cout << "Agama                                       : ";
    getline(cin, newUser.agama);
    cout << "Status Kawin (1=Sudah, 0=Belum)             : ";
    cin >> newUser.status_perkawinan;
    cin.ignore();
    cout << "Pekerjaan                                   : ";
    getline(cin, newUser.pekerjaan);
    cout << "Kewarganegaraan (1=WNI, 0=WNA)              : ";
    cin >> newUser.kewarganegaraan;
    cin.ignore();
    cout << "Berlaku Hingga                              : ";
    getline(cin, newUser.berlaku_hingga);
    
    cout << "\n--- DATA LOGIN ---\n";
    cout << "Password                                    : ";
    getline(cin, newUser.password);
    cout << "Role (1=Admin, 2=Kasir)                     : ";
    int roleChoice;
    cin >> roleChoice;
    cin.ignore();
    
    if (roleChoice == 1) newUser.role = "Admin";
    else if (roleChoice == 2) newUser.role = "Kasir";
    else {
        cout << "\n✗ Role tidak valid!\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }
    
    addUserArray(newUser);
    addUserLinkedList(newUser);
    
    cout << "\n✓ User berhasil didaftarkan!\n";
    cout << "NIK (Username): " << newUser.nik << "\n";
    cout << "Nama          : " << newUser.nama << "\n";
    cout << "Role          : " << newUser.role << "\n";
    cout << "\nTekan ENTER untuk kembali...";
    cin.get();
}

// ===== LOGIN =====
bool loginUser() {
    system("cls");
    cout << "     SISTEM MANAJEMEN LAUNDRY PREMIUM          \n";
    cout << "              LOGIN DENGAN KTP                  \n\n";
    
    string nik, password;
    cin.ignore(10000, '\n');
    
    cout << "NIK (Username): ";
    getline(cin, nik);
    cout << "Password      : ";
    getline(cin, password);
    
    for (int i = 0; i < userCount; i++) {
        if (arrUser[i].nik == nik && arrUser[i].password == password) {
            currentUserNIK = arrUser[i].nik;
            currentUserName = arrUser[i].nama;
            currentUserRole = arrUser[i].role;
            
            system("cls");
            cout << "\n LOGIN BERHASIL!\n";
            cout << "Selamat datang, " << currentUserName << "!\n";
            cout << "NIK  : " << currentUserNIK << "\n";
            cout << "Role : " << currentUserRole << "\n";
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.get();
            return true;
        }
    }
    
    cout << "\n✗ Login gagal! NIK atau password salah.\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.get();
    return false;
}

// ===== TAMPILKAN USER DARI ARRAY =====
void tampilkanDaftarUserArray() {
    system("cls");
    cout << "\n=== DAFTAR USER (Array 1D) ===\n";
    for (int i = 0; i < userCount; i++) {
        cout << "\nUser ke-" << i+1 << endl;
        cout << "NIK             : " << arrUser[i].nik << endl;
        cout << "Nama            : " << arrUser[i].nama << endl;
        cout << "Tempat/Tgl Lahir: " 
             << arrUser[i].tempat_lahir << ", "
             << arrUser[i].tgl_lahir.hari << "-"
             << arrUser[i].tgl_lahir.bulan << "-"
             << arrUser[i].tgl_lahir.tahun << endl;
        cout << "Jenis Kelamin   : " 
             << (arrUser[i].jenis_kelamin ? "Laki-laki" : "Perempuan") << endl;
        cout << "Pekerjaan       : " << arrUser[i].pekerjaan << endl;
        cout << "Role            : " << arrUser[i].role << endl;
        cout << "-------------------------------------------\n";
    }
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

// ===== TAMPILKAN USER DARI LINKED LIST =====
void tampilkanDaftarUserLinkedList() {
    system("cls");
    cout << "\n=== DAFTAR USER (Linked List) ===\n";
    NodeKTP* temp = headUser;
    int i = 1;
    while (temp != nullptr) {
        cout << "\nUser ke-" << i++ << endl;
        cout << "NIK             : " << temp->data.nik << endl;
        cout << "Nama            : " << temp->data.nama << endl;
        cout << "Tempat/Tgl Lahir: "
             << temp->data.tempat_lahir << ", "
             << temp->data.tgl_lahir.hari << "-"
             << temp->data.tgl_lahir.bulan << "-"
             << temp->data.tgl_lahir.tahun << endl;
        cout << "Jenis Kelamin   : "
             << (temp->data.jenis_kelamin ? "Laki-laki" : "Perempuan") << endl;
        cout << "Pekerjaan       : " << temp->data.pekerjaan << endl;
        cout << "Role            : " << temp->data.role << endl;
        cout << "-------------------------------------------\n";
        
        temp = temp->next;
    }
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

// ===== MENU LOGIN =====
void menuLogin() {
    int pilihan;
    do {
        system("cls");
        cout << "     SISTEM MANAJEMEN LAUNDRY PREMIUM          \n";
        cout << "          LOGIN SYSTEM (BERBASIS KTP)          \n";
        cout << "1. Login\n";
        cout << "2. Register User Baru (Input Data KTP)\n";
        cout << "3. Lihat Daftar User (Array)\n";
        cout << "4. Lihat Daftar User (Linked List)\n";
        cout << "0. Keluar\n";
        cout << "\nPilih: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }
        
        switch (pilihan) {
            case 1:
                if (loginUser()) {
                    return;
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                tampilkanDaftarUserArray();
                break;
            case 4:
                tampilkanDaftarUserLinkedList();
                break;
            case 0:
                system("cls");
                cout << "Terima kasih!\n";
                exit(0);
            default:
                cout << "Pilihan tidak valid!\n";
                cin.ignore(10000, '\n');
                cin.get();
        }
    } while (true);
}

#endif

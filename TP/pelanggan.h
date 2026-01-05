#ifndef PELANGGAN_H
#define PELANGGAN_H

#include "laundry_core.h"

// Variabel global sudah didefinisikan di laundry_core.h:
// - PelangganNode* pelangganHead
// - int jumlahPelanggan

void tambahPelanggan() {
    if (jumlahPelanggan >= 100) {
        cout << "Kapasitas daftar pelanggan penuh.\n";
        return;
    }

    cin.ignore(10000, '\n');
    cout << "\n--- Tambah Pelanggan ---\n";

    PelangganNode* newPelanggan = new PelangganNode();
    cout << "Nama    : ";
    getline(cin, newPelanggan->nama);
    cout << "Alamat  : ";
    getline(cin, newPelanggan->alamat);
    cout << "Telepon : ";
    getline(cin, newPelanggan->telepon);
    newPelanggan->isMember = false;
    newPelanggan->memberID = "";
    newPelanggan->next = nullptr;

    if (pelangganHead == nullptr) {
        pelangganHead = newPelanggan;
    } else {
        PelangganNode* temp = pelangganHead;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newPelanggan;
    }

    jumlahPelanggan++;
    cout << "Pelanggan berhasil ditambahkan.\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

string generateMemberID(int index) {
    char buf[16];
    sprintf(buf, "MBR%04d", index + 1);
    return string(buf);
}

void daftarMenjadiMember() {
    if (pelangganHead == nullptr) {
        cout << "Belum ada pelanggan. Ingin menambahkan pelanggan baru dan menjadi member? (Y/N): ";
        char yn;
        cin >> yn;
        if (yn == 'Y' || yn == 'y') {
            tambahPelanggan();
            pelangganHead->isMember = true;
            pelangganHead->memberID = generateMemberID(0);
            cout << "Pelanggan " << pelangganHead->nama << " telah terdaftar sebagai member (ID: "
                 << pelangganHead->memberID << ").\n";
        }
        return;
    }

    cout << "=== Daftar Pelanggan ===\n";
    PelangganNode* temp = pelangganHead;
    int idx = 1;
    while (temp != nullptr) {
        cout << idx << ". " << temp->nama
             << " | " << (temp->isMember ? temp->memberID : "-") << "\n";
        temp = temp->next;
        idx++;
    }
    cout << "0. Tambah pelanggan baru dan langsung jadi member\n";
    cout << "Pilih nomor pelanggan: ";
    int pil;
    if (!(cin >> pil)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid.\n";
        return;
    }
    if (pil == 0) {
        tambahPelanggan();
        if (pelangganHead != nullptr) {
            pelangganHead->isMember = true;
            pelangganHead->memberID = generateMemberID(0);
        }
        return;
    }
    if (pil < 1 || pil > jumlahPelanggan) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    temp = pelangganHead;
    for (int i = 1; i < pil; i++) {
        temp = temp->next;
    }

    if (temp->isMember) {
        cout << "Pelanggan sudah menjadi member (ID: " << temp->memberID << ").\n";
        return;
    }
    temp->isMember = true;
    temp->memberID = generateMemberID(pil - 1);
    cout << "Pelanggan " << temp->nama << " berhasil didaftarkan sebagai member (ID: "
         << temp->memberID << ").\n";
}

void tampilkanMember() {
    system("cls");
    cout << "=== Daftar Member ===\n";
    bool ada = false;
    PelangganNode* temp = pelangganHead;
    while (temp != nullptr) {
        if (temp->isMember) {
            ada = true;
            cout << "- " << temp->nama << " | ID: " << temp->memberID
                 << " | Telepon: " << temp->telepon << "\n";
        }
        temp = temp->next;
    }
    if (!ada) cout << "Belum ada member terdaftar.\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void tampilkanPelanggan() {
    system("cls");
    if (pelangganHead == nullptr) {
        cout << "Belum ada data pelanggan.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    cout << "=== Daftar Pelanggan ===\n";
    PelangganNode* temp = pelangganHead;
    int i = 1;
    while (temp != nullptr) {
        cout << i++ << ". " << temp->nama
             << " | " << temp->telepon
             << " | " << temp->alamat
             << " | Member: " << (temp->isMember ? temp->memberID : "-") << "\n";
        temp = temp->next;
    }
    cout << "=======================\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void menuPelanggan() {
    int pil;
    do {
        system("cls");
        cout << "\n--- MENU PELANGGAN ---\n";
        cout << "1. Tambah Pelanggan\n";
        cout << "2. Tampilkan Daftar Pelanggan\n";
        cout << "3. Jadikan Pelanggan menjadi Member\n";
        cout << "4. Tampilkan Daftar Member\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        if (!(cin >> pil)) {
            cin.clear();
            cin.ignore(10000, '\n');
            pil = -1;
        }
        switch (pil) {
            case 1: tambahPelanggan(); break;
            case 2: tampilkanPelanggan(); break;
            case 3: daftarMenjadiMember(); break;
            case 4: tampilkanMember(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n"; break;
        }
    } while (pil != 0);
}

#endif

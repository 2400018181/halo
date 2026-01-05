#ifndef LAUNDRY_CORE_H
#define LAUNDRY_CORE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

// ===== FUNGSI TIMESTAMP =====
string getCurrentTimestamp() {
    time_t now = time(nullptr);
    struct tm *lt = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", lt);
    return string(buf);
}

// ===== VARIABEL GLOBAL PENDAPATAN =====
long long totalPendapatanBaju = 0;
long long totalPendapatanSepatu = 0;
long long totalPendapatanSelimut = 0;
long long totalPendapatanBedCover = 0;
long long totalPendapatanKarpet = 0;
long long totalPendapatanBoneka = 0;
long long totalPendapatanGorden = 0;
long long totalPendapatanBantal = 0;
long long totalPendapatanBarang = 0;

// ===== STRUKTUR TRANSAKSI =====
struct TransaksiLaundry {
    string nama;
    string jenisLayanan;
    string deskripsi;
    int total;
    string metodePembayaran;
    string status;
    string tanggal;
};

// ===== BINARY SEARCH TREE =====
struct Node {
    TransaksiLaundry data;
    int id;
    Node* left;
    Node* right;
    Node() : id(0), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;
int nextTxnID = 0;

// ===== STACK HISTORY =====
struct HistoryNode {
    int txnID;
    TransaksiLaundry snapshot;
    HistoryNode* next;
    HistoryNode(int id = 0, const TransaksiLaundry &s = TransaksiLaundry()) 
        : txnID(id), snapshot(s), next(nullptr) {}
};
HistoryNode* historyTop = nullptr;

// ===== LINKED LIST PELANGGAN =====
struct PelangganNode {
    string nama;
    string alamat;
    string telepon;
    bool isMember;
    string memberID;
    PelangganNode* next;
    PelangganNode() : isMember(false), next(nullptr) {}
};

PelangganNode* pelangganHead = nullptr;
int jumlahPelanggan = 0;

// ===== FUNGSI STACK =====
void pushHistoryNode(Node* txn) {
    if (txn == nullptr) return;
    HistoryNode* h = new HistoryNode(txn->id, txn->data);
    h->next = historyTop;
    historyTop = h;
}

void tampilkanHistoryStack() {
    system("cls");
    if (historyTop == nullptr) {
        cout << "History aktivitas kosong.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }
    cout << "===== STACK RIWAYAT AKTIVITAS (TERBARU di ATAS) =====\n";
    HistoryNode* cur = historyTop;
    int i = 1;
    while (cur) {
        const TransaksiLaundry &t = cur->snapshot;
        cout << i++ << ". " << t.nama
             << " | " << t.jenisLayanan
             << " | Rp " << t.total
             << " | " << t.tanggal
             << " | Status: " << t.status << "\n";
        cur = cur->next;
    }
    cout << "====================================================\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

// ===== FUNGSI BST =====
void insertNode(Node*& rootRef, Node* node) {
    if (rootRef == nullptr) {
        rootRef = node;
        node->left = node->right = nullptr;
        return;
    }
    if (node->id < rootRef->id) insertNode(rootRef->left, node);
    else insertNode(rootRef->right, node);
}

int countNodes(Node* cur) {
    if (!cur) return 0;
    return 1 + countNodes(cur->left) + countNodes(cur->right);
}

Node* findKthInorder(Node* cur, int &k) {
    if (!cur) return nullptr;
    Node* left = findKthInorder(cur->left, k);
    if (left) return left;
    if (--k == 0) return cur;
    return findKthInorder(cur->right, k);
}

void printInorderTransactions(Node* cur, int &index) {
    if (!cur) return;
    printInorderTransactions(cur->left, index);
    Node* temp = cur;
    cout << "Transaksi #" << (index+1) << "\n";
    cout << left << setw(15) << "Nama" << ": " << temp->data.nama << "\n";
    cout << left << setw(15) << "Layanan" << ": " << temp->data.jenisLayanan << "\n";
    cout << left << setw(15) << "Deskripsi" << ": " << temp->data.deskripsi << "\n";
    cout << left << setw(15) << "Total" << ": Rp " << temp->data.total << "\n";
    cout << left << setw(15) << "Metode" << ": " << temp->data.metodePembayaran << "\n";
    cout << left << setw(15) << "Status" << ": " << temp->data.status << "\n";
    cout << left << setw(15) << "Tanggal" << ": " << temp->data.tanggal << "\n";
    cout << string(50, '-') << "\n";
    index++;
    printInorderTransactions(cur->right, index);
}

void printInorderSimple(Node* cur, int &idx) {
    if (!cur) return;
    printInorderSimple(cur->left, idx);
    cout << (idx+1) << ". " << cur->data.nama
         << " - " << cur->data.jenisLayanan
         << " - Status: " << cur->data.status << endl;
    idx++;
    printInorderSimple(cur->right, idx);
}

void deleteNodeByID(Node*& rootRef, int id) {
    if (!rootRef) return;
    if (id < rootRef->id) {
        deleteNodeByID(rootRef->left, id);
    } else if (id > rootRef->id) {
        deleteNodeByID(rootRef->right, id);
    } else {
        Node* toDelete = rootRef;
        if (!rootRef->left) {
            rootRef = rootRef->right;
            delete toDelete;
            return;
        } else if (!rootRef->right) {
            rootRef = rootRef->left;
            delete toDelete;
            return;
        } else {
            Node* succ = rootRef->right;
            while (succ->left) succ = succ->left;
            rootRef->data = succ->data;
            rootRef->id = succ->id;
            deleteNodeByID(rootRef->right, succ->id);
            return;
        }
    }
}

// ===== FUNGSI TRANSAKSI =====
void simpanTransaksi(string nama, string jenis, 
    string deskripsi, int total, string metode) {
    TransaksiLaundry t;
    t.nama = nama;
    t.jenisLayanan = jenis;
    t.deskripsi = deskripsi;
    t.total = total;
    t.metodePembayaran = metode;
    t.status = "Dalam Proses";
    t.tanggal = getCurrentTimestamp();

    Node* newNode = new Node;
    newNode->data = t;
    newNode->left = newNode->right = nullptr;
    newNode->id = ++nextTxnID;

    insertNode(root, newNode);
    pushHistoryNode(newNode);
}

void popHistoryAktivitas() {
    system("cls");
    if (historyTop == nullptr) {
        cout << "Tidak ada aktivitas untuk dibatalkan.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    int id = historyTop->txnID;
    TransaksiLaundry snap = historyTop->snapshot;

    cout << "Membatalkan aktivitas terakhir:\n";
    cout << "Nama   : " << snap.nama << "\n";
    cout << "Layanan: " << snap.jenisLayanan << "\n";
    cout << "Total  : Rp " << snap.total << "\n";
    cout << "Tanggal: " << snap.tanggal << "\n\n";

    deleteNodeByID(root, id);

    HistoryNode* tmp = historyTop;
    historyTop = historyTop->next;
    delete tmp;

    cout << "✓ Aktivitas terakhir berhasil dibatalkan.\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void tampilkanRiwayatTransaksi() {
    system("cls");
    if (root == nullptr) {
        cout << "Belum ada transaksi yang tercatat.\n";
        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    cout << "===== RIWAYAT TRANSAKSI LAUNDRY (URUTAN ID) =====\n\n";
    int idx = 0;
    printInorderTransactions(root, idx);

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void ubahStatusLaundry() {
    system("cls");
    if (root == nullptr) {
        cout << "Belum ada data laundry yang tersimpan.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }
    int total = countNodes(root);
    int idx = 0;
    printInorderSimple(root, idx);

    int pilihan;
    cout << "\nMasukkan nomor transaksi yang ingin diubah statusnya: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > total) {
        cout << "Nomor tidak valid!\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    int k = pilihan;
    Node* target = findKthInorder(root, k);

    cout << "Pilih status baru:\n";
    cout << "1. Dalam Proses\n";
    cout << "2. Selesai\n";
    cout << "3. Sudah Diambil\n";
    cout << "Pilihan: ";
    int statusBaru;
    cin >> statusBaru;

    switch (statusBaru) {
        case 1: target->data.status = "Dalam Proses"; break;
        case 2: target->data.status = "Selesai"; break;
        case 3: target->data.status = "Sudah Diambil"; break;
        default:
            cout << "Pilihan tidak valid!\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
    }

    cout << "\nStatus laundry berhasil diperbarui!\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void tampilkanTotalPendapatan() {
    system("cls");
    long long totalSemua =
        totalPendapatanBaju
        + totalPendapatanSepatu
        + totalPendapatanSelimut
        + totalPendapatanBedCover
        + totalPendapatanKarpet
        + totalPendapatanBoneka
        + totalPendapatanGorden
        + totalPendapatanBantal
        + totalPendapatanBarang;

    cout << "\n===== TOTAL PENDAPATAN LAUNDRY =====\n";
    cout << left << setw(25) << "Laundry Baju" << "Rp " << totalPendapatanBaju << endl;
    cout << left << setw(25) << "Laundry Sepatu" << "Rp " << totalPendapatanSepatu << endl;
    cout << left << setw(25) << "Laundry Selimut" << "Rp " << totalPendapatanSelimut << endl;
    cout << left << setw(25) << "Laundry Bed Cover" << "Rp " << totalPendapatanBedCover << endl;
    cout << left << setw(25) << "Laundry Karpet" << "Rp " << totalPendapatanKarpet << endl;
    cout << left << setw(25) << "Laundry Boneka" << "Rp " << totalPendapatanBoneka << endl;
    cout << left << setw(25) << "Laundry Gorden" << "Rp " << totalPendapatanGorden << endl;
    cout << left << setw(25) << "Laundry Bantal" << "Rp " << totalPendapatanBantal << endl;
    cout << left << setw(25) << "Penjualan Barang" << "Rp " << totalPendapatanBarang << endl;
    cout << "--------------------------------------\n";
    cout << left << setw(25) << "Total Semua" << "Rp " << totalSemua << endl;
    cout << "======================================\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void pilihMetodePembayaran(string &metode) {
    system("cls");
    cout << "\n--- PILIH METODE PEMBAYARAN ---\n";
    cout << "1. Cash\n";
    cout << "2. Debit\n";
    cout << "3. E-Wallet\n";
    cout << "Pilih metode: ";
    int pil;
    cin >> pil;
    switch (pil) {
        case 1: metode = "Cash"; break;
        case 2: metode = "Debit"; break;
        case 3: metode = "E-Wallet"; break;
        default: metode = "Cash"; break;
    }
}

#endif

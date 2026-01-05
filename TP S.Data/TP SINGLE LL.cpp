#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    struct tm *lt = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", lt);
    return string(buf);
}

long long totalPendapatanBaju = 0;
long long totalPendapatanSepatu = 0;
long long totalPendapatanSelimut = 0;
long long totalPendapatanBedCover = 0;
long long totalPendapatanKarpet = 0;
long long totalPendapatanBoneka = 0;
long long totalPendapatanGorden = 0;
long long totalPendapatanBantal = 0;
long long totalPendapatanBarang = 0;

struct TransaksiLaundry {
    string nama;
    string jenisLayanan;
    string deskripsi;
    int total;
    string metodePembayaran;
    string status;
    string tanggal;
    // optional: keep an ID here if needed
};

// ===== BINARY SEARCH TREE UNTUK TRANSAKSI =====
struct Node {
    TransaksiLaundry data;
    int id; // unique transaction id (insertion order)
    Node* left;
    Node* right;
    Node() : id(0), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;
int nextTxnID = 0;

// ===== STACK HISTORY (menyimpan ID dan snapshot) =====
struct HistoryNode {
    int txnID;
    TransaksiLaundry snapshot;
    HistoryNode* next;
    HistoryNode(int id = 0, const TransaksiLaundry &s = TransaksiLaundry()) : txnID(id), snapshot(s), next(nullptr) {}
};
HistoryNode* historyTop = nullptr;

// ===== SINGLE LINKED LIST UNTUK PELANGGAN =====
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

void popHistoryAktivitas() {
    system("cls");
    if (historyTop == nullptr) {
        cout << "Tidak ada aktivitas untuk dibatalkan.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    // pop from history and delete by txnID from BST
    int id = historyTop->txnID;
    TransaksiLaundry snap = historyTop->snapshot;

    cout << "Membatalkan aktivitas terakhir:\n";
    cout << "Nama   : " << snap.nama << "\n";
    cout << "Layanan: " << snap.jenisLayanan << "\n";
    cout << "Total  : Rp " << snap.total << "\n";
    cout << "Tanggal: " << snap.tanggal << "\n\n";

    // Delete node with given ID from BST
    extern void deleteNodeByID(Node*& rootRef, int id);
    deleteNodeByID(root, id);

    // Pop history node
    HistoryNode* tmp = historyTop;
    historyTop = historyTop->next;
    delete tmp;

    cout << "? Aktivitas terakhir berhasil dibatalkan.\n";
    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

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

void simpanTransaksi(string nama, string jenis, string deskripsi, int total, string metode) {
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

    // insert into BST
    extern void insertNode(Node*& rootRef, Node* node);
    insertNode(root, newNode);

    // record history (snapshot)
    pushHistoryNode(newNode);
}

// ===== BST HELPERS =====
void insertNode(Node*& rootRef, Node* node) {
    if (rootRef == nullptr) {
        rootRef = node;
        node->left = node->right = nullptr;
        return;
    }
    if (node->id < rootRef->id) insertNode(rootRef->left, node);
    else insertNode(rootRef->right, node);
}

// Helpers without using std::vector
int countNodes(Node* cur) {
    if (!cur) return 0;
    return 1 + countNodes(cur->left) + countNodes(cur->right);
}

// find k-th node in inorder (k is 1-based via caller, passed by reference and decremented)
Node* findKthInorder(Node* cur, int &k) {
    if (!cur) return nullptr;
    Node* left = findKthInorder(cur->left, k);
    if (left) return left;
    if (--k == 0) return cur;
    return findKthInorder(cur->right, k);
}

// Print detailed transactions in inorder with sequential numbering
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

// Print simple indexed list for selection (name - layanan - status)
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
        // found node
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
            // two children: find inorder successor
            Node* succ = rootRef->right;
            while (succ->left) succ = succ->left;
            // copy successor data into current node
            rootRef->data = succ->data;
            rootRef->id = succ->id;
            // delete successor node (it will have at most right child)
            deleteNodeByID(rootRef->right, succ->id);
            return;
        }
    }
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

// ===== FUNGSI-FUNGSI LAUNDRY =====
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

void prosesLaundryBaju() {
    cin.ignore();
    cout << "Selamat datang di layanan laundry baju kami!\n";
    cout << "Kami mengerti betapa berharganya pakaian Anda, dan kami berkomitmen untuk memberikan perawatan terbaik agar pakaian Anda tetap bersih, segar, dan terlihat seperti baru kembali.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan aman, serta produk pembersih berkualitas tinggi, kami akan memastikan bahwa pakaian Anda mendapatkan perhatian khusus yang layak mereka terima.\n";
    cout << "Percayakan laundry baju Anda kepada kami, dan biarkan kami mengembalikan keceriaan pada pakaian kesayangan Anda!\n\n";
    cout << endl;
    cout << "--- LAUNDRY BAJU ORANG KAYA ---\n";

    string nama, deskripsi;
    string metode;
    double beratKg = 0.0;
    int hargaPerKg = 10000; // fixed price per kg

    cout << "Masukkan berat pakaian (kg): ";
    if (!(cin >> beratKg) || beratKg <= 0.0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Berat tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }
    cout << "Harga per kg: Rp " << hargaPerKg << "\n";

    double subtotal = beratKg * hargaPerKg;

    // Hitung diskon: setiap kelipatan 10 kg memberi diskon 10% per kelipatan
    int kelipatan = static_cast<int>(beratKg / 10.0);
    double persenDiskon = kelipatan * 10.0; // 10% per kelipatan 10kg
    double diskon = subtotal * (persenDiskon / 100.0);
    double totalDouble = subtotal - diskon;
    long long total = static_cast<long long>(totalDouble + 0.5); // pembulatan

    cin.ignore(10000, '\n'); // buang newline sebelum getline
    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);

    pilihMetodePembayaran(metode);
    // opsi antar-jemput
    char pick;
    int ongkir = 0;
    double jarak = 0.0;
    cout << "Butuh antar-jemput? (Y/N): ";
    cin >> pick;
    if (pick == 'Y' || pick == 'y') {
        cout << "Masukkan jarak (km): ";
        cin >> jarak;
        if (jarak < 5.0) ongkir = 0;
        else {
            double extra = jarak - 5.0;
            int extraKm = (int)ceil(extra);
            ongkir = 15000 + 5000 * extraKm;
        }
    }

    // Simpan transaksi dan tambahkan ke pendapatan (termasuk ongkir bila ada)
    string deskripsiFull = deskripsi + " (berat: " + to_string(beratKg) + " kg, harga/kg: Rp " + to_string(hargaPerKg)
                           + ", diskon: " + to_string(static_cast<int>(persenDiskon)) + "%)";
    if (ongkir > 0) {
        deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
        total += ongkir;
    }
    simpanTransaksi(nama, "Laundry Baju", deskripsiFull, static_cast<int>(total), metode);
    totalPendapatanBaju += total;
    cout << "\nTransaksi laundry baju berhasil disimpan!\n";
    cout << "Rincian: " << beratKg << " kg x Rp " << hargaPerKg << " = Rp " << static_cast<long long>(subtotal) << "\n";
    cout << "Diskon: " << static_cast<int>(persenDiskon) << "%  => Rp " << static_cast<long long>(diskon) << "\n";
    cout << "Total dibayar: Rp " << total << "\n";

    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.get();
}

void prosesLaundrySelimut() {
    cin.ignore();
    cout << "Selamat datang di layanan laundry selimut kami!\n";
    cout << "Kami memahami betapa pentingnya selimut yang bersih dan nyaman untuk kenyamanan tidur Anda.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan produk pembersih berkualitas tinggi, kami akan memastikan bahwa selimut Anda tidak hanya bersih, tetapi juga tetap lembut dan harum.\n";
    cout << "Percayakan laundry selimut Anda kepada kami, dan nikmati tidur yang lebih nyenyak dengan selimut yang segar dan bersih setiap malamnya!\n\n";
    cout << endl;
    cout << "--- LAUNDRY SELIMUT ORANG KAYA ---\n";

    int pilihanJenis = 0;
    int jumlah = 0;
    int hargaPer = 0;
    string jenisStr;

    cout << "Pilih jenis selimut:\n";
    cout << "1. Selimut Bayi       - Rp 15.000\n";
    cout << "2. Selimut Single Bed - Rp 30.000\n";
    cout << "3. Selimut Double Bed - Rp 45.000\n";
    cout << "4. Selimut Queen Bed  - Rp 60.000\n";
    cout << "5. Selimut King Bed   - Rp 75.000\n";
    cout << "Pilihan (1-5): ";
    if (!(cin >> pilihanJenis)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    switch (pilihanJenis) {
        case 1: 
                hargaPer = 15000; 
                jenisStr = "Selimut Bayi"; 
                break;
        case 2: 
                hargaPer = 30000; 
                jenisStr = "Selimut Single Bed"; 
                break;
        case 3: 
                hargaPer = 45000; 
                jenisStr = "Selimut Double Bed"; 
                break;
        case 4: 
                hargaPer = 60000; 
                jenisStr = "Selimut Queen Bed"; 
                break;
        case 5: 
                hargaPer = 75000; 
                jenisStr = "Selimut King Bed"; 
                break;
        default:
            cout << "Pilihan tidak valid. Kembali ke menu.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
    }

    cout << "Jumlah (pcs): ";
    if (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Jumlah tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    long long total = (long long)hargaPer * jumlah;

    cin.ignore(10000, '\n'); // buang newline sebelum getline
    string nama, deskripsi;
    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi (opsional): ";
    getline(cin, deskripsi);

    string metode;
    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    char pick;
    int ongkir = 0;
    double jarak = 0.0;
    cout << "Butuh antar-jemput? (Y/N): ";
    cin >> pick;
    if (pick == 'Y' || pick == 'y') {
        cout << "Masukkan jarak (km): ";
        cin >> jarak;
        if (jarak < 5.0) ongkir = 0;
        else {
            double extra = jarak - 5.0;
            int extraKm = (int)ceil(extra);
            ongkir = 15000 + 5000 * extraKm;
        }
    }

    string deskripsiFull = deskripsi + " (qty: " + to_string(jumlah) + ")";
    if (ongkir > 0) {
        deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
        total += ongkir;
    }
    // Simpan transaksi dengan jenis yang lebih spesifik
    simpanTransaksi(nama, "Laundry Selimut - " + jenisStr, deskripsiFull, (int)total, metode);
    totalPendapatanSelimut += total;

    cout << "\nTransaksi laundry selimut berhasil disimpan!\n";
    cout << "Rincian: " << jenisStr << " x" << jumlah << " @ Rp " << hargaPer << " = Rp " << total << "\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.get();
}

void prosesLaundryBedCover() {
    cin.ignore();
    cout << "Selamat datang di layanan laundry bed cover kami!\n";
    cout << "Kami memahami betapa pentingnya bed cover yang bersih dan nyaman untuk menciptakan suasana tidur yang menyenangkan.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan produk pembersih berkualitas tinggi, kami akan memastikan bahwa bed cover Anda tidak hanya bersih, tetapi juga tetap lembut dan harum.\n";
    cout << "Percayakan laundry bed cover Anda kepada kami, dan nikmati tidur yang lebih nyenyak dengan bed cover yang segar dan bersih setiap malamnya!\n\n";
    cout << endl;
    cout << "--- LAUNDRY BED COVER ORANG KAYA ---\n";
    string nama, deskripsi;
    int pilihanJenis = 0;
    int jumlah = 0;
    int hargaPer = 0;
    string jenisStr;
    string metode;

    cout << "Pilih jenis bed cover:\n";
    cout << "1. Single Twin              - Rp 75.000\n";
    cout << "2. Super Single / Double    - Rp 100.000\n";
    cout << "3. Queen Size               - Rp 125.000\n";
    cout << "4. King Size                - Rp 150.000\n";
    cout << "5. Super King / Extra King  - Rp 175.000\n";
    cout << "Pilihan (1-5): ";
    if (!(cin >> pilihanJenis)) {
        cin.clear();
        cin.ignore();
        cout << "Input tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    switch (pilihanJenis) {
        case 1:
            hargaPer = 75000;
            jenisStr = "Single Twin";
            break;
        case 2:
            hargaPer = 100000;
            jenisStr = "Super Single / Double";
            break;
        case 3:
            hargaPer = 125000;
            jenisStr = "Queen Size";
            break;
        case 4:
            hargaPer = 150000;
            jenisStr = "King Size";
            break;
        case 5:
            hargaPer = 175000;
            jenisStr = "Super King / Extra King";
            break;
        default:
            cout << "Pilihan tidak valid. Kembali ke menu.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000);
            cin.get();
            return;
    }

    cout << "Jumlah (pcs): ";
    if (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Jumlah tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    long long total = (long long)hargaPer * jumlah;

    cin.ignore(); // buang newline sebelum getline
    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi (opsional): ";
    getline(cin, deskripsi);

    pilihMetodePembayaran(metode);

    string deskripsiFull = deskripsi + " (" + jenisStr + " x" + to_string(jumlah) + " @ Rp " + to_string(hargaPer) + ")";
    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
    }
    simpanTransaksi(nama, "Laundry Bed Cover - " + jenisStr, deskripsiFull, (int)total, metode);
    totalPendapatanBedCover += total;

    cout << "\nTransaksi laundry bed cover berhasil disimpan!\n";
    cout << "Rincian: " << jenisStr << " x" << jumlah << " @ Rp " << hargaPer << " = Rp " << total << "\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.get();
}

void prosesLaundrySepatu() {
    cin.ignore();
    cout << "Selamat datang di layanan cuci sepatu kami!\n";
    cout << "Kami memahami betapa berharganya sepatu kesayangan Anda, dan kami berkomitmen untuk memberikan perawatan terbaik agar sepatu Anda tetap bersih, segar, dan terlihat seperti baru kembali.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan aman, serta produk pembersih berkualitas tinggi, kami akan memastikan bahwa sepatu Anda mendapatkan perhatian khusus yang layak mereka terima.\n";
    cout << "Percayakan cuci sepatu Anda kepada kami, dan biarkan kami mengembalikan keceriaan pada sepatu kesayangan Anda!\n\n";
    cout << endl;
    cout << "--- CUCI SEPATU ORANG KAYA ---\n";
    string nama, deskripsi;
    int hargaPer = 0;
    string jenisStr;
    int jumlah = 0;
    long long total = 0;
    string metode;

    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);

    cout << "Pilih jenis sepatu:\n";
    cout << "1. Sports   - Rp 50.000\n";
    cout << "2. Sneakers - Rp 45.000\n";
    cout << "3. Anak     - Rp 30.000\n";
    cout << "4. Boots    - Rp 75.000\n";
    cout << "5. Lainnya  - Masukkan harga sendiri\n";
    cout << "Pilihan (1-5): ";
    int pilJenis;
    if (!(cin >> pilJenis)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    switch (pilJenis) {
        case 1: 
                hargaPer = 50000; 
                jenisStr = "Sports"; 
                break;
        case 2: 
                hargaPer = 45000; 
                jenisStr = "Sneakers"; 
                break;
        case 3: hargaPer = 30000; 
                jenisStr = "Anak"; 
                break;
        case 4: hargaPer = 75000; 
                jenisStr = "Boots"; 
                break;
        case 5:
            cout << "Masukkan harga per item (Rp): ";
            if (!(cin >> hargaPer) || hargaPer <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Harga tidak valid. Kembali ke menu.\n";
                cout << "Tekan ENTER untuk kembali...";
                cin.get();
                return;
            }
            jenisStr = "Lainnya";
            break;
        default:
            cout << "Pilihan jenis tidak valid. Kembali ke menu.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
    }

    cout << "Jumlah (pcs): ";
    if (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Jumlah tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    total = (long long)hargaPer * jumlah;

    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        string deskripsiFull = deskripsi + " (jenis: " + jenisStr + ", qty: " + to_string(jumlah) + ", harga/item: Rp " + to_string(hargaPer) + ")";
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
        simpanTransaksi(nama, "Cuci Sepatu - " + jenisStr, deskripsiFull, (int)total, metode);
        totalPendapatanSepatu += total;
    }

    cout << "\nTransaksi cuci sepatu berhasil disimpan!\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void prosesLaundryKarpet() {
    cin.ignore();
    cout << "Selamat datang di layanan cuci karpet kami!\n";
    cout << "Kami memahami betapa berharganya karpet kesayangan Anda, dan kami berkomitmen untuk memberikan perawatan terbaik agar karpet Anda tetap bersih, segar, dan terlihat seperti baru kembali.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan aman, serta produk pembersih berkualitas tinggi, kami akan memastikan bahwa karpet Anda mendapatkan perhatian khusus yang layak mereka terima.\n";
    cout << "Percayakan cuci karpet Anda kepada kami, dan biarkan kami mengembalikan keceriaan pada karpet kesayangan Anda!\n\n";   
    cout << endl;
    cout << "--- CUCI KARPET ORANG KAYA ---\n";
    string nama, deskripsi;
    int hargaPer = 0;
    string jenisStr;
    int jumlah = 0;
    long long total = 0;
    string metode;

    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);

    cout << "Pilih jenis pembersihan karpet:\n";
    cout << "1. Manual       - Rp 35.000\n";
    cout << "2. Mesin        - Rp 40.000\n";
    cout << "3. Steam        - Rp 50.000\n";
    cout << "4. Drycleaning  - Rp 75.000\n";
    cout << "5. Deepcleaning - Rp 80.000\n";
    cout << "6. Masjid       - Rp 85.000\n";
    cout << "7. Kantor       - Rp 100.000\n";
    cout << "8. Express      - Rp 150.000\n";
    cout << "9. Lainnya - Masukkan harga sendiri\n";
    cout << "Pilihan (1-9): ";
    int pilJenis;
    if (!(cin >> pilJenis)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    switch (pilJenis) {
        case 1: 
                hargaPer = 35000; 
                jenisStr = "Manual"; 
                break;
        case 2: 
                hargaPer = 40000; 
                jenisStr = "Mesin"; 
                break;
        case 3: 
                hargaPer = 50000; 
                jenisStr = "Steam"; 
                break;
        case 4: 
                hargaPer = 75000; 
                jenisStr = "Drycleaning"; 
                break;
        case 5: 
                hargaPer = 80000; 
                jenisStr = "Deepcleaning"; 
                break;
        case 6: 
                hargaPer = 85000; 
                jenisStr = "Masjid"; 
                break;
        case 7: 
                hargaPer = 100000; 
                jenisStr = "Kantor"; 
                break;
        case 8: 
                hargaPer = 150000; 
                jenisStr = "Express"; 
                break;
        case 9:
            cout << "Masukkan harga per unit (Rp): ";
            if (!(cin >> hargaPer) || hargaPer <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Harga tidak valid. Kembali ke menu.\n";
                cout << "Tekan ENTER untuk kembali...";
                cin.get();
                return;
            }
            jenisStr = "Lainnya";
            break;
        default:
            cout << "Pilihan jenis tidak valid. Kembali ke menu.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
    }

    cout << "Jumlah (pcs): ";
    if (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Jumlah tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    total = (long long)hargaPer * jumlah;

    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        string deskripsiFull = deskripsi + " (jenis: " + jenisStr + ", qty: " + to_string(jumlah) + ", harga/unit: Rp " + to_string(hargaPer) + ")";
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
        simpanTransaksi(nama, "Cuci Karpet - " + jenisStr, deskripsiFull, (int)total, metode);
        totalPendapatanKarpet += total;
    }

    cout << "\nTransaksi cuci karpet berhasil disimpan!\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void prosesLaundryBoneka() {
    cin.ignore();
    cout << "Selamat datang di layanan cuci boneka kami!\n";
    cout << "Kami memahami betapa berharganya boneka kesayangan Anda, dan kami berkomitmen untuk memberikan perawatan terbaik agar boneka Anda tetap bersih, segar, dan terlihat seperti baru kembali.\n";
    cout << "Dengan menggunakan teknik pencucian yang lembut dan aman, serta produk pembersih berkualitas tinggi, kami akan memastikan bahwa boneka Anda mendapatkan perhatian khusus yang layak mereka terima.\n";
    cout << "Percayakan cuci boneka Anda kepada kami, dan biarkan kami mengembalikan keceriaan pada boneka kesayangan Anda!\n\n";  
    cout << "--- CUCI BONEKA ORANG KAYA ---\n";
    string nama, deskripsi;
    int hargaPer = 0;
    string ukuranStr;
    int jumlah = 0;
    long long total = 0;
    string metode;

    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);

    cout << "Pilih ukuran boneka:\n";
    cout << "1. Kecil  - Rp 35.000\n";
    cout << "2. Sedang - Rp 50.000\n";
    cout << "3. Besar  - Rp 50.000\n";
    cout << "4. Lainnya - Masukkan harga sendiri\n";
    cout << "Pilihan (1-4): ";
    int pilUkuran;
    if (!(cin >> pilUkuran)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    switch (pilUkuran) {
        case 1: 
                hargaPer = 35000; 
                ukuranStr = "Kecil"; 
                break;
        case 2: 
                hargaPer = 50000; 
                ukuranStr = "Sedang"; 
                break;
        case 3: 
                hargaPer = 50000; 
                ukuranStr = "Besar"; 
                break;
        case 4:
            cout << "Masukkan harga per item (Rp): ";
            if (!(cin >> hargaPer) || hargaPer <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Harga tidak valid. Kembali ke menu.\n";
                cout << "Tekan ENTER untuk kembali...";
                cin.get();
                return;
            }
            ukuranStr = "Lainnya";
            break;
        default:
            cout << "Pilihan ukuran tidak valid. Kembali ke menu.\n";
            cout << "Tekan ENTER untuk kembali...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
    }

    cout << "Jumlah (pcs): ";
    if (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Jumlah tidak valid. Kembali ke menu.\n";
        cout << "Tekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    total = (long long)hargaPer * jumlah;

    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        string deskripsiFull = deskripsi + " (ukuran: " + ukuranStr + ", qty: " + to_string(jumlah) + ", harga/item: Rp " + to_string(hargaPer) + ")";
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
        simpanTransaksi(nama, "Cuci Boneka - " + ukuranStr, deskripsiFull, (int)total, metode);
        totalPendapatanBoneka += total;
    }

    cout << "\nTransaksi cuci boneka berhasil disimpan!\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void prosesLaundryGorden() {
    cin.ignore();
    cout << "SELAMAT DATANG DI LAUNDRY GORDEN KAMI\n";
    cout << "Kami menyediakan layanan cuci gorden dengan kualitas terbaik untuk menjaga keindahan dan kebersihan rumah Anda.\n";
    cout << "Dengan teknologi cuci modern dan ramah lingkungan, gorden Anda akan kembali segar dan harum seperti baru.\n";
    cout << "Percayakan cuci gorden Anda kepada kami dan rasakan perbedaannya!\n\n";
    cout << endl;
    cout << "--- CUCI GORDEN ORANG KAYA ---\n";
    string nama, deskripsi;
    int total;
    string metode;

    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);
    cout << "Total Harga: Rp ";
    cin >> total;

    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        string deskripsiFull = deskripsi;
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
        simpanTransaksi(nama, "Cuci Gorden", deskripsiFull, total, metode);
        totalPendapatanGorden += total;
    }

    cout << "\nTransaksi cuci gorden berhasil disimpan!\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

void prosesLaundryBantal() {
    cin.ignore();
    cout << "SELAMAT DATANG DI LAUNDRY BANTAL KAMI\n";
    cout << "Kami menyediakan layanan cuci bantal dengan kualitas terbaik untuk menjaga kenyamanan tidur Anda.\n";
    cout << "Dengan teknologi cuci modern dan ramah lingkungan, bantal Anda akan kembali segar, bersih, dan harum seperti baru.\n";
    cout << "Percayakan cuci bantal Anda kepada kami dan rasakan perbedaannya!\n\n";
    cout << endl;
    cout << "--- CUCI BANTAL ORANG KAYA ---\n";
    string nama, deskripsi;
    int total;
    string metode;

    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Deskripsi: ";
    getline(cin, deskripsi);
    cout << "Total Harga: Rp ";
    cin >> total;

    pilihMetodePembayaran(metode);

    // opsi antar-jemput
    {
        char pick;
        int ongkir = 0;
        double jarak = 0.0;
        cout << "Butuh antar-jemput? (Y/N): ";
        cin >> pick;
        if (pick == 'Y' || pick == 'y') {
            cout << "Masukkan jarak (km): ";
            cin >> jarak;
            if (jarak < 5.0) ongkir = 0;
            else {
                double extra = jarak - 5.0;
                int extraKm = (int)ceil(extra);
                ongkir = 15000 + 5000 * extraKm;
            }
        }
        string deskripsiFull = deskripsi;
        if (ongkir > 0) {
            deskripsiFull += " | antar-jemput: Rp " + to_string(ongkir) + " (jarak: " + to_string(jarak) + " km)";
            total += ongkir;
        }
        simpanTransaksi(nama, "Cuci Bantal", deskripsiFull, total, metode);
        totalPendapatanBantal += total;
    }

    cout << "\nTransaksi cuci bantal berhasil disimpan!\n";
    // tampilkan struk (inline)
    if (historyTop != nullptr) {
        const TransaksiLaundry &s = historyTop->snapshot;
        int id = historyTop->txnID;
        cout << "\n======= STRUK TRANSAKSI =======\n";
        cout << left << setw(18) << "ID Transaksi" << ": " << id << "\n";
        cout << left << setw(18) << "Nama" << ": " << s.nama << "\n";
        cout << left << setw(18) << "Layanan" << ": " << s.jenisLayanan << "\n";
        cout << left << setw(18) << "Deskripsi" << ": " << s.deskripsi << "\n";
        cout << left << setw(18) << "Total" << ": Rp " << s.total << "\n";
        cout << left << setw(18) << "Metode" << ": " << s.metodePembayaran << "\n";
        cout << left << setw(18) << "Status" << ": " << s.status << "\n";
        cout << left << setw(18) << "Tanggal" << ": " << s.tanggal << "\n";
        cout << "===============================\n";
    }

    cout << "Tekan ENTER untuk kembali...";
    cin.ignore(10000, '\n');
    cin.get();
}

int main() {
    int pilihan;
    char ulang;

    do {
        system("cls");
        cout << "\n===== MENU LAUNDRY =====" << endl;
        cout << "1. Laundry Baju" << endl;
        cout << "2. Laundry Selimut" << endl;
        cout << "3. Laundry Bed Cover" << endl;
        cout << "4. Cuci Sepatu" << endl;
        cout << "5. Cuci Karpet" << endl;
        cout << "6. Cuci Boneka" << endl;
        cout << "7. Cuci Gorden" << endl;
        cout << "8. Cuci Bantal" << endl;
        cout << "9. Lihat riwayat transaksi" << endl;
        cout << "10. Ubah Status Laundry" << endl;
        cout << "11. Tampilkan Total Pendapatan" << endl;
        cout << "12. Menu Pelanggan" << endl;
        cout << "13. Batalkan Aktivitas Terakhir (POP History)" << endl;
        cout << "14. Tampilkan Stack History" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                prosesLaundryBaju();
                break;
            case 2:
                system("cls");
                prosesLaundrySelimut();
                break;
            case 3:
                system("cls");
                prosesLaundryBedCover();
                break;
            case 4:
                system("cls");
                prosesLaundrySepatu();
                break;
            case 5:
                system("cls");
                prosesLaundryKarpet();
                break;
            case 6:
                system("cls");
                prosesLaundryBoneka();
                break;
            case 7:
                system("cls");
                prosesLaundryGorden();
                break;
            case 8:
                system("cls");
                prosesLaundryBantal();
                break;
            case 9:
                system("cls");
                tampilkanRiwayatTransaksi();
                break;
            case 10:
                system("cls");
                ubahStatusLaundry();
                break;
            case 11:
                system("cls");
                tampilkanTotalPendapatan();
                break;
            case 12:
                system("cls");
                menuPelanggan();
                break;
            case 13:
                system("cls");
                popHistoryAktivitas();
                break;
            case 14:
                system("cls");
                tampilkanHistoryStack();
                break;
            case 0:
                system("cls");
                cout << "Terima kasih telah menggunakan layanan kami!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid!" << endl;
                cin.ignore(10000, '\n');
                cin.get();
        }

        if (pilihan != 0) {
            cout << "\nKembali ke menu utama? (y/n): ";
            cin >> ulang;
        }

    } while (ulang == 'y' || ulang == 'Y');

    system("cls");
    cout << "Program selesai. Sampai jumpa!" << endl;
    return 0;
}

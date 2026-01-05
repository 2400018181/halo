#ifndef LAYANAN_H
#define LAYANAN_H

#include "laundry_core.h"


void prosesLaundryBaju() {
    system("cls");
    cout << "\n=== LAUNDRY BAJU ===\n";
    cout << "- Harga: Rp 10.000/kg\n";
    cout << "- Diskon: 10% per kelipatan 10kg\n";
    cout << "- Antar-jemput: Gratis <5km, charge >5km\n";
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
    system("cls");
    cout << "\n=== LAUNDRY SELIMUT ===\n";
    
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
    system("cls");
    cout << "\n=== LAUNDRY BED COVER ===\n";
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
    system("cls");
    cout << "\n=== CUCI SEPATU ===\n";
    cout << "Jenis:\n";
    cout << "1. Sports - Rp 50.000\n";
    cout << "2. Sneakers - Rp 45.000\n";
    cout << "3. Anak - Rp 30.000\n";
    cout << "4. Boots - Rp 75.000\n";
    cout << "5. Lainnya - Input manual\n";
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
    system("cls");
    cout << "\n=== CUCI KARPET ===\n";
    cout << "Jenis Pembersihan:\n";
    cout << "1. Manual - Rp 35.000\n";
    cout << "2. Mesin - Rp 40.000\n";
    cout << "3. Steam - Rp 50.000\n";
    cout << "4. Drycleaning - Rp 75.000\n";
    cout << "5. Deepcleaning - Rp 80.000\n";
    cout << "6. Masjid - Rp 85.000\n";
    cout << "7. Kantor - Rp 100.000\n";
    cout << "8. Express - Rp 150.000\n";
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
    system("cls");
    cout << "\n=== CUCI BONEKA ===\n";
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
    system("cls");
    cout << "\n=== CUCI GORDEN ===\n";
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
    system("cls");
    cout << "\n=== CUCI BANTAL ===\n";
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

    
#endif

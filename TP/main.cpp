#include <iostream>
#include "ktp_login.h"
#include "laundry_core.h"
#include "pelanggan.h"
#include "layanan.h"

using namespace std;

int main() {
    // Inisialisasi user default (admin dan kasir)
    initializeDefaultUser();
    
    // Menu Login (menggunakan sistem KTP)
    menuLogin();
    
    // Setelah login berhasil, lanjut ke menu utama TP Laundry
    char ulang = 'y';
    int pilihan;

    do {
        system("cls");
        cout << "     SISTEM MANAJEMEN LAUNDRY PREMIUM          \n";
        cout << "Logged in as: " << currentUserName << " (" << currentUserRole << ")\n";
        cout << "NIK         : " << currentUserNIK << "\n";
        cout << "1.  Laundry Baju\n";
        cout << "2.  Laundry Selimut\n";
        cout << "3.  Laundry Bed Cover\n";
        cout << "4.  Cuci Sepatu\n";
        cout << "5.  Cuci Karpet\n";
        cout << "6.  Cuci Boneka\n";
        cout << "7.  Cuci Gorden\n";
        cout << "8.  Cuci Bantal\n";
        cout << "9.  Tampilkan Riwayat Transaksi\n";
        cout << "10. Ubah Status Laundry\n";
        cout << "11. Tampilkan Total Pendapatan\n";
        cout << "12. Menu Pelanggan\n";
        cout << "13. Undo Aktivitas Terakhir\n";
        cout << "14. Tampilkan History Stack\n";
        cout << "0.  Keluar\n";
        cout << "\nPilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }

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

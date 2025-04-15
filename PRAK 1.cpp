#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    string nama, jenis_bensin;
    int total_liter;
    int harga_per_liter;
    int total_harga;

    const int HARGA_PERTALITE = 7000;
    const int HARGA_PERTAMAX = 9000;

    cout << "Masukkan nama pelanggan: ";
    getline(cin, nama);
    cout << "Masukkan jenis bensin (pertalite/pertamax): ";
    cin >> jenis_bensin;
    cout << "Masukkan jumlah liter: ";
    cin >> total_liter;

    if (jenis_bensin == "pertalite") {
        harga_per_liter = HARGA_PERTALITE;
    } else if (jenis_bensin == "pertamax") {
        harga_per_liter = HARGA_PERTAMAX;
    } else {
        cout << "Jenis bensin tidak valid!" << endl;
        return 1;
    }

    total_harga = total_liter * harga_per_liter;

    cout << "\n====== STRUK PEMBELIAN ======" << endl;
    cout << "Nama Pelanggan  : " << nama << endl;
    cout << "Jenis Bensin    : " << jenis_bensin << endl;
    cout << "Total Liter     : " << total_liter << " liter" << endl;
    cout << "Total Harga     : Rp " << fixed << setprecision(2) << total_harga << endl;
    cout << "==============================" << endl;

    return 0;
}

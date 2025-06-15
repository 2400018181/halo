#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

class KTP {
private:
    long long nik;
    string nama;
    string tempat_tgl_lahir;
    string jenis_kelamin;
    string gol_darah;
    string alamat;
    string rt_rw;
    string kel_desa;
    string kecamatan;
    string agama;
    string status_perkawinan;
    string pekerjaan;
    string kewarganegaraan;
    string berlaku_hingga;

public:
    void input(bool skipNik = false) {
        if (!skipNik) {
            cout << "Masukkan NIK: ";
            cin >> nik;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Masukkan Nama: ";
        getline(cin, nama);
        cout << "Masukkan Tempat/Tgl Lahir: ";
        getline(cin, tempat_tgl_lahir);
        cout << "Masukkan Jenis Kelamin: ";
        getline(cin, jenis_kelamin);
        cout << "Masukkan Golongan Darah (A/B/AB/O): ";
        getline(cin, gol_darah);
        cout << "Masukkan Alamat: ";
        getline(cin, alamat);
        cout << "Masukkan RT/RW: ";
        getline(cin, rt_rw);
        cout << "Masukkan Kelurahan/Desa: ";
        getline(cin, kel_desa);
        cout << "Masukkan Kecamatan: ";
        getline(cin, kecamatan);
        cout << "Masukkan Agama: ";
        getline(cin, agama);
        cout << "Masukkan Status Perkawinan: ";
        getline(cin, status_perkawinan);
        cout << "Masukkan Pekerjaan: ";
        getline(cin, pekerjaan);
        cout << "Masukkan Kewarganegaraan: ";
        getline(cin, kewarganegaraan);
        cout << "Masukkan Berlaku Hingga: ";
        getline(cin, berlaku_hingga);
    }

    void tampil() const {
        const int lebar = 60;
        cout << string(lebar, '=') << endl;
        cout << setw((lebar + 18) / 2) << "KARTU TANDA PENDUDUK (KTP)" << endl;
        cout << string(lebar, '=') << endl;
        cout << left << setw(20) << "NIK" << ": " << nik << endl;
        cout << left << setw(20) << "Nama" << ": " << nama << endl;
        cout << left << setw(20) << "Tempat/Tgl Lahir" << ": " << tempat_tgl_lahir << endl;
        cout << left << setw(20) << "Jenis Kelamin" << ": " << jenis_kelamin << "    Gol Darah: " << gol_darah << endl;
        cout << left << setw(20) << "Alamat" << ": " << alamat << endl;
        cout << left << setw(20) << "RT/RW" << ": " << rt_rw << endl;
        cout << left << setw(20) << "Kel/Desa" << ": " << kel_desa << endl;
        cout << left << setw(20) << "Kecamatan" << ": " << kecamatan << endl;
        cout << left << setw(20) << "Agama" << ": " << agama << endl;
        cout << left << setw(20) << "Status Perkawinan" << ": " << status_perkawinan << endl;
        cout << left << setw(20) << "Pekerjaan" << ": " << pekerjaan << endl;
        cout << left << setw(20) << "Kewarganegaraan" << ": " << kewarganegaraan << endl;
        cout << left << setw(20) << "Berlaku Hingga" << ": " << berlaku_hingga << endl;
        cout << string(lebar, '=') << endl;
    }

    long long getNIK() const {
        return nik;
    }

    void edit() {
        int pilihan;
        string inputBaru;

        do {
            cout << "\n== MENU EDIT DATA KTP ==\n";
            cout << "1. Nama\n2. Tempat/Tgl Lahir\n3. Jenis Kelamin\n4. Golongan Darah\n5. Alamat\n";
            cout << "6. RT/RW\n7. Kelurahan/Desa\n8. Kecamatan\n9. Agama\n10. Status Perkawinan\n";
            cout << "11. Pekerjaan\n12. Kewarganegaraan\n13. Berlaku Hingga\n0. Selesai\n";
            cout << "Pilihan Anda: ";
            cin >> pilihan;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (pilihan) {
                case 1: cout << "Nama baru: "; getline(cin, nama); break;
                case 2: cout << "Tempat/Tgl Lahir baru: "; getline(cin, tempat_tgl_lahir); break;
                case 3: cout << "Jenis Kelamin baru: "; getline(cin, jenis_kelamin); break;
                case 4: cout << "Golongan Darah baru: "; getline(cin, gol_darah); break;
                case 5: cout << "Alamat baru: "; getline(cin, alamat); break;
                case 6: cout << "RT/RW baru: "; getline(cin, rt_rw); break;
                case 7: cout << "Kel/Desa baru: "; getline(cin, kel_desa); break;
                case 8: cout << "Kecamatan baru: "; getline(cin, kecamatan); break;
                case 9: cout << "Agama baru: "; getline(cin, agama); break;
                case 10: cout << "Status Perkawinan baru: "; getline(cin, status_perkawinan); break;
                case 11: cout << "Pekerjaan baru: "; getline(cin, pekerjaan); break;
                case 12: cout << "Kewarganegaraan baru: "; getline(cin, kewarganegaraan); break;
                case 13: cout << "Berlaku Hingga baru: "; getline(cin, berlaku_hingga); break;
                case 0: cout << "Selesai mengedit.\n"; break;
                default: cout << "Pilihan tidak valid.\n"; break;
            }
        } while (pilihan != 0);
    }
};

// Fungsi untuk mencari dan mengedit KTP berdasarkan NIK
void cariDanEdit(vector<KTP> &daftar) {
    long long cariNik;
    cout << "Masukkan NIK yang ingin diedit: ";
    cin >> cariNik;
    cin.ignore();

    for (int i = 0; i < daftar.size(); ++i) {
    if (daftar[i].getNIK() == cariNik) {
        daftar[i].edit();
   		 }
	}

    cout << "Data dengan NIK tersebut tidak ditemukan.\n";
}

bool bandingkanNIK(const KTP &a, const KTP &b) {
    return a.getNIK() < b.getNIK();
	}

int main() {
    vector<KTP> daftarKTP;
    int jumlah;

    cout << "Masukkan jumlah data KTP: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; ++i) {
        cout << "\nData ke-" << (i + 1) << ":\n";
        KTP ktp;
        ktp.input();
        daftarKTP.push_back(ktp);
    }
    
    

    // Pengurutan berdasarkan NIK
    sort(daftarKTP.begin(), daftarKTP.end(), bandingkanNIK);


    // Tampilkan data
    cout << "\n=== DATA KTP SETELAH DIURUTKAN BERDASARKAN NIK ===\n";
    for (int i = 0; i < daftarKTP.size(); ++i) {
    daftarKTP[i].tampil();
	}


    char editLagi;
    cout << "\nApakah ingin mengedit salah satu data? (y/n): ";
    cin >> editLagi;
    cin.ignore();

    if (editLagi == 'y' || editLagi == 'Y') {
        cariDanEdit(daftarKTP);
    }

    // Tampilkan ulang setelah edit
    cout << "\n=== DATA KTP TERBARU ===\n";
   for (int i = 0; i < daftarKTP.size(); ++i) {
    // proses pakai daftarKTP[i]
}


    return 0;
}


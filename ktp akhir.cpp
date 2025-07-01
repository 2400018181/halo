#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
using namespace std;

class ktp {
public:
    void inputdata();
    void tampilkandata() const;
    string getNama() const { return nama; }
    long long getNik() const { return nik; }

    string jk, agama;

private:
    string nama, tempat, tgl, alamat, desa, kec, kawin, pekerjaan, warga, berlaku;
    long long nik;
    int rt, rw, pil;

    friend void simpanKeFile(const ktp data[], int n);
};

void ktp::inputdata() {
    cout << "masukkan nik : ";
    cin >> nik;
    cin.ignore();
    cout << "masukkan nama : ";
    getline(cin, nama);
    cout << "masukkan tempat lahir : ";
    getline(cin, tempat);
    cout << "masukkan tanggal lahir : ";
    getline(cin, tgl);
    do {
        cout << "Masukkan Jenis Kelamin (L/P): ";
        getline(cin, jk);
        if (jk != "L" && jk != "P") {
            cout << "Input tidak valid! Masukkan 'L' atau 'P'.\n";
        }
    } while (jk != "L" && jk != "P");

    cout << "masukkan alamat : ";
    getline(cin, alamat);
    cout << "masukkan rt : ";
    cin >> rt;
    cout << "masukkan rw : ";
    cin >> rw;
    cin.ignore();
    cout << "masukkan desa : ";
    getline(cin, desa);
    cout << "masukkan kecamatan : ";
    getline(cin, kec);
    cout << "pilih agama : ";
    cout << "\n1. Islam\n2. Katholik\n3. Protestan\n4. Hindu\n5. Konghucu\n6. Buddha\n";
    cin >> pil;
    switch (pil) {
        case 1: agama = "Islam"; break;
        case 2: agama = "Katholik"; break;
        case 3: agama = "Protestan"; break;
        case 4: agama = "Hindu"; break;
        case 5: agama = "Konghucu"; break;
        case 6: agama = "Buddha"; break;
        default: agama = "Lainnya";
    }
    cin.ignore();
    cout << "masukkan Status perkawinan : ";
    getline(cin, kawin);
    cout << "masukkan pekerjaan : ";
    getline(cin, pekerjaan);
    cout << "masukkan kewarganegaraan : ";
    getline(cin, warga);
    cout << "masukkan masa berlaku : ";
    getline(cin, berlaku);
}

void ktp::tampilkandata() const {
    cout << "==============================================" << endl;
    cout << "\t\tProvinsi Yogyakarta" << endl;
    cout << "==============================================" << endl;
    cout << "NIK\t\t\t: " << nik << endl;
    cout << "Nama\t\t\t: " << nama << endl;
    cout << "Tempat/Tgl Lahir\t: " << tempat << ", " << tgl << endl;
    cout << "Jenis kelamin\t\t: " << (jk == "L" ? "Laki-laki" : "Perempuan") << endl;
    cout << "Alamat\t\t\t: " << alamat << endl;
    cout << "     RT/RW\t\t: " << rt << "/" << rw << endl;
    cout << "     Kel/Desa\t\t: " << desa << endl;
    cout << "     Kecamatan\t\t: " << kec << endl;
    cout << "Agama\t\t\t: " << agama << endl;
    cout << "Status Perkawinan\t: " << kawin << endl;
    cout << "Pekerjaan\t\t: " << pekerjaan << endl;
    cout << "Kewarganegaraan\t\t: " << warga << endl;
    cout << "Berlaku Hingga\t\t: " << berlaku << endl;
    cout << "==============================================" << endl;
}

void simpanKeFile(const ktp data[], int n) {
    ofstream file("data_ktp.txt");
    for (int i = 0; i < n; ++i) {
        file << "==============================================" << endl;
        file << "NIK: " << data[i].getNik() << endl;
        file << "Nama: " << data[i].getNama() << endl;
        file << "Tempat/Tgl Lahir: " << data[i].tempat << ", " << data[i].tgl << endl;
        file << "Jenis Kelamin: " << (data[i].jk == "L" ? "Laki-laki" : "Perempuan") << endl;
        file << "Alamat: " << data[i].alamat << " RT/RW: " << data[i].rt << "/" << data[i].rw << endl;
        file << "Kel/Desa: " << data[i].desa << ", Kecamatan: " << data[i].kec << endl;
        file << "Agama: " << data[i].agama << ", Status Kawin: " << data[i].kawin << endl;
        file << "Pekerjaan: " << data[i].pekerjaan << ", Kewarganegaraan: " << data[i].warga << endl;
        file << "Berlaku Hingga: " << data[i].berlaku << endl;
        file << "==============================================" << endl << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke file data_ktp.txt" << endl;
}

bool bandingNik(const ktp& a, const ktp& b) {
    return a.getNik() > b.getNik();
}

void editDataByNik(ktp data[], int jumlah) {
    long long target;
    cout << "Masukkan NIK yang ingin diedit: ";
    cin >> target;
    cin.ignore();
    bool ditemukan = false;

    for (int i = 0; i < jumlah; i++) {
        if (data[i].getNik() == target) {
            cout << "Data ditemukan. Silakan input ulang data:\n";
            data[i].inputdata();
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Data dengan NIK tersebut tidak ditemukan.\n";
}

void hapusDataByNik(ktp data[], int& jumlah) {
    long long target;
    cout << "Masukkan NIK yang ingin dihapus: ";
    cin >> target;
    cin.ignore();
    bool ditemukan = false;

    for (int i = 0; i < jumlah; i++) {
        if (data[i].getNik() == target) {
            for (int j = i; j < jumlah - 1; j++) {
                data[j] = data[j + 1]; // geser data ke kiri
            }
            jumlah--;
            ditemukan = true;
            cout << "Data berhasil dihapus.\n";
            break;
        }
    }
    if (!ditemukan) cout << "Data dengan NIK tersebut tidak ditemukan.\n";
}

void jumlahGender(const ktp data[], int jumlah) {
    int laki = 0, perempuan = 0;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].jk == "L") laki++;
        else if (data[i].jk == "P") perempuan++;
    }
    cout << "Jumlah Laki-laki: " << laki << endl;
    cout << "Jumlah Perempuan: " << perempuan << endl;
}

void tampilkanByAgama(const ktp data[], int jumlah) {
    string agamaCari;
    cout << "Masukkan agama yang ingin ditampilkan (Contoh: Islam): ";
    getline(cin, agamaCari);
    bool ditemukan = false;

    for (int i = 0; i < jumlah; i++) {
        if (data[i].agama == agamaCari) {
            data[i].tampilkandata();
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Tidak ada data dengan agama tersebut.\n";
}

int main() {
    int jumlah;
    cout << "Masukkan jumlah data KTP: ";
    cin >> jumlah;
    cin.ignore();

    ktp* data = new ktp[jumlah];
    string tabel[100][2];

    for (int i = 0; i < jumlah; i++) {
        cout << "\nData ke-" << i + 1 << endl;
        data[i].inputdata();
    }

    int pilihan;
    string cari;
    do {
        cout << "\nMenu:\n"
             << "1. Tampilkan Semua Data\n"
             << "2. Cari Nama\n"
             << "3. Urutkan NIK (Tinggi ke Rendah)\n"
             << "4. Simpan ke File\n"
             << "5. List KTP Terdaftar\n"
             << "6. Keluar\n"
             << "7. Edit Data Berdasarkan NIK\n"
             << "8. Hapus Data Berdasarkan NIK\n"
             << "9. Jumlah Laki-laki dan Perempuan\n"
             << "10. Tampilkan Berdasarkan Agama\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                for (int i = 0; i < jumlah; i++) {
                    data[i].tampilkandata();
                }
                break;
            case 2:
                cout << "Masukkan nama yang dicari: ";
                getline(cin, cari);
                {
                    bool ditemukan = false;
                    for (int i = 0; i < jumlah; i++) {
                        if (data[i].getNama() == cari) {
                            data[i].tampilkandata();
                            ditemukan = true;
                        }
                    }
                    if (!ditemukan) cout << "Nama tidak ditemukan.\n";
                }
                break;
            case 3:
                sort(data, data + jumlah, bandingNik);
                cout << "Data berhasil diurutkan berdasarkan NIK (tinggi ke rendah).\n";
                break;
            case 4:
                simpanKeFile(data, jumlah);
                break;
            case 5:
                for (int i = 0; i < jumlah; i++) {
                    tabel[i][0] = data[i].getNama();
                    stringstream ss;
                    ss << data[i].getNik();
                    tabel[i][1] = ss.str();
                }

                cout << "=================================================\n";
                cout << "Nama\t\t\tNIK\n";
                for (int i = 0; i < jumlah; i++) {
                    cout << tabel[i][0] << "\t\t" << tabel[i][1] << endl;
                }
                cout << "=================================================\n";
                break;
            case 6:
                cout << "Terima kasih.\n";
                break;
            case 7:
                editDataByNik(data, jumlah);
                break;
            case 8:
                hapusDataByNik(data, jumlah);
                break;
            case 9:
                jumlahGender(data, jumlah);
                break;
            case 10:
                tampilkanByAgama(data, jumlah);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 6);

    delete[] data;
    return 0;
}


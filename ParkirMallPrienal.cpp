#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Kendaraan{
    string platMobil;
    string merkMobil;
    string warnaMobil;
    time_t waktuMasuk;
};

struct Petugas{
    string nama;
    string id;
};

class ParkirMall{
    private:
    vector<Kendaraan*> daftarParkir;
    Petugas dataPetugas;
    Petugas* petugas = &dataPetugas;
    const int KAPASITAS = 20;
    const int TARIF_PER_DETIK = 2;

    public:
    string formatWaktu(double detik){
        int jam = (int)detik / 3600;
        int menit = ((int)detik % 3600) / 60;
        int dtk = (int)detik % 60;
        return to_string(jam) + " jam " + to_string(menit) + " menit " + to_string(dtk) + " detik";
    }

    void inputPetugas(){
        cout << "===============================================================================" << endl;
        cout << "-------------------------- S E L A M A T  D A T A N G ------------------------" << endl;
        cout << "                          DI PORTAL PARKIR KHUSUS MOBIL" << endl;
        cout << "                                  MALL PRIENAL" << endl;
        cout << "===============================================================================" << endl;
        cout << "\nKami senang Anda telah hadir." << endl;
        cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n" << endl;
        cout << "Masukkan nama : "; getline(cin, petugas->nama);
        cout << "Masukkan ID   : "; getline(cin, petugas->id);
    }

    void tampilkanMenu(){
        cout << "===============================================================================" << endl;
        cout << "Nama Petugas : " << petugas->nama << endl;
        cout << "ID Petugas   : " << petugas->id << endl;
        cout << "\n                    TERIMA KASIH ATAS KERJASAMANYA !" << endl;
        cout << "-------------------------- S E L A M A T  B E R T U G A S -------------------" << endl;
        cout << "===============================================================================\n" << endl;
        cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
        cout << "1. Tambahkan Daftar Kendaraan" << endl;
        cout << "2. Tampilkan Daftar Kendaraan" << endl;
        cout << "3. Pembayaran" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "Masukkan opsi : "; 
    }

    void tambahKendaraan(){
        int jumlah;
        cout << "Masukan jumlah mobil yang akan di parkirkan : "; cin >> jumlah;
        cin.ignore();

        if ((int)daftarParkir.size() >= KAPASITAS){
            cout << "Maaf, parkiran hanya dapat memuat " << KAPASITAS << " mobil !" << endl;
            return;
        }

        int tersedia = KAPASITAS - (int)daftarParkir.size();
        if (jumlah > tersedia){
            cout << "Maaf, parkiran hanya dapat memuat " << KAPASITAS << " mobil." << endl;
            jumlah = tersedia;
        }

        for (int i = 0; i < jumlah; i++){
            if ((int)daftarParkir.size() >= KAPASITAS){
                cout << "Maaf, parkiran hanya dapat memuat " << KAPASITAS << " mobil !" << endl;
                break;
            }
            Kendaraan* mobil = new Kendaraan();
            cout << "\nMobil ke " << (daftarParkir.size() + 1) << endl;
            cout << "Masukkan plat mobil  : "; getline(cin, mobil->platMobil);
            cout << "Masukkan merk mobil  : "; getline(cin, mobil->merkMobil);
            cout << "Masukkan warna mobil : "; getline(cin, mobil->warnaMobil);
            mobil->waktuMasuk = time(nullptr);
            daftarParkir.push_back(mobil);
        }
    }

    void tampilkanDaftarKendaraan(){
        if (daftarParkir.empty()){
            cout << "Tidak ada kendaraan yang sedang parkir." << endl;
            return;
        }
        cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :" << endl;
        for (int i = 0; i < (int)daftarParkir.size(); i++){
            cout << "============================================================" << endl;
            double durasi = difftime(time(nullptr), daftarParkir[i]->waktuMasuk);
            cout << "Mobil ke-" << (i + 1) << endl;
            cout << "Plat mobil   : " << daftarParkir[i]->platMobil << endl;
            cout << "Merk mobil   : " << daftarParkir[i]->merkMobil << endl;
            cout << "Warna mobil  : " << daftarParkir[i]->warnaMobil << endl;
            cout << "Waktu parkir : " << formatWaktu(durasi) << endl;
        }
        cout << "============================================================" << endl;
    }

    void pembayaran(){
        if (daftarParkir.empty()){
            cout << "Tidak ada kendaraan yang sedang parkir." << endl;
            return;
        }
        tampilkanDaftarKendaraan();

        string plat;
        bool ditemukan = false;
        while (true) {
            cout << "\nMasukkan plat mobil yang ingin dibayar : "; getline(cin, plat);
            ditemukan = false;
            for (int i = 0; i < (int)daftarParkir.size(); i++){
                if (daftarParkir[i]->platMobil == plat){
                    ditemukan = true;
                    double durasi = difftime(time(nullptr), daftarParkir[i]->waktuMasuk);
                    long long biaya = (long long)(durasi * TARIF_PER_DETIK);
                    cout << "\nB I A Y A  P A R K I R : Rp" << biaya << endl;
                    cout << "============================================================" << endl;
                    delete daftarParkir[i];
                    daftarParkir.erase(daftarParkir.begin() + i);
                    break;
                }
            }
            if (!ditemukan) cout << "PLAT TIDAK DITEMUKAN !" << endl;
            else break;
        }
    }

    void run(){
        inputPetugas();
        int opsi;
        do {
            cout << endl;
            tampilkanMenu();
            cin >> opsi;
            cin.ignore();
            cout << endl;
            switch (opsi){
                case 1: tambahKendaraan(); break;
                case 2: tampilkanDaftarKendaraan(); break;
                case 3: pembayaran(); break;
                case 4: cout << "Terima kasih, selamat tinggal!" << endl; break;
                default: cout << "Opsi tidak valid. Silahkan coba lagi." << endl;
            }
        } while (opsi != 4);

        for (Kendaraan* k : daftarParkir) delete k;
    }
};

int main(){
    ParkirMall sistem;
    sistem.run();
    return 0;
}

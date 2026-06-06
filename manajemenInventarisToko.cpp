#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

vector<Barang> inventaris;

void tambahBarang() {
    Barang b;
    cout << "\n-- TAMBAH BARANG --\n";

    cout << "Kode Barang : "; cin >> b.kodeBarang;

    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == b.kodeBarang) {
            cout << "Kode sudah ada!\n";
            return;
        }
    }

    cin.ignore();
    cout << "Nama Barang : "; getline(cin, b.namaBarang);

    do {
    cout << "Harga : "; cin >> b.harga;
    if (b.harga < 0)
        cout << "Harga tidak boleh negatif!\n";}
    while (b.harga < 0);
    
    do {
        cout << "Stok : "; cin >> b.stok;
        if (b.stok < 0)
            cout << "Stok tidak boleh negatif!\n";}
    while (b.stok < 0);

    inventaris.push_back(b);
    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanBarang() {
    cout << "\n-- DAFTAR BARANG --\n";
    if (inventaris.empty()) { cout << "Inventaris kosong.\n"; return; }

    cout << left << setw(12) << "Kode" << setw(20) << "Nama" << setw(15) << "Harga" << "Stok\n";
    cout << string(55, '-') << "\n";
    for (int i = 0; i < inventaris.size(); i++) {
        cout << left << setw(12) << inventaris[i].kodeBarang
             << setw(20) << inventaris[i].namaBarang
             << setw(15) << inventaris[i].harga
             << inventaris[i].stok << "\n";
    }
}

void cariTermahal() {
    cout << "\n-- BARANG TERMAHAL --\n";
    if (inventaris.empty()) { cout << "Inventaris kosong.\n"; return; }

    int idx = 0;
    for (int i = 1; i < inventaris.size(); i++) {
        if (inventaris[i].harga > inventaris[idx].harga) idx = i;
    }

    cout << "Kode  : " << inventaris[idx].kodeBarang << "\n";
    cout << "Nama  : " << inventaris[idx].namaBarang << "\n";
    cout << "Harga : Rp " << inventaris[idx].harga << "\n";
    cout << "Stok  : " << inventaris[idx].stok << "\n";
}

void totalNilai() {
    cout << "\n-- TOTAL NILAI INVENTARIS --\n";
    if (inventaris.empty()) { cout << "Inventaris kosong.\n"; return; }

    double total = 0;
    for (int i = 0; i < inventaris.size(); i++) {
        total += inventaris[i].harga * inventaris[i].stok;
    }
    cout << "Total Nilai : Rp " << total << "\n";
}

void cekRestock() {
    cout << "\n-- BARANG PERLU RESTOCK (stok < 5) --\n";
    if (inventaris.empty()) { cout << "Inventaris kosong.\n"; return; }

    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].stok < 5) {
            cout << inventaris[i].kodeBarang << " - " << inventaris[i].namaBarang
                 << " (stok: " << inventaris[i].stok << ")\n";
        }
        else cout<<"-";
    }
}

void updateStok() {
    cout << "\n-- UPDATE STOK --\n";
    if (inventaris.empty()) { cout << "Inventaris kosong.\n"; return; }

    string kode;
    cout << "Kode barang : "; cin >> kode;

    int* ptrStok = nullptr;
    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == kode) {
            ptrStok = &inventaris[i].stok;
            cout << "Barang : " << inventaris[i].namaBarang << " | Stok: " << *ptrStok << "\n";
            break;
        }
    }

    if (ptrStok == nullptr) { cout << "Barang tidak ditemukan.\n"; return; }

    int opsi, jumlah;
    cout << "1. Tambah  2. Kurangi\nPilihan: "; cin >> opsi;
    cout << "Jumlah  : "; cin >> jumlah;

    if (jumlah < 0) { cout << "Jumlah tidak boleh negatif!\n"; return; }

    if (opsi == 1) {
        *ptrStok += jumlah;
    } else if (opsi == 2) {
        if (jumlah > *ptrStok) { cout << "Stok tidak cukup!\n"; return; }
        *ptrStok -= jumlah;
    } else {
        cout << "Pilihan tidak valid.\n"; return;
    }

    cout << "Stok sekarang: " << *ptrStok << "\n";
}

int main() {
    int pilihan;
    cout << "=== Sistem Manajemen Inventaris Toko ===\n";

    do {
        cout << "\n1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Barang Termahal\n";
        cout << "4. Total Nilai Inventaris\n";
        cout << "5. Cek Restock\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "Pilihan: "; cin >> pilihan;

        if (pilihan == 1) tambahBarang();
        else if (pilihan == 2) tampilkanBarang();
        else if (pilihan == 3) cariTermahal();
        else if (pilihan == 4) totalNilai();
        else if (pilihan == 5) cekRestock();
        else if (pilihan == 6) updateStok();
        else if (pilihan == 7) cout << "Keluar. Sampai jumpa!\n";
        else cout << "Pilihan tidak valid.\n";

    } while (pilihan != 7);

    return 0;
}

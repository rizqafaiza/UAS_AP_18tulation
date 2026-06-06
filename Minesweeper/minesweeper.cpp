#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Minesweeper {
private:
    int n, bom;
    int papan[10][10];
    bool buka[10][10];
    bool tanda[10][10];
    bool selesai, menang;
    time_t waktuMulai;

    bool valid(int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

    void clearScreen() {
        system("cls");
    }

    void pause() {
        cout << "\nTekan ENTER untuk lanjut...";
        cin.ignore();
        cin.get();
    }

    void inputAwal() {
        do {
            clearScreen();
            cout << "=== PENGATURAN PAPAN ===\n";
            cout << "Masukkan ukuran papan (4 - 10): ";
            cin >> n;

            if (n < 4 || n > 10) {
                cout << "Ukuran papan harus 4 sampai 10.\n";
                pause();
            }
        } while (n < 4 || n > 10);

        do {
            clearScreen();
            cout << "=== PENGATURAN BOM ===\n";
            cout << "Ukuran papan: " << n << " x " << n << endl;
            cout << "Masukkan jumlah bom: ";
            cin >> bom;

            if (bom < 1 || bom >= n * n) {
                cout << "Jumlah bom harus minimal 1 dan kurang dari jumlah kotak.\n";
                pause();
            }
        } while (bom < 1 || bom >= n * n);
    }

    void resetPapan() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                papan[i][j] = 0;
                buka[i][j] = false;
                tanda[i][j] = false;
            }
        }
    }

    void pasangBom() {
        int jumlah = 0;

        while (jumlah < bom) {
            int r = rand() % n;
            int c = rand() % n;

            if (papan[r][c] != -1) {
                papan[r][c] = -1;
                jumlah++;
            }
        }
    }

    void hitungAngka() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (papan[i][j] == -1) {
                    continue;
                }

                int total = 0;

                for (int a = -1; a <= 1; a++) {
                    for (int b = -1; b <= 1; b++) {
                        int x = i + a;
                        int y = j + b;

                        if (valid(x, y) && papan[x][y] == -1) {
                            total++;
                        }
                    }
                }

                papan[i][j] = total;
            }
        }
    }

    int jumlahTanda() {
        int total = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tanda[i][j]) {
                    total++;
                }
            }
        }

        return total;
    }

    void tampilPapan() {
        int waktu = time(0) - waktuMulai;

        cout << "=== MINESWEEPER++ ===\n";
        cout << "Ukuran papan : " << n << " x " << n << endl;
        cout << "Jumlah bom   : " << bom << endl;
        cout << "Sisa bom     : " << bom - jumlahTanda() << endl;
        cout << "Waktu        : " << waktu << " detik\n\n";

        cout << "   ";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            if (i + 1 < 10) {
                cout << " ";
            }

            cout << i + 1 << " ";

            for (int j = 0; j < n; j++) {
                if (tanda[i][j]) {
                    cout << "F ";
                } else if (!buka[i][j]) {
                    cout << "# ";
                } else if (papan[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << papan[i][j] << " ";
                }
            }

            cout << endl;
        }
    }

    void tampilPapanAkhir() {
        cout << "=== PAPAN AKHIR ===\n\n";

        cout << "   ";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            if (i + 1 < 10) {
                cout << " ";
            }

            cout << i + 1 << " ";

            for (int j = 0; j < n; j++) {
                if (papan[i][j] == -1) {
                    cout << "* ";
                } else if (papan[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << papan[i][j] << " ";
                }
            }

            cout << endl;
        }
    }

    void floodFill(int r, int c) {
        if (!valid(r, c)) {
            return;
        }

        if (buka[r][c] || tanda[r][c]) {
            return;
        }

        if (papan[r][c] == -1) {
            return;
        }

        buka[r][c] = true;

        if (papan[r][c] != 0) {
            return;
        }

        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (a != 0 || b != 0) {
                    floodFill(r + a, c + b);
                }
            }
        }
    }

    void bukaKotak(int r, int c) {
        if (buka[r][c]) {
            cout << "Kotak sudah terbuka.\n";
            return;
        }

        if (tanda[r][c]) {
            cout << "Kotak sedang ditandai. Hapus tanda dulu.\n";
            return;
        }

        if (papan[r][c] == -1) {
            selesai = true;
            menang = false;
            return;
        }

        floodFill(r, c);
    }

    void tandaiKotak(int r, int c) {
        if (buka[r][c]) {
            cout << "Kotak yang sudah terbuka tidak bisa ditandai.\n";
            return;
        }

        tanda[r][c] = !tanda[r][c];

        if (tanda[r][c]) {
            cout << "Kotak ditandai.\n";
        } else {
            cout << "Tanda dihapus.\n";
        }
    }

    void cekMenang() {
        int totalTanda = 0;
        int tandaBenar = 0;
        int tandaSalah = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tanda[i][j]) {
                    totalTanda++;

                    if (papan[i][j] == -1) {
                        tandaBenar++;
                    } else {
                        tandaSalah++;
                    }
                }
            }
        }

        if (totalTanda == bom && tandaBenar == bom && tandaSalah == 0) {
            selesai = true;
            menang = true;
        }
    }

public:
    void mainkan() {
        inputAwal();
        resetPapan();
        pasangBom();
        hitungAngka();

        selesai = false;
        menang = false;
        waktuMulai = time(0);

        while (!selesai) {
            clearScreen();
            tampilPapan();

            int aksi, r, c;

            cout << "\nAksi:\n";
            cout << "1. Buka kotak\n";
            cout << "2. Tandai / hapus tanda\n";
            cout << "Pilih aksi: ";
            cin >> aksi;

            if (aksi != 1 && aksi != 2) {
                cout << "Aksi tidak valid.\n";
                pause();
                continue;
            }

            cout << "Masukkan baris: ";
            cin >> r;
            cout << "Masukkan kolom: ";
            cin >> c;

            r--;
            c--;

            if (!valid(r, c)) {
                cout << "Koordinat tidak valid.\n";
                pause();
                continue;
            }

            if (aksi == 1) {
                bukaKotak(r, c);
            } else {
                tandaiKotak(r, c);
            }

            if (!selesai) {
                cekMenang();
            }

            if (!selesai) {
                pause();
            }
        }

        clearScreen();
        tampilPapanAkhir();

        int lamaMain = time(0) - waktuMulai;

        if (menang) {
            cout << "\nYEAAAYYY Menang!\n";
        } else {
            cout << "\nDUAAARRR! Bom Meledak.\n";
        }

        cout << "Waktu bermain: " << lamaMain << " detik\n";
        pause();
    }
};

int main() {
    srand(time(0));

    int menu;

    do {
        system("cls");

        cout << "=== MENU UTAMA MINESWEEPER ===\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if (menu == 1) {
            Minesweeper game;
            game.mainkan();
        } else if (menu == 2) {
            cout << "Program selesai.\n";
        } else {
            cout << "Menu tidak valid.\n";
            cout << "\nTekan ENTER untuk lanjut...";
            cin.ignore();
            cin.get();
        }

    } while (menu != 2);

    return 0;
}
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

Game::Game()
{
    skor = 0;
    isiNegara();
}

void Game::isiNegara()
{
    string negara[] =
    {
        "indonesia",
        "malaysia",
        "singapore",
        "thailand",
        "vietnam",
        "laos",
        "cambodia",
        "myanmar",
        "philippines",
        "japan",
        "china",
        "india",
        "pakistan",
        "nepal",
        "bhutan",
        "brunei",
        "oman",
        "norway",
        "sweden",
        "finland",
        "denmark",
        "germany",
        "france",
        "italy",
        "spain",
        "portugal",
        "canada",
        "mexico",
        "brazil",
        "argentina",
        "chile",
        "peru",
        "colombia",
        "egypt",
        "morocco",
        "algeria",
        "australia",
        "newzealand",
        "russia",
        "ukraine"
    };

    int jumlah = sizeof(negara)/sizeof(negara[0]);

    for(int i = 0; i < jumlah; i++)
    {
        Negara n;
        n.nama = negara[i];
        daftarNegara.push_back(n);
    }
}

string Game::buatSoal(const string& negara)
{
    string hasil = negara;

    int panjang = negara.length();

    int jumlahHilang = panjang / 2;

    for(int i = 0; i < jumlahHilang; i++)
    {
        int posisi = rand() % panjang;

        hasil[posisi] = '_';
    }

    return hasil;
}

bool Game::cekJawaban(string jawaban,
                      const string& negara)
{
    transform(jawaban.begin(),
              jawaban.end(),
              jawaban.begin(),
              ::tolower);

    return jawaban == negara;
}

void Game::mulai()
{
    char lanjut = 'y';

    while(lanjut == 'y' || lanjut == 'Y')
    {
        int index = rand() % daftarNegara.size();

        /*
            POINTER
        */
        Negara* ptrNegara = &daftarNegara[index];

        string soal = buatSoal(ptrNegara->nama);

        cout << "\nTebak negara : "
             << soal << endl;

        string jawaban;
        cout << "Negara apakah yang dimaksud? ";
        cin >> jawaban;

        if(cekJawaban(jawaban, ptrNegara->nama))
        {
            cout << "Selamat! Anda benar.\n";
            skor++;
        }
        else
        {
            cout << "Maaf, jawaban Anda salah.\n";
            cout << "Jawaban yang benar: "
                 << ptrNegara->nama << endl;
        }

        cout << "Skor Anda : "
             << skor << endl;

        cout << "Ingin bermain lagi? (y/n): ";
        cin >> lanjut;
    }

    cout << "\nGame Selesai :D\n";
    cout << "Total Skor : "
         << skor << endl;
}

int main()
{
    srand(time(0));

    Game game;

    game.mulai();

    return 0;
}
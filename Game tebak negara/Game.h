#ifndef GAME_H
#define GAME_H

#include "Negara.h"
#include <vector>

class Game
{
private:
    std::vector<Negara> daftarNegara;
    int skor;

public:
    Game();

    void isiNegara();
    std::string buatSoal(const std::string& negara);
    bool cekJawaban(std::string jawaban,
                    const std::string& negara);

    void mulai();
};

#endif
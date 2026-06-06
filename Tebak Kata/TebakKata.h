#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

struct KataGame{
    std::string kataAsli;
    std::string statusTebakan;
    int sisa_nyawa;
    std::vector<char>tebakanSalah;
    int jumlahSalah;
};

struct StatusPlayer{
    std::vector<int>skor;
};

class Game{
    private:
    std::string kata[15]={"hujan","bulan","kuman","badai","bukit",
    "danau","hutan","flora","fauna","hantu",
    "bunga","kawah", "badak","gurun","semut"};

    KataGame ronde;
    StatusPlayer data;
    StatusPlayer* player = &data;

    public:
    void tingkat_kesulitan(int *skor){
        int pilih;

        std::cout<<"1. Easy\n2. Medium\n3. Hard\n";
        std::cout <<"pilihan: "; std::cin>>pilih;
        switch(pilih){
            case 1: ronde.sisa_nyawa=8; *skor=50;
                break;
            case 2: ronde.sisa_nyawa=6; *skor=70;
                break;
            case 3: ronde.sisa_nyawa=4; *skor=100;
                break;
            default: std::cout<<"pilihan tidak valid"<<std::endl;
                     exit(0);
        }
    }

    int sisaNyawa(int *x){
        *x-=1;
        return*x;
    }

    void cekJawaban(KataGame *game,char huruf){
        bool cocok=false,ada=false;

        for(int i=0;i<game->kataAsli.length();i++){
            if(game->kataAsli[i]==huruf){
                game->statusTebakan[i]=huruf;
                cocok=true;
            }
        }

        for(char c:game->tebakanSalah){
            if(c==huruf){
                ada=true;
                break;
            }
        }

        if(!cocok){
            if(ada){
                std::cout<<"coba huruf lain (^_^)"<<std::endl;
                game->jumlahSalah+=1;
            } else if(huruf=='1'){
                game->statusTebakan[0]=game->kataAsli[0];
                game->tebakanSalah.push_back(huruf);
                sisaNyawa(&ronde.sisa_nyawa);
            } else {
                std::cout<<"tebakan salah (T~T)"<<std::endl;
                game->tebakanSalah.push_back(huruf);
                game->jumlahSalah+=1;
                sisaNyawa(&ronde.sisa_nyawa);
            }
        }
    }

    void play(){
        char huruf;
        int skor=0;
        
        tingkat_kesulitan(&skor);

        srand(time(0));
        ronde.kataAsli= kata[rand()%15];

        ronde.statusTebakan="";
        for(int i=0;i<ronde.kataAsli.size();i++){
            ronde.statusTebakan+="_";
        }

        ronde.jumlahSalah=0;

        do{
            system ("cls");
            std::cout<<ronde.statusTebakan<<"\nketik 1 untuk meminta hint (*U*)\n!!hint mengurangi 1 nyawa!! (hanya bisa digunakan sekali)"<<std::endl;
            std::cout<<"sisa nyawa: "<<ronde.sisa_nyawa<<"\n\n";
            std::cout<<"masukkan jawaban: ";std::cin>>huruf;
            cekJawaban(&ronde,huruf);
            system("pause");

            if(ronde.statusTebakan==ronde.kataAsli){
                skor= skor + (ronde.sisa_nyawa*10) -(ronde.jumlahSalah * 2);
                player->skor.push_back(skor);
                std::cout<<"selamat!! Anda menang (*o*)"<<std::endl;
            } else if(ronde.sisa_nyawa<=0){
                std::cout<<"anda kalah (T~T)"<<std::endl;
            }
        }while((ronde.statusTebakan!=ronde.kataAsli) && (ronde.sisa_nyawa>0));
    }

    void leaderboard(){
        int temp;
        for(int pass=0;pass<player->skor.size()-1;pass++){
            for(int i=1;i<player->skor.size();i++){
                if(player->skor[i-1]<player->skor[i]){
                    temp=player->skor[i];
                    player->skor[i]=player->skor[i-1];
                    player->skor[i-1]=temp;
                }
            }
        }

        std::cout<<"\nLeaderboard:\n";
        for(int i=0;i<player->skor.size();i++){
            std::cout<< i+1<< ". " << "\t" << player->skor[i] <<std::endl;
        }
    }
};

#include <iostream>
#include "TebakKata.h"

int main(){
    char pilih;
    Game tebak;
    do{
        system ("cls");
        tebak.play();
        tebak.leaderboard();
        std::cout<<"apakah anda ingin mengulang program? (y/n)"; std::cin>>pilih;
    }while(pilih=='y' || pilih=='Y');
}
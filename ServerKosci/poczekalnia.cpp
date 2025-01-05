#include "poczekalnia.h"

using namespace std;

PlayerManager gracz;

Poczekalnia::Poczekalnia() {}

Partia Poczekalnia::pokoje[ILEPOKOI];

void Poczekalnia::podajPokoje(int usr){
    string msg="";
    for(int i=0;i<ILEPOKOI;i++){
        if(pokoje[i].liczbaGraczy>0){
            msg+="p"+to_string(i)+"g"+to_string(pokoje[i].liczbaGraczy);
        }
    }
    char tab[msg.length()+1];
    strcpy(tab,msg.c_str());
    write(usr,tab,sizeof(tab));
}

void Poczekalnia::wyborPokoju(int usr,int wyb){
    if(pokoje[wyb].liczbaGraczy < MAXGRACZY && pokoje[wyb].runda==0){
        //
        pokoje[wyb].liczbaGraczy++;
        gracz.zmienPozycjeGracza(usr,'g',wyb);
        //
        string msg = "rm"+to_string(wyb);
        char tab[msg.length()+1];
        strcpy(tab,msg.c_str());
        write(usr,tab,sizeof(tab));
    } else {
        write(usr,"rb",2);
    }
}

void Poczekalnia::nowyPokoj(int usr){
    int wyb=0;
    while(wyb<ILEPOKOI){
        if(pokoje[wyb].liczbaGraczy == 0){
            wyborPokoju(usr,wyb);
            return;
        }
        wyb++;
    }
    write(usr,"rd",2);
}

void Poczekalnia::actionManager(int usr, char* command, int size){
    if(size>=3){
        string komenda = {command[0],command[1],command[2]};
        if(komenda == "nwr"){
            nowyPokoj(usr);
        } else if(komenda == "gib"){
            podajPokoje(usr);
        } else if(komenda == "chs"){
            //unikaj nie-numerow (teraz nie implementuje) i pustych wartosci
            string s = command;
            s.erase(0,3);
            int wyb = stoi(s);
            wyborPokoju(usr,wyb);
        }
    }
}

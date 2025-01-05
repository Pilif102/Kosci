#include "poczekalnia.h"

using namespace std;

static PlayerManager gracz;
static GameManager partia;

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
        gracz.zmienPozycjeGracza(usr,'g',wyb);
        Partia* pokoj = pokoje+wyb;
        partia.dodajGracza(usr,pokoj);
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
            //gra przygotowanie
            pokoje[wyb]={};
            wyborPokoju(usr,wyb);
            return;
        }
        wyb++;
    }
    write(usr,"rd",2);
}

Partia* Poczekalnia::zwrocPokoj(int usr){
    Partia* ptr = pokoje+gracz.podajPokojGracza(usr);
    return ptr;
}

void Poczekalnia::actionManager(int usr, char* command, int size){
    if(size>=3){
        string komenda = {command[0],command[1],command[2]};
        if(komenda == "new"){
            nowyPokoj(usr);
        } else if(komenda == "gib"){
            podajPokoje(usr);
        } else if(komenda == "chs"){
            //unikaj nie-numerow (teraz nie implementuje) i pustych wartosci
            string s = command;
            s.erase(0,3);
            int wyb = stoi(s);
            wyborPokoju(usr,wyb);
        } else if(komenda == "ext"){
            cout << "gracz sie rozlaczyl" << endl;
            gracz.usunGracza(usr);
            shutdown(usr,SHUT_RDWR);
            close(usr);
            return;
        }
    }
}

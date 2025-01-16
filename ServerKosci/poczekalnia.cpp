#include "poczekalnia.h"

using namespace std;

static PlayerManager gracz;
static GameManager partia;

Poczekalnia::Poczekalnia() {}

Partia Poczekalnia::pokoje[ILEPOKOI];

void Poczekalnia::podajPokoje(int usr){
    string msg="pok";
    for(int i=0;i<ILEPOKOI;i++){
        if(pokoje[i].liczbaGraczy>0 && pokoje[i].runda==0){
            msg+="p"+to_string(i)+"g"+to_string(pokoje[i].liczbaGraczy);
        }
    }
    msg+=":";
    char tab[msg.length()];
    strcpy(tab,msg.c_str());
    write(usr,tab,sizeof(tab));
}

void Poczekalnia::wyborPokoju(int usr,int wyb){
    if(pokoje[wyb].liczbaGraczy < MAXGRACZY && pokoje[wyb].runda==0){
        Partia* pokoj = pokoje+wyb;
        string msg = "rom"+to_string(wyb)+"ply"+to_string(pokoj->liczbaGraczy)+":";
        char tab[msg.length()];
        strcpy(tab,msg.c_str());
        write(usr,tab,sizeof(tab));
        gracz.zmienPozycjeGracza(usr,'g',wyb);
        partia.dodajGracza(usr,pokoj);
    } else {
        write(usr,"rbd:",4);
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
    write(usr,"nrm:",4);
}

Partia* Poczekalnia::zwrocPokoj(int usr){
    Partia* ptr = pokoje+gracz.podajPokojGracza(usr);
    return ptr;
}

void Poczekalnia::actionManager(int usr, string s){
    string komenda = s.string::substr(0,3);
    cout << komenda << endl;
    cout << usr << endl;
    if(komenda == "new" && gracz.zwrocNick(usr).string::compare("")!=0){
        cout << usr << endl;
        nowyPokoj(usr);
    } else if(komenda == "gib"){
        podajPokoje(usr);
    } else if(komenda == "chs" && gracz.zwrocNick(usr).string::compare("")!=0){
        //unikaj nie-numerow (teraz nie implementuje) i pustych wartosci
        s.erase(0,3);
        if(!s.empty() && find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
            int wyb = stoi(s);
            wyborPokoju(usr,wyb);
        }
    } else if(komenda == "nnc"){
        s.erase(0,3);
        cout << s <<endl;
        gracz.dajNick(usr,s);
        cout << "nick" <<endl;
    } else if(komenda == "ext"){
        cout << "gracz sie rozlaczyl" << endl;
        gracz.usunGracza(usr);
        shutdown(usr,SHUT_RDWR);
        close(usr);
        return;
    }

}

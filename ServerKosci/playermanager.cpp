#include "playermanager.h"

using namespace std;

PlayerManager::PlayerManager() {}

Gracz PlayerManager::gracze[MAXGRACZY*ILEPOKOI];

int PlayerManager::graczId(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            return i;
        }
    }
    return -1;
}

void PlayerManager::przygotujGracza(int usr){
    if(int i = graczId(-1);i != -1){
        gracze[i].id = usr;
    }
}

void PlayerManager::zmienPozycjeGracza(int usr,char pozycja,int num){
    if(int i = graczId(usr);i != -1){
        gracze[i].pozycja = pozycja;
        if(num != -1){
            gracze[i].numpokoju = num;
        }
    }
}

char PlayerManager::podajPozycjeGracza(int usr){
    if(int i = graczId(usr);i != -1){
        return gracze[i].pozycja;
    }
    return 'l';
}

int PlayerManager::podajPokojGracza(int usr){
    if(int i = graczId(usr);i != -1){
        return gracze[i].numpokoju;
    }
    return -1;
}

string PlayerManager::zwrocNick(int usr){
    if(int i = graczId(usr);i != -1){
        return gracze[i].nick;
    }
    return "dziwny_gracz";
}

void PlayerManager::dajNick(int usr, string nick){ //przy dołączaniu do pokoju
    if(nick.string::length()<3){
        write(usr,"bnc:",4);
        return;
    }
    if(nick.string::length()>=20) nick = nick.string::substr(0,20);
    for(int i=0;i<MAXGRACZY*ILEPOKOI;i++){
        if(nick.string::compare(gracze[i].nick)==0){
            write(usr,"unc:",4);
            return;
        }
    }
    if(int i = graczId(usr);i != -1){
        write(usr,"nst:",4);
        gracze[i].nick = nick;
        return;
    }
    write(usr,"bnc:",4);
}

void PlayerManager::usunGracza(int usr){
    if(int i = graczId(usr);i != -1){
        gracze[i] = {};
        shutdown(usr,SHUT_RDWR);
        close(usr);
    }
}

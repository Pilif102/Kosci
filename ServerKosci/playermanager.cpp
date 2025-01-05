#include "playermanager.h"

using namespace std;

PlayerManager::PlayerManager() {}

Gracz PlayerManager::gracze[MAXGRACZY*ILEPOKOI];

void PlayerManager::przygotujGracza(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == -1){
            cout << i << endl;
            gracze[i].id = usr;
            cout << gracze[i].id << endl;
            break;
        }
    }
}

void PlayerManager::zmienPozycjeGracza(int usr,char pozycja,int num){
    cout << gracze[0].id << endl;
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            gracze[i].pozycja = pozycja;
            if(num != -1){
                gracze[i].numpokoju = num;
            }
            break;
        }
    }
}

char PlayerManager::podajPozycjeGracza(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            return gracze[i].pozycja;
        }
    }
    return 'l';
}

int PlayerManager::podajPokojGracza(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            return gracze[i].numpokoju;
        }
    }
    return -1;
}

string PlayerManager::zwrocNick(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            return gracze[i].nick;
        }
    }
    return NULL;
}

void PlayerManager::dajNick(int usr, string nick){ //przy dołączaniu do pokoju
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            gracze[i].nick = nick;
            break;
        }
    }
}

void PlayerManager::usunGracza(int usr){
    for(int i = 0;i<MAXGRACZY*ILEPOKOI;i++){
        if(gracze[i].id == usr){
            gracze[i] = {};
            break;
        }
    }
}

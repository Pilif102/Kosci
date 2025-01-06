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
        cout << i << endl;
        gracze[i].id = usr;
        cout << gracze[i].id << endl;
    }
}

void PlayerManager::zmienPozycjeGracza(int usr,char pozycja,int num){
    cout << gracze[0].id << endl;
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
    if(int i = graczId(usr);i != -1){
        gracze[i].nick = nick;
    }
}

void PlayerManager::usunGracza(int usr){
    if(int i = graczId(usr);i != -1){
        gracze[i] = {};
        shutdown(usr,SHUT_RDWR);
        close(usr);
    }
}

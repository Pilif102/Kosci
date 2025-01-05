#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "struktury.h"

class PlayerManager
{
public:
    PlayerManager();
    static Gracz gracze[MAXGRACZY*ILEPOKOI];
    int graczId(int usr);
    void przygotujGracza(int usr);
    void zmienPozycjeGracza(int usr,char pozycja,int num = -1);
    char podajPozycjeGracza(int usr);
    int podajPokojGracza(int usr);
    std::string zwrocNick(int usr);
    void dajNick(int usr, std::string nick); //przy dołączaniu do pokoju
    void usunGracza(int usr);
};

#endif // PLAYERMANAGER_H

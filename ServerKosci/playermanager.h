#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "struktury.h"

class PlayerManager
{
public:
    PlayerManager();

    void przygotujGracza(int usr);
    void dajNick(int usr); //przy dołączaniu do pokoju
    void usunGracza(int usr);
};

#endif // PLAYERMANAGER_H

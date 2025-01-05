#ifndef POCZEKALNIA_H
#define POCZEKALNIA_H

#include "struktury.h"
#include "playermanager.h"

class Poczekalnia
{
public:
    Poczekalnia();
    static Partia pokoje[ILEPOKOI];
    void podajPokoje(int usr);
    void wyborPokoju(int usr,int wyb);
    void nowyPokoj(int usr);
    void actionManager(int usr,char* command, int size);
};

#endif // POCZEKALNIA_H

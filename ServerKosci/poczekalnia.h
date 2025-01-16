#ifndef POCZEKALNIA_H
#define POCZEKALNIA_H

#include "struktury.h"
#include "playermanager.h"
#include "gamemanager.h"
#include <string>

class Poczekalnia
{
public:
    Poczekalnia();
    static Partia pokoje[ILEPOKOI];
    void podajPokoje(int usr);
    void wyborPokoju(int usr,int wyb);
    void nowyPokoj(int usr);
    Partia* zwrocPokoj(int usr);

    void actionManager(int usr,std::string s);
};

#endif // POCZEKALNIA_H

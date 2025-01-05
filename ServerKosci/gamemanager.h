#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "struktury.h"
#include "playermanager.h"

class GameManager
{
public:
    GameManager();

    int graczId(int usr,Partia* gra);
    int rollDie();
    std::string rollDice(int Number,int arr[]);
    void reroll(Partia* gra);
    void endPlayerTurn(int usr);
    void wezKosc(int usr,int kosc);
    void koniecGry();//liczenie punktów
    void dodajGracza(int usr,Partia* gra);
    void przygotowanie(int usr);
    void runda(Partia* gra);//przebieg rundy
    void refactor(int usr);
    void actionManager(int usr,char* command, int size, Partia* gra);

};

#endif // GAMEMANAGER_H

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "struktury.h"
#include "playermanager.h"
#include "pointscount.h"

class GameManager
{
public:
    GameManager();
    int graczId(int usr,Partia* gra);
    int rollDie();
    std::string rollDice(int Number,int arr[]);
    std::string reroll(Partia* gra);
    void endPlayerTurn(int usr);
    void wezKosc(int usr,int kosc);
    void koniecGry(Partia* gra);//liczenie punktów
    void dodajGracza(int usr,Partia* gra);
    void przygotowanie(int usr);
    void runda(Partia* gra);//przebieg rundy
    void refactor(int usr,Partia* gra);
    void actionManager(int usr,std::string s, Partia* gra);
    void punktyGra(int usr,int pid);
    void zmienOpcje(Partia* gra,std::string dane);
    void timerPocz(Partia* gra,int czas);
    void timerRunda(Partia* gra,int czas);
    void timerPunktowanie(Partia* gra,int czas);
    void timerRoll(Partia* gra,int usr,std::string msg);
};

#endif // GAMEMANAGER_H

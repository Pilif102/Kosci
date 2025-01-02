#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "struktury.h"

class GameManager
{
public:
    GameManager();

    int rollDie();
    std::string rollDice(int Number,int arr[]);
    void koniecGry();//liczenie punktów
    void przygotowanie();
    void runda();//przebieg rundy
    void gra(Partia partia); //tworzona przy stworzeniu pokoju

};

#endif // GAMEMANAGER_H

#include "gamemanager.h"

using namespace std;

GameManager::GameManager() {}

int GameManager::rollDie(){
    return rand()%6+1;
}

string GameManager::rollDice(int Number,int arr[]){
    string res="";
    for(int i=0;i<Number*5;i++){
        arr[i]=rollDie();
        res+=to_string(arr[i])+",";
    }
    return res;
}

void GameManager::koniecGry(){
    //liczenie punktów
}

void GameManager::przygotowanie(){
    bool gotowosc[MAXGRACZY]={};
    //czekaj

}

void GameManager::runda(){
    //przebieg rundy
    //rzuty

    //przerzut

    //punkty
}

void GameManager::gra(Partia partia){ //tworzona przy stworzeniu pokoju
    if(partia.runda == 0){
        przygotowanie();
    } else if (partia.runda <= partia.limitRund){
        runda();
    } else{
        koniecGry();
    }
}

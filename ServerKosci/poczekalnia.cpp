#include "poczekalnia.h"

#include <string.h>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <thread>


Poczekalnia::Poczekalnia() {
}


// Gracz gracze[ILEPOKOI*MAXGRACZY];

void Poczekalnia::podajPokoje(int usr){
    std::string msg="";
    for(int i=0;i<ILEPOKOI;i++){
        if(pokoje[i].liczbaGraczy>0){
            msg+="p"+std::to_string(i)+"g"+std::to_string(pokoje[i].liczbaGraczy);
        }
    }
    char tab[msg.length()+1];
    strcpy(tab,msg.c_str());
    write(usr,tab,sizeof(tab));
}

void Poczekalnia::wyborPokoju(int usr,int wyb){
    if(pokoje[wyb].liczbaGraczy < MAXGRACZY && pokoje[wyb].runda==0){
        std::string msg = "rm"+std::to_string(wyb);
        char tab[msg.length()+1];
        strcpy(tab,msg.c_str());
        write(usr,tab,sizeof(tab));
    } else {
        write(usr,"rb",2);
    }
}

void Poczekalnia::nowyPokoj(int usr){
    int wyb=0;
    while(wyb<ILEPOKOI){
        if(pokoje[wyb].liczbaGraczy == 0){
            wyborPokoju(usr,wyb);
            return;
        }
        wyb++;
    }
    write(usr,"rd",2);
}

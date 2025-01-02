#include "poczekalnia.h"

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

#define MAXBUF 255
using namespace std;

struct Gracz{
    //struct in_addr ipik;
    string nick; //mozna ze nick do 10 znakow
    int id;
    char pozycja;
    int numpokoju;
};


int rollDie(){
    return rand()%6+1;
}

string rollDice(int Number,int arr[]){
    string res="";
    for(int i=0;i<Number*5;i++){
        arr[i]=rollDie();
        res+=to_string(arr[i])+",";
    }
    return res;
}

void koniecGry(){
    //liczenie punktów
}

void przygotowanie(){
    bool gotowosc[MAXGRACZY]={};
    //czekaj

}

void runda(){
    //przebieg rundy
    //rzuty

    //przerzut

    //punkty
}

void gra(Partia partia){ //tworzona przy stworzeniu pokoju
    if(partia.runda == 0){
        przygotowanie();
    } else if (partia.runda <= partia.limitRund){
        runda();
    } else{
        koniecGry();
    }
}

void responseHandler(){

}


void przygotujGracza(int usr){

}

void dajNick(int usr){ //przy dołączaniu do pokoju

}

void usunGracza(int usr){

}

int main()
{
    Poczekalnia pocz;
    pocz.pokoje[0].liczbaGraczy=2;

    srand(time(NULL));


    int fd = socket(PF_INET,SOCK_STREAM,0);
    sockaddr_in addr{AF_INET,htons(9999),{htonl(INADDR_ANY) }};
    const int one = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
    bind(fd,(sockaddr*)&addr,sizeof(addr));
    listen(fd,1);

    sockaddr_in klient;
    socklen_t kllen = sizeof(klient);
    int c1;

    char buff[MAXBUF];
    int size;
    c1=accept(fd,(sockaddr*)&klient,&kllen);

    while(1){
        cout << c1 << endl;
        size = read(c1,buff,MAXBUF);
        switch(buff[0]){ //switch dla czytelnosci
        case 'r': //sygnały związane z poczekalnia
            //if(gracz not in poczekalnia)
            switch(buff[1]){
            case 'n':
                pocz.nowyPokoj(c1);
                break;
            case 'r':
                pocz.podajPokoje(c1);
                break;
            case 'j':
                //unikaj nie-numerow (teraz nie implementuje) i pustych wartosci
                string s = buff;
                s.erase(0,2);
                int wyb = stoi(s);
                pocz.wyborPokoju(c1,wyb);
                break;
            }
            break;
        case 'g': //komendy dla gry
            //if w grze
            switch(buff[2]){
            case 's':
                //zglos gotowosc
                break;
            case 'r':
                //przerzuc kosci
                break;
            case 'c':
                //zablokowac kosc o danym id
                break;
            case 'p':
                //wybierz rubryke punktacji (id)
                break;
            // case 'z':
            //     //zmienione zasady (może, może nie)
            //     break;
            case 'q':
                //wyjdz z gry
                break;
            }

        case 'q':
            shutdown(c1,SHUT_RDWR);
            close(c1);
            break;
        default:
            write(c1,"br",2);
        }
        if(buff[0]=='q'){
            break;
        }
        write(c1,"\n",1);
    }
    shutdown(fd,SHUT_RDWR);
    close(fd);
    return 0;

}

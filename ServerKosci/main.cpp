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

using namespace std;

struct Gracz{
    struct in_addr ipik;
    string nick;
};

struct Partia{
    int liczbaGraczy = 0;
    int idGraczy[4]={};
    int kosci[20]={};
    int wybrane[20]={};
    int runda=0;
    int limitRund = 13;
};

Partia pokoje[10];
Gracz gracze[40];

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

void gra(){
    if(runda == 0){

    }
}

void podajPokoje(){

}

void wyborPokoju(){

}

int main()
{
    cout << pokoje[0].runda << endl;
    return 0;

    srand(time(NULL));

    int fd = socket(PF_INET,SOCK_STREAM,0);
    sockaddr_in addr{AF_INET,htons(9999),{htonl(INADDR_ANY)}};
    const int one = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
    bind(fd,(sockaddr*)&addr,sizeof(addr));
    listen(fd,1);
    sockaddr_in klient;
    socklen_t kllen = sizeof(klient);
    int c1;
    int arr[20];
    while((c1=accept(fd,(sockaddr*)&klient,&kllen))){

        string res = rollDice(4,arr);
        char tab[res.length()+1];
        cout << res.length()+1 << endl;
        cout << sizeof(tab) << endl;
        strcpy(tab,res.c_str());
        write(c1,tab,sizeof(tab));

        shutdown(c1,SHUT_RDWR);
        close(c1);
    }
    shutdown(fd,SHUT_RDWR);
    close(fd);
    return 0;
}

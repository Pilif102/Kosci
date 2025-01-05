#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <netdb.h> //addrinfo
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <thread>

//main
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>

#define MAXGRACZY 4
#define ILEPOKOI 10

struct Partia{
    int liczbaGraczy = 0;
    int idGraczy[MAXGRACZY]={};
    int kosci[MAXGRACZY*5]={};
    int wybrane[MAXGRACZY*5]={};
    int runda=0;
    int limitRund = 17;
};

struct Gracz{
    //struct in_addr ipik;
    std::string nick = "nowy_gracz"; //mozna ze nick do 10 znakow
    int id = -1;
    char pozycja = 'r';
    int numpokoju = -1;
};

#endif // STRUKTURY_H

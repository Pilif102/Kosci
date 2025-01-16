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
#include <bits/stdc++.h>

#define MAXGRACZY 4
#define ILEPOKOI 10

struct Partia{
    int liczbaGraczy = 0;
    int idGraczy[MAXGRACZY]={};
    int kosci[MAXGRACZY*5]={};
    int wybrane[MAXGRACZY*5];
    int runda=0;
    int limitRund = 1;
    int rerolls=2;
    int MaxRolls=2;
    int LimitGraczy=4;
    bool ready[4] = {};
    bool punktowanie = false;
    int punkty[17*MAXGRACZY]={};
};

struct Gracz{
    //struct in_addr ipik;
    std::string nick = ""; //mozna ze nick do 20 znakow
    int id = -1;
    char pozycja = 'r';
    int numpokoju = -1;
};

#endif // STRUKTURY_H

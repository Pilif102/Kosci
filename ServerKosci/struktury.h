#ifndef STRUKTURY_H
#define STRUKTURY_H

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

#endif // STRUKTURY_H

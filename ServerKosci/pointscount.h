#ifndef POINTSCOUNT_H
#define POINTSCOUNT_H
#include <bits/stdc++.h>

class PointsCount
{
public:
    PointsCount();
    int cyfry(int kosci[5],int wyb);
    int szansa(int kosci[5]);
    int parzystosci(int kosci[5],bool parz = true);
    int strity(int kosci[5],bool duzy=false);
    int identyczne(int kosci[5],int wyb);
    int full(int kosci[5]);
    int dwiePary(int kosci[5]);
    int punktyFinalne(int punktyGracza[17]);


};

#endif // POINTSCOUNT_H

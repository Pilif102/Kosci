#include "pointscount.h"

using namespace std;

PointsCount::PointsCount() {}

int PointsCount::cyfry(int kosci[5],int wyb){
    int ile = count(kosci,kosci+5,wyb);
    return wyb*(ile-3);
}

int PointsCount::szansa(int kosci[5]){
    return accumulate(kosci,kosci+5,0);
}

int PointsCount::parzystosci(int kosci[5],bool parz){
    int suma = 0;
    int ile = 0;
    for(int i=0;i<5;i++){
        ile = kosci[i]%2;
    }
    if((parz && ile==5) || (parz && ile==0)){
        suma = accumulate(kosci,kosci+5,0);
    }
    return suma;
}

int PointsCount::strity(int kosci[5],bool duzy){
    sort(kosci,kosci+5);
    int malyS[] = {1,2,3,4,5};
    int duzyS[] = {2,3,4,5,6};
    int* strit = malyS;
    int* strit2 = duzyS;
    if(duzy) strit = duzyS;
    for(int i=0;i<5;i++){
        if(kosci[i]!=strit[i]){
            return 0;
        }
    }
    if(duzy) return 20;
    return 15;
}

int PointsCount::identyczne(int kosci[5],int wyb){
    int bonus = 0;
    int suma = 0;
    int ile=0;
    for(int i=6;i>=1;i--){
        ile = count(kosci,kosci+5,i);
        if(ile==wyb){
            suma=ile*wyb;
            break;
        }
    }
    if(suma > 0){
        if(wyb==4){
            bonus=20;
        }else if(wyb==5){
            bonus=50;
        }
    }
    return suma+bonus;
}

int PointsCount::full(int kosci[5]){
    int para = identyczne(kosci,2);
    int trojka = identyczne(kosci,3);
    if(para > 0 && trojka > 0) return para+trojka+10;
    return 0;
}

int PointsCount::dwiePary(int kosci[5]){
    int bonus = 0;
    int suma = 0;
    int ile=0;
    int wyb = 0;
    for(int i=6;i>=1;i--){
        ile = count(kosci,kosci+5,i);
        if(ile==wyb){
            suma+=ile*wyb;
            wyb++;
            if(wyb==2) break;
        }
    }
    return suma+bonus;
}



int PointsCount::punktyFinalne(int punktyGracza[17]){
    int punkty=0;
    int szkolka = 0;
    for(int i=0;i<6;i++){
        szkolka = punktyGracza[i]-3;
    }
    if(szkolka > 10){
        punkty += 30;
    } else if(szkolka <= 0) {
        punkty -= 30;
    }
    for(int i=6;i<17;i++){
        punkty+=punktyGracza[i];
    }
    return punkty;
}

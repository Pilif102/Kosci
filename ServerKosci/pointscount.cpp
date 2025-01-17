#include "pointscount.h"

using namespace std;

PointsCount::PointsCount() {}

int cyfry(int kosci[5],int wyb){
    int ile = count(kosci,kosci+5,wyb);
    return wyb*(ile-3);
}

int szansa(int kosci[5]){
    return accumulate(kosci,kosci+5,0);
}

int parzystosci(int kosci[5],bool parz){
    int suma = 0;
    int ile = 0;
    for(int i=0;i<5;i++){
        ile += kosci[i]%2;
        suma+=kosci[i];
    }
    if((!parz && ile==5) || (parz && ile==0)){
        return suma;
    }
    return 0;
}

int strity(int kosci[5],bool duzy){
    sort(kosci,kosci+5);
    int malyS[] = {1,2,3,4,5};
    int duzyS[] = {2,3,4,5,6};
    int* strit = malyS;
    if(duzy) strit = duzyS;
    for(int i=0;i<5;i++){
        if(kosci[i]!=strit[i]){
            return 0;
        }
    }
    if(duzy) return 20;
    return 15;
}

int identyczne(int kosci[5],int wyb){
    sort(kosci,kosci+5);
    int bonus = 0;
    int suma = 0;
    int ile=0;
    for(int i=6;i>=1;i--){
        ile = count(kosci,kosci+5,i);
        if(ile>=wyb){
            suma=wyb*i;
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

int full(int kosci[5]){
    sort(kosci,kosci+5);
    int suma = 0;
    bool niebylo = true;
    int pop = 0;
    for(int i=0;i<5;i++){
        if(pop!=0){
            if(pop!=kosci[i]){
                if((i==2 || i==3) && niebylo){
                    niebylo=false;
                } else {
                    return 0;
                }
            }
        }
        pop = kosci[i];
        suma+=kosci[i];
    }
    return suma+10;
}

int dwiePary(int kosci[5]){
    sort(kosci,kosci+5);
    int bonus = 0;
    int suma = 0;
    int ile=0;
    int wyb = 0;
    for(int i=6;i>=1;i--){
        ile = count(kosci,kosci+5,i);
        if(ile>=2){
            suma+=2*i;
            wyb++;
            if(wyb==2) break;
        }
    }
    if(wyb!=2) return 0;
    return suma;
}



int PointsCount::punktyFinalne(int punktyGracza[17]){
    int punkty=0;
    int szkolka = 0;
    for(int i=0;i<6;i++){
        cout << "gracz" << punktyGracza[i] << endl;
        szkolka += punktyGracza[i];
    }
    if(szkolka > 10){
        punkty += 30;
    } else if(szkolka <= 0) {
        punkty -= 30;
    }
    cout << punkty << endl;
    for(int i=6;i<17;i++){
        punkty+=punktyGracza[i];
        cout <<"gracz" << punktyGracza[i] << endl;
        cout <<"pkt" << punkty << endl;
    }
    return punkty;
}

int PointsCount::liczPunkty(int kosci[5],int wybPunkt){
    if(wybPunkt<6 && wybPunkt >=0){ //szkolka
        return cyfry(kosci,wybPunkt+1);
    }else if(wybPunkt==6){ //para
        return identyczne(kosci,2);
    }else if(wybPunkt==7){ //dwie pary
        return dwiePary(kosci);
    }else if(wybPunkt==8 || wybPunkt==9){ //trojka i kareta
        return identyczne(kosci,wybPunkt-5);
    }else if(wybPunkt==10 || wybPunkt==11){ //nieparzyste i parzyste
        return parzystosci(kosci,wybPunkt-10);
    }else if(wybPunkt==12 || wybPunkt==13){ //maly i duzy strit
        return strity(kosci,wybPunkt-12);
    }else if(wybPunkt==14){
        return full(kosci);
    }else if(wybPunkt==15){
        return identyczne(kosci,5);
    }else if(wybPunkt==16){
        return szansa(kosci);
    } else return -1;
}

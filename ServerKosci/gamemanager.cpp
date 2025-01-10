#include "gamemanager.h"

using namespace std;

PlayerManager gracz;
Partia* partia;
PointsCount punkty;

//thread gry[ILEPOKOI];

GameManager::GameManager() {}

void SendToAll(Partia* gra, string msg){
    msg+=":";
    for(int i=0;i<gra->liczbaGraczy;i++){
        char tab[msg.length()];
        strcpy(tab,msg.c_str());
        write(gra->idGraczy[i],tab,sizeof(tab));
    }
}

void SendKosciToAll(Partia* gra, int mes[], string msg=""){
    for(int i=0; i<gra->liczbaGraczy*5;i++){
        msg+=to_string(mes[i]);
        msg+=",";
    }
    SendToAll(gra,msg);
}

int GameManager::graczId(int usr,Partia* gra){
    for(int i=0;i<MAXGRACZY;i++){
        if(gra->idGraczy[i]==usr){
            return i;
        }
    }
    return -1;
}

int GameManager::rollDie(){
    return rand()%6+1;
}

string GameManager::rollDice(int Number,int arr[]){
    string res="";
    for(int i=0;i<Number*5;i++){
        arr[i]=rollDie();
        res+=to_string(arr[i]);
    }
    return res;
}

void GameManager::wezKosc(int usr,int kosc){
    int wolne = -1;
    int id = graczId(usr,partia);
    if(id!=-1){
        for(int i=id*5;i<(id*5)+5;i++){
            if(partia->wybrane[i]==-1){
                if(wolne==-1){
                    wolne=i;
                }
            }else{
                if(partia->wybrane[i]==kosc){ //usuniecie wybranej kosci
                    partia->wybrane[i]=-1;
                    SendToAll(partia,"got"+to_string(kosc)+"g"+to_string(id));
                    //SendKosciToAll(partia,partia->wybrane,"wyb");
                    return;
                }
            }
        }
        for(int i=0;i<partia->liczbaGraczy*5;i++){
            if(partia->wybrane[i]==kosc){ //kosc w posiadaniu innego gracza
                write(usr,"zaj:",4);
                return;
            }
        }
        partia->wybrane[wolne]=kosc;
        //write done
        SendKosciToAll(partia,partia->wybrane,"wyb");
    }
}

void GameManager::koniecGry(Partia* gra){
    //liczenie punktów
    int max=0;
    int wygrany=0;

    for(int i=0;i<gra->liczbaGraczy;i++){
        int wynik=0;
        for(int j=0;j<ILEWIERSZY;j++){
            wynik+=gra->punkty[(17*i)+j];
        }
        SendToAll(gra,"fin"+to_string(wynik)+"usr"+to_string(i));
        if(wynik > max){
            max=wynik;
            wygrany=i;
        }
    }
    SendToAll(gra,"win"+to_string(wygrany));
    gra->runda=0;
    fill(gra->ready,gra->ready+MAXGRACZY,0);
}

void GameManager::dodajGracza(int usr,Partia* gra){
    //dodanie gracza
    gra -> liczbaGraczy++;
    int i = graczId(0,gra);
    if(i!=-1){
        gra->idGraczy[i]=usr;
        gra->ready[i]=false;
    }
    SendToAll(gra,"nic"+to_string(i)+","+gracz.zwrocNick(usr));
    for(int j=0;j<gra->liczbaGraczy;j++){
        if(i!=j){
            string msg = "nic"+to_string(j)+","+gracz.zwrocNick(gra->idGraczy[j])+":";
            char tab[msg.length()];
            strcpy(tab,msg.c_str());
            write(usr,tab,sizeof(tab));
        }
    }

    for(int j=0;j<MAXGRACZY;j++){
        cout << "nic"+to_string(j)+","+gracz.zwrocNick(gra->idGraczy[j]) << endl;
    }

}

void GameManager::przygotowanie(int usr){
    //czekaj
    //dodac informacje dla innych graczy ze jest gotowosc
    if(int i = graczId(usr,partia);i!=-1){
        partia->ready[i]=true;
        SendToAll(partia,"prd"+to_string(i));
    }
    if(partia->liczbaGraczy>1){
        int suma=0;
        for(int i=0;i<MAXGRACZY;i++){
            if(partia->ready[i]){
                suma++;
            }
        }
        if(suma == partia->liczbaGraczy){
            SendToAll(partia,"beg");
            //mozna dodac timer
            //thread nowy(runda,partia); //wrzucic do thread
            partia->runda++;
            runda(partia);
        }
    }
}

void GameManager::runda(Partia* gra){
    //przebieg rundy
    fill(gra->kosci,gra->kosci+MAXGRACZY*5,0);
    fill(gra->wybrane,gra->wybrane+MAXGRACZY*5,-1);
    gra->rerolls=3;
    fill(gra->ready,gra->ready+MAXGRACZY,0);
    SendToAll(gra,"rnd"+to_string(gra->runda));
    //rzuty
    SendToAll(gra,"kos"+rollDice(gra->liczbaGraczy,gra->kosci));
}

void GameManager::reroll(Partia* gra){
    string msg="";
    for(int i=0;i<gra->liczbaGraczy*5;i++){
        bool znalezione=false;
        for(int j=0;j<gra->liczbaGraczy*5;j++){
            if(i==gra->wybrane[j]){
                znalezione=true;
                break;
            }
        }
        if(znalezione==false){
            gra->kosci[i]=rollDie();
            gra->rerolls--;
        }
    }

    for(int i=0;i<gra->liczbaGraczy*5;i++){
        msg+=to_string(gra->kosci[i]);
    }
    SendToAll(gra,"rrl"+to_string(gra->rerolls)+":");
    SendToAll(gra,"kos"+msg+":");
    cout << msg << endl;
}

void GameManager::refactor(int usr,Partia* gra){
    if(int i = graczId(usr,gra);i!=-1){ //niech idzie z pokoju
        if(gra->liczbaGraczy==1){
            *gra = {};
            return;
        }
        //wyslij informacje do innych graczy, zmien kolejnosc graczy zeby było ich mało
        SendToAll(gra,"qit"+to_string(i));
        for(int j=i;j<gra->liczbaGraczy-1;j++){
            gra->idGraczy[j]=gra->idGraczy[j+1]; /*else {
                SendToAll(gra,"nic"+to_string(j-1)+","+gracz.zwrocNick(gra->idGraczy[j-1]));
            }*/
        }
        gra->liczbaGraczy--;
        gra->idGraczy[gra->liczbaGraczy]=0;

    }
    if(gra->liczbaGraczy==1 && gra->runda>0){
        koniecGry(gra);
    }else
    //zrestartuj runde ktora aktualnie jest
    if( gra->runda > 0 && gra->punktowanie==false) runda(gra);
}
void GameManager::punktyGra(int usr,int pid){
    int gid = (graczId(usr,partia));
    int ksc[5];
    for(int i=0;i<5;i++){
        ksc[i]=partia->kosci[partia->wybrane[(gid*5)+i]];
    }
    int pkt = punkty.liczPunkty(ksc,pid);
    //dodaj do punktacji gracza
    partia->punkty[(gid*17)+pid]=pkt;
    SendToAll(partia,"pts"+to_string(pkt)+"usr"+to_string(gid));
    //dodac gotowosc, jesli gotowe to nowa runda chyba ze koniec
    partia->ready[gid]=true;
    for(int i=0;i<partia->liczbaGraczy;i++){
        if(partia->ready[i]==false){
            return;
        }
    }
    if(partia->runda==partia->limitRund){
        koniecGry(partia);
    }else{
        partia->runda++;
        runda(partia);
    }
}

void GameManager::endPlayerTurn(int usr){
    if(int i = graczId(usr,partia);i!=-1){
        for(int j=i*5;j<i*5+5;j++){
            if(partia->wybrane[j]==-1){
                return;
            }
        }
        partia->ready[i]=true;
        SendToAll(partia,"pdn"+to_string(i));

        if(partia->liczbaGraczy>1){
            int suma=0;
            for(int i=0;i<MAXGRACZY;i++){
                if(partia->ready[i]){
                    suma++;
                }
            }
            if(suma == partia->liczbaGraczy){
                //koniec tury, przejsc do punktowania
                SendToAll(partia,"t-e");
                partia->punktowanie=true;
                fill(partia->ready,partia->ready+MAXGRACZY,0);
            }
        }
    }
}

void GameManager::actionManager(int usr,char* command, int size,Partia* gra){
    if(size>=3){
        string komenda = {command[0],command[1],command[2]};
        partia = gra;
        if(komenda == "ext"){
            cout << "gracz sie rozlaczyl" << endl;
            refactor(usr,partia);
            gracz.usunGracza(usr);
        }else if(partia->runda == 0){
            if(komenda == "rdy"){
                //gotowosc
                przygotowanie(usr);
            } else if(komenda == "chg"){
                //zmienione zasady (może, może nie)
            }
        } else if (partia->runda <= partia->limitRund){
            if(partia->punktowanie==false){
                if(komenda == "rol"){
                    reroll(partia);
                } else if(komenda == "get"){
                    //dodaj kontrole bledow
                    string s = command;
                    s.erase(0,3);
                    int wyb = stoi(s);
                    wezKosc(usr,wyb);
                } else if(komenda == "rdy"){
                    //koniec,wszystko wybrane
                    endPlayerTurn(usr);
                }

                for(int i=0;i<gra->liczbaGraczy*5;i++){
                    cout << partia->kosci[i] << ",";
                }
                cout << endl;
                for(int i=0;i<partia->liczbaGraczy*5;i++){
                    cout << partia->wybrane[i] << ",";
                }
                cout << endl;
            }else {
                if(komenda == "ptn" && partia->ready[graczId(usr,partia)]){
                //wybierz rubryke punktacji (id)
                    cout << "punktacja" << endl;
                    string s = command;
                    s.erase(0,3);
                    int wyb = stoi(s);
                    punktyGra(usr,wyb);
                }
            }
        }

    }
}

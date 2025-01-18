#include "gamemanager.h"

using namespace std;

PlayerManager gracz;
Partia* partia;
PointsCount punkty;
bool timeout = false;
int przerolowany = -1;

//thread gry[ILEPOKOI];

GameManager::GameManager() {}

void SendToAll(Partia* gra, string msg){
    msg+=";";
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

void GameManager::timerPunktowanie(Partia* gra,int czas){
    int runda = gra->runda;
    int l = gra->liczbaGraczy;
    while(czas>0){
        if(gra->punktowanie && runda==gra->runda && l==gra->liczbaGraczy){
            SendToAll(gra,"rem"+to_string(czas));
            cout << czas << endl;
            this_thread::sleep_for(chrono::seconds(1));
            czas--;
        } else {
            return;
        }
    }
    timeout = true;
    //wyrzuc niegotowych i daj nastepna runde
    bool nieakt[MAXGRACZY]={};
    for(int i=0;i<gra->liczbaGraczy;i++){
        if(!gra->ready[i]){
            nieakt[i]=true;
        }
    }
    for(int i=gra->liczbaGraczy-1;i>=0;i--){
        if(nieakt[i]){
            int usr = gra->idGraczy[i];
            cout << "gracz wyrzucony" << endl;
            refactor(usr,gra);
            gracz.zmienPozycjeGracza(usr,'r');
            write(usr,"but;",4);
        }
    }
    timeout = false;
    gra->runda++;
    thread t([=] {timerPocz(gra,5);});
    t.detach();
}

void GameManager::timerRunda(Partia* gra,int czas){
    int runda = gra->runda;
    int l = gra->liczbaGraczy;
    while(czas>0){
        if(!gra->punktowanie && runda==gra->runda && l==gra->liczbaGraczy){
            SendToAll(gra,"rem"+to_string(czas));
            cout << czas << endl;
            this_thread::sleep_for(chrono::seconds(1));
            czas--;
        } else {
            return;
        }
    }
    timeout = true;
    //wyrzuc niegotowych i powtorz runde
    bool nieakt[MAXGRACZY]={};
    for(int i=0;i<gra->liczbaGraczy;i++){
        if(!gra->ready[i]){
            nieakt[i]=true;
        }
    }
    for(int i=gra->liczbaGraczy-1;i>=0;i--){
        if(nieakt[i]){
            int usr = gra->idGraczy[i];
            cout << "gracz wyrzucony" << endl;
            refactor(usr,gra);
            gracz.zmienPozycjeGracza(usr,'r');
            write(usr,"but;",4);
        }
    }
    timeout = false;
    thread t([=] {timerPocz(gra,5);});
    t.detach();
}

void GameManager::timerPocz(Partia* gra,int czas){
    int rnd = gra->runda;
    while(czas>0){
        if(gra->ready[0] && rnd==gra->runda){
            SendToAll(gra,"rem"+to_string(czas));
            cout << czas << endl;
            this_thread::sleep_for(chrono::seconds(1));
            czas--;
        } else {
            return;
        }
    }
    runda(gra);
}

void GameManager::timerRoll(Partia* gra,int usr,string msg){
    gra->rerolls--;
    SendToAll(gra,"rrl"+to_string(gra->rerolls));
    przerolowany = usr;
    this_thread::sleep_for(chrono::seconds(1));
    przerolowany = -1;
    reroll(partia);

}

int GameManager::graczId(int usr,Partia* gra){
    for(int i=0;i<MAXGRACZY;i++){
        if(gra->idGraczy[i]==usr){
            return i;
        }
    }
    return -1;
}
void GameManager::zmienOpcje(Partia* gra, string dane){
    int gracze = dane.find("g");
    int rundy = dane.find("r");
    int rolls = dane.find("p");
    if(gracze ==-1 || rundy ==-1|| rolls ==-1 || !(gracze<rundy<rolls))return;
    string s = dane.substr(gracze+1,rundy-gracze-1);
    cout << s << endl;
    if(!s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
        int wyb = stoi(s);
        if(wyb <= 4 || wyb >=2){
            gra->LimitGraczy = wyb;
        }
    }
    s = dane.substr(rundy+1,rolls-rundy-1);
    cout << s << endl;
    if(!s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
        int wyb = stoi(s);
        if(wyb <= 17 || wyb >=1){
            gra->limitRund = wyb;
        }
    }
    s = dane.substr(rolls+1,dane.length()-rolls-1);
    cout << s << endl;
    if(!s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
        int wyb = stoi(s);
        if(wyb <= 5 || wyb >=0){
            gra->MaxRolls = wyb;
        }
    }
    SendToAll(gra,"setg"+to_string(gra->LimitGraczy)+"r"+to_string(gra->limitRund)+"p"+to_string(gra->MaxRolls));
    fill(gra->ready,gra->ready+MAXGRACZY,0);
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
                    break;
                }
            }
        }
        if(wolne == -1) return;
        for(int i=0;i<partia->liczbaGraczy*5;i++){
            if(partia->wybrane[i]==kosc){ //kosc w posiadaniu innego gracza
                write(usr,"zaj;",4);
                return;
            }
        }
        partia->wybrane[wolne]=kosc;
        //write done
        SendToAll(partia,"got"+to_string(kosc)+"g"+to_string(id));
        if(wolne==(id*5)+4) endPlayerTurn(usr);
    }
}

void GameManager::koniecGry(Partia* gra){
    gra->punktowanie=false;
    //liczenie punktów
    int max=0;
    int wygrany=0;

    for(int i=0;i<gra->liczbaGraczy;i++){
        int pkt[17]={};
        for(int j=0;j<ILEWIERSZY;j++){
            pkt[j]=gra->punkty[(17*i)+j];
            cout << pkt[j] << endl;
        }
        int wynik = punkty.punktyFinalne(pkt);
        SendToAll(gra,"fin"+to_string(wynik)+"usr"+to_string(i));
        if(wynik > max){
            max=wynik;
            wygrany=i;
        }
    }
    SendToAll(gra,"win"+to_string(wygrany));
    gra->runda=0;
    fill(gra->ready,gra->ready+MAXGRACZY,0);
    fill(gra->kosci,gra->kosci+MAXGRACZY*5,0);
    fill(gra->wybrane,gra->wybrane+MAXGRACZY*5,0);
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
            string msg = "nic"+to_string(j)+","+gracz.zwrocNick(gra->idGraczy[j])+";";
            char tab[msg.length()];
            strcpy(tab,msg.c_str());
            write(usr,tab,sizeof(tab));
        } else {
            //napisz ustawienia gry
            string msg = "setg"+to_string(gra->LimitGraczy)+"r"+to_string(gra->limitRund)+"p"+to_string(gra->MaxRolls)+";";
            char tab[msg.length()];
            strcpy(tab,msg.c_str());
            write(usr,tab,sizeof(tab));
        }
    }


    for(int j=0;j<MAXGRACZY;j++){
        cout << "nic"+to_string(j)+","+gracz.zwrocNick(gra->idGraczy[j]) << endl;
    }
    fill(gra->ready,gra->ready+MAXGRACZY,0);

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
            fill(partia->punkty,partia->punkty+17,0);
            for(int j=0;j<partia->liczbaGraczy;j++){
                for(int i=0;i<6;i++){
                    int zero[5]={};
                    partia->punkty[17*j+i]=punkty.liczPunkty(zero,i);
                }
            }
            partia->runda++;
            thread t([=] {timerPocz(partia,5);});
            t.detach();
        }
    }
}

void GameManager::runda(Partia* gra){
    //przebieg rundy
    cout<< "round" <<gra->runda<<endl;
    gra->punktowanie=false;
    fill(gra->kosci,gra->kosci+MAXGRACZY*5,0);
    fill(gra->wybrane,gra->wybrane+MAXGRACZY*5,-1);
    gra->rerolls=2;
    fill(gra->ready,gra->ready+MAXGRACZY,0);
    SendToAll(gra,"rnd"+to_string(gra->runda));
    //rzuty
    SendToAll(gra,"kos"+rollDice(gra->liczbaGraczy,gra->kosci));
    thread t([=] { timerRunda(gra,30); });
    t.detach();
}

string GameManager::reroll(Partia* gra){
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
        }
    }

    for(int i=0;i<gra->liczbaGraczy*5;i++){
        msg+=to_string(gra->kosci[i]);
    }
    SendToAll(gra,"kos"+msg);
    cout << msg << endl;
    return msg;
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
                SendToAll(gra,"nic"+to_string(j-1)+","+gracz.zwrocNick(gra->idGraczy[j-1])); //teraz zalatwia klient
            }*/
        }
        gra->liczbaGraczy--;
        gra->idGraczy[gra->liczbaGraczy]=0;

    }
    if(gra->liczbaGraczy==1 && gra->runda>0){
        koniecGry(gra);
    }else
    //zrestartuj runde ktora aktualnie jest
        if( gra->runda > 0 && gra->punktowanie==false && !timeout){
            thread t([=] {timerPocz(gra,5);});
            t.detach();
        }
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
    if(pid > 5){
        SendToAll(partia,"pts"+to_string(pkt)+"usr"+to_string(gid));
    }
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
        thread t([=] {timerPocz(partia,5);});
        t.detach();
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
                //timer
                thread t([=] {timerPunktowanie(partia,30);});
                t.detach();
            }
        }
    }
}

void GameManager::actionManager(int usr,string s,Partia* gra){
    string komenda = s.string::substr(0,3);
    partia = gra;
    if(komenda == "ext"){
        cout << "gracz sie rozlaczyl" << endl;
        refactor(usr,partia);
        gracz.zmienPozycjeGracza(usr,'r');
        write(usr,"bck;",4);
    }else if(partia->runda == 0){
        if(komenda == "rdy"){
            //gotowosc
            przygotowanie(usr);
        } else if(komenda == "chg"){
            //zmienione zasady
            s.erase(0,3);
            if(!s.empty() && gra->idGraczy[0]==usr){
                zmienOpcje(gra,s);
            } else {
                write(usr,"brq;",4);
            }
        } else {
            write(usr,"brq;",4);
        }
    } else if (partia->runda <= partia->limitRund){
        if(partia->punktowanie==false && usr!=przerolowany){
            if(komenda == "rol" ){ //przerzuc kosci
                if(gra->rerolls<1) return;
                thread t([=] {timerRoll(gra,usr,"msg");});
                t.detach();
            } else if(komenda == "get"){ //wez kosc
                s.erase(0,3);
                if(!s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
                    int wyb = stoi(s);
                    if(wyb < gra->liczbaGraczy*5){
                        wezKosc(usr,wyb);
                    } else {
                        write(usr,"brq;",4);
                        return;
                    }
                } else {
                    write(usr,"brq;",4);
                    return;
                }
            } else {
                write(usr,"brq;",4);
                return;
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
            if(komenda == "ptn"){
            //wybierz rubryke punktacji (id)
                cout << "punktacja " << s << endl;
                s.erase(0,3);
                if(!s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end()){
                    int wyb = stoi(s);
                    if(wyb < 17){
                        punktyGra(usr,wyb);
                    }else {
                        write(usr,"brq;",4);
                    }
                } else {
                    write(usr,"brq;",4);
                }
            } else {
                write(usr,"brq;",4);
            }
        }
    }


}

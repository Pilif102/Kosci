#include "wybor.h"
#include "./ui_wybor.h"
#include "gra.h"

#include <QMessageBox>
bool powiadomienia=true;
bool first = true;
gra *nw;

wybor::wybor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wybor)
{
    ui->setupUi(this);
    nw = new gra();

    //server koneksje
    connect(ui->PushConnect, &QPushButton::clicked, this, &wybor::connectBtnHit);
    connect(ui->lineEditIP, &QLineEdit::returnPressed, ui->PushConnect, &QPushButton::click);

    //nick
    connect(ui->nickEdit, &QLineEdit::editingFinished, this, &wybor::sendNick);

    //odswiez pokoje
    connect(ui->refresh, &QPushButton::clicked, this,[=]() {sock->write("gib:");});

    //wyslij prosbe o nowy pokoj
    connect(ui->newRoom, &QPushButton::clicked, this,[=]() {sock->write("new:");});

    //dolacz do pokoju
    connect(ui->GameButton,&QPushButton::clicked, this, &wybor::connectRoom);
    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&wybor::connectRoom);
    connect(ui->listWidget,&QListWidget::itemClicked,this,[=]() {ui->GameButton->setEnabled("true");});

    //sprobuj sie polaczyc z domyślnym serverem
    QSettings settings(QString(":/res/resources/config.ini"),QSettings::IniFormat);
    QString ip = settings.value("serverIP/server1").toString();
    int port = settings.value("serverPort/server1").toInt();
    ui->lineEditIP->setText(ip);
    ui->portSpinBox->setValue(port);
    ui->PushConnect->click();

//-------------

    //dodanie gracza
    connect(this,SIGNAL(dodajGracza(QString)),nw,SLOT(gracze(QString)));

    //usuniecie gracza
    connect(this,SIGNAL(usunGracza(QString)),nw,SLOT(usunGracza(QString)));

    //podanie kosci
    connect(this,SIGNAL(rzucone(QString)),nw,SLOT(rzucone(QString)));

    //wybranie kosci
    connect(nw,SIGNAL(wybierzKosc(QString)),this,SLOT(wybierzKosc(QString)));

    //zablokowanie kosci
    connect(this,SIGNAL(zablokujKosc(QString)),nw,SLOT(zablokujKosc(QString)));

    //wyjscie z pokoju
    connect(nw,SIGNAL(exitPok()),this,SLOT(exitPok()));

    //reroll
    connect(nw,SIGNAL(reroll()),this,SLOT(reroll()));

    //gotowosc
    connect(nw,SIGNAL(gotowy()),this,SLOT(gotowy()));

    //niegotowosc
    connect(this,SIGNAL(unset()),nw,SLOT(unset()));

    //przerzucono
    connect(this,SIGNAL(rerolled(QString)),nw,SLOT(rerolled(QString)));

    connect(this,SIGNAL(punktowanie()),nw,SLOT(punktowanie()));
    //-------------------------------
    //numerrundy
    connect(this,SIGNAL(roundNum(QString)),nw,SLOT(roundNum(QString)));
    //otrzymane punkty
    connect(this,SIGNAL(przypiszPunkty(QString)),nw,SLOT(przypiszPunkty(QString)));
    //punktacja koncowa
    connect(this,SIGNAL(PunktyKoniec(QString)),nw,SLOT(PunktyKoniec(QString)));
    //zwyciezca
    connect(this,SIGNAL(zwyciezca(QString)),nw,SLOT(zwyciezca(QString)));

}

wybor::~wybor()
{
    powiadomienia = false;
    sock->close();
    delete ui;
}

void wybor::responseHandler(QByteArray komenda){
    QString command = QString::fromUtf8(komenda).trimmed();
    int lend=command.indexOf(":");
    while(lend!=-1 && command.length()>3){
        QString kmd = command.first(3);
        QString dane = command.mid(3,lend-3);
        if(!dane.isEmpty()){
            if(kmd=="pok"){
                roomsSetup(dane);

            } else if(kmd=="rom"){
                joinGame(dane);

            } else if(kmd=="nic"){
                emit dodajGracza(dane);

            }  else if(kmd=="got"){
                emit zablokujKosc(dane);

            } else if(kmd=="qit"){
                emit usunGracza(dane);

            }  else if(kmd=="kos"){
                emit rzucone(dane);

            } else if(kmd=="rrl"){
                //przerzut
                emit rerolled(dane);

            } else if(kmd=="rnd"){
                //numer rundy
                emit roundNum(dane);

            } else if(kmd=="pts"){
                //otrzymane punkty
                emit przypiszPunkty(dane);

            }  else if(kmd=="fin"){
                //punktacja koncowa
                emit PunktyKoniec(dane);

            } else if(kmd=="win"){
                //zwyciezca

            } else if(kmd=="pdn"){
                //konieczbierania kosci przez jednego z graczy

            } else if(kmd=="prd"){
                //gotowosc do startu gry

            }  else if(kmd=="set"){
                //opcje gry

            }
        } else {
            if(kmd=="ust"){
                emit unset();

            }else if(kmd=="bck"){
                //powrocono do poczekalni
                QMessageBox::information(this, "Left Game", "Opuszczono gre");

            }else if(kmd=="t-e"){
                emit punktowanie();

            }else if(kmd=="beg"){
                //game start

            }else if(kmd=="nst"){
                //ustowiono nick
                ui->listWidget->setEnabled(true);
                ui->refresh->setEnabled(true);
                ui->newRoom->setEnabled(true);
                QMessageBox::information(this, "Done", "Ustawiono nick");

            } else if(kmd=="end"){
                //skonczono gre

            }else if(kmd=="nrm"){
                //brak miejsc na nowe pokoje
                QMessageBox::critical(this, "Error", "Nie można stworzyć nowego pokoju");

            }else if(kmd=="rbd"){
                //podlaczenie do pokoju niemozliwe
                QMessageBox::critical(this, "Error", "Błąd dołączenia do pokoju");

            }else if(kmd=="bnc"){
                //niepoprawny nick
                QMessageBox::critical(this, "Error", "Nick niepoprawny");
            }else if(kmd=="zaj"){
                //wybrano zajetą kość
                // QMessageBox::critical(this, "Error", "zla kosc");
            }else if(kmd=="brq"){
                //niepoprawne zapytanie
                QMessageBox::critical(this, "Error", "Błąd klienta");
            }else if(kmd=="unc"){
                //nick w użyciu
                QMessageBox::critical(this, "Error", "Nick jest już w użyciu");
            }else if(kmd=="bnc"){
                //zł← nick
                QMessageBox::critical(this, "Error", "Nick zbyt krótki, przynajmniej 3 litery");
            }
        }
        command = command.remove(0,lend+1);
        lend=command.indexOf(":");
    }
}

void wybor::connectRoom(){
    auto dana = (ui->listWidget->currentItem()->data(Qt::UserRole)).value<int>();
    QString msg = "chs"+QString::number(dana);
    sock->write(msg.toUtf8()+":");

}

void wybor::joinGame(QString dane){
    int wyb = dane.indexOf("ply");
    int pok = (dane.first(wyb)).toInt();
    int gracze = (dane.remove(0,wyb+3)).toInt();
    this->hide();
    nw->show();
    nw->setup(pok,gracze);


}

void wybor::roomsSetup(QString dane){
    ui->listWidget->clear();
    int pok = dane.indexOf("p");
    int gra = dane.indexOf("g");
    QString poknum;
    QString granum;
    while(pok!=-1 && gra!=-1){
        poknum = dane.mid(pok+1,gra-pok-1);
        granum = dane.at(gra+1);
        auto* item = new QListWidgetItem("Room number: "+poknum+", players: "+granum);
        QVariant v;
        v.setValue(poknum.toInt());
        item->setData(Qt::UserRole,v);
        ui->listWidget->addItem(item);
        dane.erase(dane.begin(),dane.begin()+gra+2);
        pok = dane.indexOf("p");
        gra = dane.indexOf("g");
    }
}

void wybor::connectBtnHit() {
    if(sock)
        delete sock;
    sock = new QTcpSocket(this);
    connTimeoutTimer = new QTimer(this);
    connTimeoutTimer->setSingleShot(true);
    connect(connTimeoutTimer, &QTimer::timeout, [&]{
        socketDisconnected();
    });
    connect(sock, &QTcpSocket::connected, this, &wybor::socketConnected);
    connect(sock, &QTcpSocket::disconnected, this, &wybor::socketDisconnected);
    connect(sock, &QTcpSocket::errorOccurred, this, &wybor::socketError);
    connect(sock, &QTcpSocket::readyRead, this, &wybor::socketReadable);

    sock->connectToHost(ui->lineEditIP->text(), ui->portSpinBox->value());
    connTimeoutTimer->start(3000);
}

void wybor::socketConnected() {
    ui->nickEdit->setEnabled(true);
    connTimeoutTimer->stop();
    connTimeoutTimer->disconnect();
    QMessageBox::information(this, "Done", "Connected");
    //wyslij prosbe o pokoje
    sock->write("gib:");
}

void wybor::socketDisconnected(){
    ui->nickEdit->setEnabled(false);
    ui->listWidget->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->GameButton->setEnabled(false);
    ui->newRoom->setEnabled(false);
    sock->abort();
    sock->deleteLater();
    sock = nullptr;
    connTimeoutTimer->deleteLater();
    connTimeoutTimer=nullptr;
    if(powiadomienia) QMessageBox::critical(this, "Error", "Connect timed out");
}

void wybor::socketError(QTcpSocket::SocketError err){
    if(err == QTcpSocket::RemoteHostClosedError)
        return;
    if(connTimeoutTimer){
        connTimeoutTimer->stop();
        connTimeoutTimer->deleteLater();
        connTimeoutTimer=nullptr;
    }
    QMessageBox::critical(this, "Error", sock->errorString());
}

void wybor::socketReadable(){
    QByteArray ba = sock->readAll();
    responseHandler(ba);
}


void wybor::sendNick(){
    auto nick = ui->nickEdit->text().trimmed();
    if(nick.isEmpty()){
        return;
    }
    sock->write("nnc"+nick.toUtf8()+":");
}

//sloty


void wybor::wybierzKosc(QString dane){
    sock->write("get"+dane.toUtf8()+":");
}
void wybor::exitPok(){
    sock->write("ext:");
    this->show();
}
void wybor::reroll(){
    sock->write("rol:");
}
void wybor::gotowy(){
    sock->write("rdy:");
}

void wybor::punkt(QString dane){
    QMessageBox::information(this, "Done", dane);
    sock->write("ptn"+dane.toUtf8()+":");
}

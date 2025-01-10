#include "wybor.h"
#include "./ui_wybor.h"
#include "gra.h"

#include <QMessageBox>


wybor::wybor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wybor)
{
    ui->setupUi(this);

    //server koneksje
    connect(ui->PushConnect, &QPushButton::clicked, this, &wybor::connectBtnHit);
    connect(ui->lineEditIP, &QLineEdit::returnPressed, ui->PushConnect, &QPushButton::click);

    //nick
    connect(ui->nickEdit, &QLineEdit::editingFinished, this, &wybor::sendNick);

    //odswiez pokoje
    connect(ui->refresh, &QPushButton::clicked, this,[=]() {sock->write("gib");});

    //wyslij prosbe o nowy pokoj
    connect(ui->newRoom, &QPushButton::clicked, this,[=]() {sock->write("new");});

    //dolacz do pokoju
    connect(ui->GameButton,&QPushButton::clicked, this, &wybor::connectRoom);
    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&wybor::connectRoom);
    connect(ui->listWidget,&QListWidget::itemClicked,this,[=]() {ui->GameButton->setEnabled("true");});
    //

}

wybor::~wybor()
{
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
            }
        }
        command = command.remove(0,lend+1);
        lend=command.indexOf(":");
    }
}

void wybor::connectRoom(){
    auto dana = (ui->listWidget->currentItem()->data(Qt::UserRole)).value<int>();
    QString msg = "chs"+QString::number(dana);
    sock->write(msg.toUtf8());

}

void wybor::joinGame(QString dane){
    int wyb = dane.indexOf("ply");
    int pok = (dane.first(wyb)).toInt();
    int gracze = (dane.remove(0,wyb+3)).toInt();
    gra *nw = new gra();
    this->hide();
    nw->show();
    nw->setup(pok,gracze);

    connect(this,SIGNAL(dodajGracza(QString)),nw,SLOT(gracze(QString)));

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
    ui->listWidget->setEnabled(true);
    ui->refresh->setEnabled(true);
    ui->newRoom->setEnabled(true);
    connTimeoutTimer->stop();
    connTimeoutTimer->disconnect();
    QMessageBox::information(this, "Done", "Connected");
    //wyslij prosbe o pokoje
    sock->write("gib");
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
    QMessageBox::critical(this, "Error", "Connect timed out");
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
    sock->write("nnc"+nick.toUtf8());
}


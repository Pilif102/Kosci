#include "wybor.h"
#include "./ui_wybor.h"

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

    //dolaczenie do pokoju
    connect(ui->GameButton, &QPushButton::clicked, this, &wybor::joinBtnHit);

}

wybor::~wybor()
{
    sock->close();
    delete ui;
}

void wybor::responseHandler(QByteArray komenda){
    QString command = QString::fromUtf8(komenda).trimmed();
    QString kmd = command.left(3);
    QString dane = command.remove(0,3);
    if(kmd=="pok"){
        QMessageBox::information(this, "EYO", dane);
    }
}

void wybor::roomsSetup(){
}

void wybor::connectBtnHit() {
    //ui->connectGroup->setEnabled(false);
    //ui->msgsTextEdit->append("<b>Connecting to " + ui->hostLineEdit->text() + ":" + QString::number(ui->portSpinBox->value())+"</b>");
    if(sock)
        delete sock;
    sock = new QTcpSocket(this);
    connTimeoutTimer = new QTimer(this);
    connTimeoutTimer->setSingleShot(true);
    connect(connTimeoutTimer, &QTimer::timeout, [&]{
        sock->abort();
        sock->deleteLater();
        sock = nullptr;
        connTimeoutTimer->deleteLater();
        connTimeoutTimer=nullptr;
        //ui->connectGroup->setEnabled(true);
        //ui->msgsTextEdit->append("<b>Connect timed out</b>");
        QMessageBox::critical(this, "Error", "Connect timed out");
    });

    connect(sock, &QTcpSocket::connected, this, &wybor::socketConnected);
    connect(sock, &QTcpSocket::disconnected, this, &wybor::socketDisconnected);
    connect(sock, &QTcpSocket::errorOccurred, this, &wybor::socketError);
    connect(sock, &QTcpSocket::readyRead, this, &wybor::socketReadable);

    sock->connectToHost(ui->lineEditIP->text(), ui->portSpinBox->value());
    connTimeoutTimer->start(3000);
}

void wybor::socketConnected() {
    connTimeoutTimer->stop();
    connTimeoutTimer->disconnect();
    QMessageBox::information(this, "Done", "Connected");
    //wyslij prosbe o pokoje
    sock->write("gib");
}

void wybor::socketDisconnected(){
    //ui->msgsTextEdit->append("<b>Disconnected</b>");
    //ui->talkGroup->setEnabled(false);
    //ui->connectGroup->setEnabled(true);
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
    //ui->msgsTextEdit->append("<b>Socket error: "+sock->errorString()+"</b>");
    //ui->talkGroup->setEnabled(false);
    //ui->connectGroup->setEnabled(true);
}

void wybor::socketReadable(){
    QByteArray ba = sock->readAll();
    responseHandler(ba);
    //ui->msgsTextEdit->append();
    //ui->msgsTextEdit->setAlignment(Qt::AlignLeft);
}


void wybor::sendNick(){

}

void wybor::joinBtnHit() {

}

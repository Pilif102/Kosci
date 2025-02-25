#ifndef WYBOR_H
#define WYBOR_H

#include <QTimer>
#include <QTcpSocket>
#include <QMainWindow>
#include <QWidget>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class wybor;
}
QT_END_NAMESPACE

class wybor : public QMainWindow
{
    Q_OBJECT

public:
    wybor(QWidget *parent = nullptr);
    ~wybor();

public slots:
    void wybierzKosc(QString dane);
    void exitPok();
    void reroll();
    void gotowy();
    void punkt(QString dane);
    void change(int g,int r,int p);


protected:
    QTimer * connTimeoutTimer{nullptr};
    QTcpSocket * sock {nullptr};
    void connectRoom();
    void responseHandler(QByteArray komenda);
    void connectBtnHit();
    void joinGame(QString dane);
    void roomsSetup(QString dane);
    void sendNick();
    void socketConnected();
    void socketDisconnected();
    void socketError(QTcpSocket::SocketError);
    void socketReadable();
    void wybieranie();

signals:
    void dodajGracza(QString dane);
    void usunGracza(QString dane);
    void rzucone(QString dane);
    void zablokujKosc(QString dane);
    void unset();
    void punktowanie();
    void rerolled(QString dane);
    void PunktyKoniec(QString dane);
    void przypiszPunkty(QString dane);
    void roundNum(QString dane);
    void zwyciezca(QString dane);
    void poczatekGry();
    void graczGotowy(QString dane);
    void opcje(QString dane);
    void remain(QString dane);


private:
    Ui::wybor *ui;
};
#endif // WYBOR_H

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


private:
    Ui::wybor *ui;
};
#endif // WYBOR_H

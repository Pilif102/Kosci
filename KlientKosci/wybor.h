#ifndef WYBOR_H
#define WYBOR_H

#include <QTimer>
#include <QTcpSocket>
#include <QMainWindow>
#include <QWidget>

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
    QTcpSocket * sock {nullptr};

protected:
    QTimer * connTimeoutTimer{nullptr};

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

private:
    Ui::wybor *ui;
};
#endif // WYBOR_H

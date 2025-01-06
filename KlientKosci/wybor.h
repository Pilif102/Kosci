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

protected:
    QTcpSocket * sock {nullptr};
    QTimer * connTimeoutTimer{nullptr};
    void responseHandler(QByteArray komenda);
    void connectBtnHit();
    void roomsSetup();
    void sendNick();
    void joinBtnHit();
    void socketConnected();
    void socketDisconnected();
    void socketError(QTcpSocket::SocketError);
    void socketReadable();

private:
    Ui::wybor *ui;
};
#endif // WYBOR_H

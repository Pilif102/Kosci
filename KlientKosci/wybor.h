#ifndef WYBOR_H
#define WYBOR_H

#include <QMainWindow>

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

private:
    Ui::wybor *ui;
};
#endif // WYBOR_H

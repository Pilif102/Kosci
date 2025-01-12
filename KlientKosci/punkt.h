#ifndef PUNKT_H
#define PUNKT_H

#include <QWidget>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class Punkt;
}

class Punkt : public QWidget
{
    Q_OBJECT

public:
    explicit Punkt(QWidget *parent = nullptr);
    ~Punkt();
    void setup(bool wyb[17]);
    void sendIt();

signals:
    void wybrane(int wyb);

private:
    Ui::Punkt *ui;
};


#endif // PUNKT_H

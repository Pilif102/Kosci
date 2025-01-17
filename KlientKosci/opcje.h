#ifndef OPCJE_H
#define OPCJE_H

#include <QDialog>

namespace Ui {
class Opcje;
}

class Opcje : public QDialog
{
    Q_OBJECT

public:
    explicit Opcje(QWidget *parent = nullptr);
    ~Opcje();
public slots:
    void setup(int g,int r,int p);

signals:
    void wybOpcje(int g,int r,int p);

private:
    Ui::Opcje *ui;
    void wybrano();
};

#endif // OPCJE_H

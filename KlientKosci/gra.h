#ifndef GRA_H
#define GRA_H

#include <QMainWindow>
#include "wybor.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QProxyStyle>

namespace Ui {
class gra;
}

class gra : public QMainWindow
{
    Q_OBJECT

public:
    explicit gra(QWidget *parent = nullptr);
    void setup(int pokoj,int gracze);
    void dodajKosc();
    void test(QModelIndex index);
    ~gra();

public slots:
    void gracze(QString dane);

protected:
    int liczbaGraczy;

private:
    Ui::gra *ui;
};

#endif // GRA_H

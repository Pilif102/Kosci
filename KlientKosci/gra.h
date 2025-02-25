#ifndef GRA_H
#define GRA_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItem>
#include <QProxyStyle>
#include <QCloseEvent>

namespace Ui {
class gra;
}

class gra : public QMainWindow
{
    Q_OBJECT

public:
    explicit gra(QWidget *parent = nullptr);
    void setup(int pokoj,int gracze);

    void test(QModelIndex index);

    ~gra();

public slots:
    void gracze(QString dane);
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
    void wybrane(int wyb);
    void poczatekGry();
    void graczGotowy(QString dane);
    void opcje(QString dane);
    void wybOpcje(int g,int r,int p);
    void remain(QString dane);

protected:
    int liczbaGraczy;

signals:
    void wybierzKosc(QString dane);
    void exitPok();
    void reroll();
    void gotowy();
    void punkt(QString dane);
    void change(int g,int r,int p);

private:
    Ui::gra *ui;
    void closeEvent(QCloseEvent* event);
};

#endif // GRA_H

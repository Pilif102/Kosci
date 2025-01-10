#include "gra.h"
#include "ui_gra.h"

int lGraczy;
int pokoj;

gra::gra(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gra)
{
    ui->setupUi(this);
}

void gra::setup(int pokoje,int gracze){
    ui->gracze->setRowCount(2);
    ui->gracze->setColumnCount(gracze+1);
    lGraczy = gracze+1;
    pokoj = pokoje;
}

void gra::gracze(QString dane){
    int num=dane.indexOf(",");
    if(num==-1) QMessageBox::critical(this, "Error", "zle polecienie"); //wroc do poczekalni czy cos
    int numer = dane.first(num).toInt();
    if(ui->gracze->columnCount()<numer) ui->gracze->insertColumn(ui->gracze->columnCount());
    dane = dane.remove(0,num+1);
    auto* v = new QTableWidgetItem(dane);
    ui->gracze->setItem(0,numer,v);
    ui->gracze->setItem(1,numer,0);
}

gra::~gra()
{
    delete ui;
}

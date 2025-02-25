#include "gra.h"
#include "ui_gra.h"
#include "punkt.h"
#include "opcje.h"

int lGraczy=0;
int yourNumber=-1;
int kosci[5]={};
bool wybWyn[17]={};
int g,r,p;
bool rolled = false;
int maxRoll = 3;
int rol = 0;

Punkt *pkty;
Opcje *opcj;
QStandardItemModel *model = new QStandardItemModel;

class ProxyStyle: public QProxyStyle{
public:
    using QProxyStyle::QProxyStyle;
    QRect subElementRect(SubElement subElement, const QStyleOption *option, const QWidget *widget) const override{
        QRect rect = QProxyStyle::subElementRect(subElement, option, widget);
        if(subElement == SE_ItemViewItemDecoration){
            rect.moveCenter(option->rect.center());
        }
        return rect;
    }
};

gra::gra(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gra)
{
    pkty = new Punkt();
    opcj = new Opcje(this);
    ui->setupUi(this);
    ui->tableView->setStyle(new ProxyStyle(ui->tableView->style()));
    connect(ui->tableView,&QTableView::clicked,this,&gra::test);
    connect(ui->Gotowosc,&QCheckBox::clicked,this,[=]() {emit gotowy();ui->Gotowosc->setEnabled(false);});
    connect(ui->rollButton,&QPushButton::clicked,this,[=]() {emit reroll();if(rol != 0) ui->tableView->setEnabled(false);});
    connect(ui->menubar,&QMenuBar::triggered,this,[=]() {if(yourNumber==0){opcj->show();opcj->setup(g,r,p);}});

    //-pnktconn
    connect(pkty,SIGNAL(wybrane(int)),this,SLOT(wybrane(int)));

    //opcje
    connect(opcj,SIGNAL(wybOpcje(int,int,int)),this,SLOT(wybOpcje(int,int,int)));
}

void gra::closeEvent(QCloseEvent* event){
    lGraczy=0;
    yourNumber=-1;
    std::fill(wybWyn,wybWyn+17,false);
    emit exitPok();
    pkty->close();
    opcj->close();
    event->accept();
}

void gra::test(QModelIndex index){
    //napisz ze bierzesz kosc
    int kol = index.column();
    int rzd = index.row();
    int Kosc = kol+(rzd*5);
    emit wybierzKosc(QString::number(Kosc));

}

void gra::setup(int pokoje,int gracze){
    lGraczy=0;
    yourNumber=-1;
    std::fill(wybWyn,wybWyn+17,false);
    ui->gracze->setRowCount(2);
    ui->gracze->setColumnCount(gracze+1);
    model->clear();
    ui->pokoj->setText("Pokoj: "+QString::number(pokoje));
    ui->runda->setText("Runda: 0");
    ui->gracze->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gracze->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rollLabel->setText("REROLLS LEFT : 2");
}

void gra::usunGracza(QString dane){
    lGraczy--;
    if(yourNumber>dane.toInt()) yourNumber--;
    ui->gracze->removeColumn(dane.toInt());
    model->removeRow(lGraczy);
    unset();
}

void gra::rzucone(QString dane){
    for(int i=0;i<5;i++){
        for(int j=0;j<lGraczy;j++){
            QString numer = dane[i+j*5];
            QImage image(":/res/resources/side"+numer+".jpeg");
            image = image.scaled(50,50,Qt::KeepAspectRatio);
            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
            if(rolled){
                if(model->item(j,i)->background()!=item->background()) item->setBackground(model->item(j,i)->background());
            }
            model->setItem(j, i, item);
        }
    }
    ui->tableView->setModel(model);
    rolled=false;
    ui->rollButton->setEnabled(true);
    ui->tableView->setEnabled(true);
}

void gra::zablokujKosc(QString dane){
    int pok = dane.indexOf("g");
    int kosc = dane.first(pok).toInt();
    QString gracz = dane.at(pok+1);
    int col = kosc%5;
    int row = kosc/5;
    QColor* kolor = new QColor(Qt::red);
    if(gracz.toInt()==yourNumber) kolor->setNamedColor("blue");
    model->item(row,col)->setBackground(*kolor);

}

void gra::unset(){
    ui->Gotowosc->setEnabled(true);
    ui->Gotowosc->setChecked(false);
    for(int i=0;i<lGraczy;i++){
        ui->gracze->item(0,i)->setBackground(QColor(Qt::white));
    }
}

void gra::punktowanie(){
    ui->rollLabel->setText("REROLLS LEFT : "+QString::number(maxRoll));
    pkty->show();
    pkty->setup(wybWyn);
}

void gra::rerolled(QString dane){
    rolled = true;
    ui->rollLabel->setText("REROLLS LEFT : "+dane);
    ui->rollButton->setEnabled(false);
    rol = dane.toInt();
}

void gra::gracze(QString dane){
    lGraczy++;
    int num=dane.indexOf(",");
    if(num==-1) QMessageBox::critical(this, "Error", "zle polecienie"); //wroc do poczekalni czy cos
    int numer = dane.first(num).toInt();
    if(yourNumber==-1) yourNumber=numer;
    if(ui->gracze->columnCount()<=numer) ui->gracze->insertColumn(ui->gracze->columnCount());
    dane = dane.remove(0,num+1);
    auto* v = new QTableWidgetItem(dane);
    ui->gracze->setItem(0,numer,v);
    auto* e = new QTableWidgetItem("0");
    ui->gracze->setItem(1,numer,e);
    if(lGraczy>yourNumber) unset();
}


void gra::PunktyKoniec(QString dane){
    int lim = dane.indexOf("usr");
    int punkty = dane.first(lim).toInt();
    int gracz = dane.mid(lim+3,dane.length()).toInt();
    ui->gracze->item(1,gracz)->setText(QString::number(punkty));
}

void gra::przypiszPunkty(QString dane){

    int lim = dane.indexOf("usr");
    int punkty = dane.first(lim).toInt();
    int gracz = dane.mid(lim+3,dane.length()).toInt();
    ui->gracze->item(1,gracz)->setText(QString::number(ui->gracze->item(1,gracz)->text().toInt()+punkty));
}

void gra::roundNum(QString dane){
    ui->runda->setText("Runda: "+dane);
}

void gra::zwyciezca(QString dane){
    int zwyciezca = dane.toInt();
    QMessageBox::information(this,"KONIEC GRY","Zwycięzca: " + ui->gracze->item(0,zwyciezca)->text());
    ui->Gotowosc->setChecked(false);
    ui->Gotowosc->setEnabled(true);
    model->clear();
    ui->runda->setText("Runda: 0");
    std::fill(wybWyn,wybWyn+17,false);

}


void gra::wybrane(int wyn){
    QString wybr = QString::number(wyn);
    wybWyn[wyn] = true;
    emit punkt(wybr);
}

void gra::poczatekGry(){
    for(int i=0;i<lGraczy;i++){
        ui->gracze->item(0,i)->setBackground(QColor(Qt::white));
        ui->gracze->item(1,i)->setText("0");
    }
}

void gra::graczGotowy(QString dane){
    int gracz = dane.toInt();
    ui->gracze->item(0,gracz)->setBackground(QColor(Qt::yellow));
}

void gra::opcje(QString dane){
    int gracz = dane.indexOf("g");
    int rund = dane.indexOf("r");
    int rolls = dane.indexOf("p");
    g =dane.mid(gracz+1,rund-gracz-1).toInt();
    r = dane.mid(rund+1,rolls-rund-1).toInt();
    p = dane.mid(rolls+1,rolls-dane.length()-1).toInt();
    maxRoll = p;
    rol = p;
    ui->MaxGraczy->setText("Max Players: " + QString::number(g));
    ui->MaxRund->setText("Max rounds: " + QString::number(r));
    ui->MaxRolls->setText("Max rolls: " + QString::number(p));
    unset();

}

void gra::wybOpcje(int g,int r,int p){
    ui->MaxGraczy->setText("Max Players: " + QString::number(g));
    ui->MaxRund->setText("Max rounds: " + QString::number(r));
    ui->MaxRolls->setText("Max rolls: " + QString::number(p));
    emit change(g,r,p);
}

void gra::remain(QString dane){
    int czas = dane.toInt();
    ui->progressBar->setValue(czas);
}
gra::~gra()
{
    delete ui;
}



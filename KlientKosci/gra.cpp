#include "gra.h"
#include "ui_gra.h"
#include "punkt.h"

int lGraczy=0;
int pokoj;
int runda=0;
int maxRols=2;
int yourNumber=-1;
bool czyPunkty = false;
int punkty[17]={};
bool wybWyn[17]={};

Punkt *pkty;
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
    ui->setupUi(this);
    ui->tableView->setStyle(new QProxyStyle(ui->tableView->style()));
    connect(ui->tableView,&QTableView::clicked,this,&gra::test);
    connect(ui->Gotowosc,&QCheckBox::clicked,this,[=]() {emit gotowy();ui->Gotowosc->setEnabled(false);});

    //-pnktconn
    connect(pkty,SIGNAL(wybrane(int)),this,SLOT(wybrane(int)));
}

void gra::closeEvent(QCloseEvent* event){
    lGraczy=0;
    runda=0;
    yourNumber=-1;
    czyPunkty = false;
    std::fill(punkty,punkty+17,0);
    std::fill(wybWyn,wybWyn+17,false);
    emit exitPok();
    pkty->close();
    event->accept();
}

void gra::test(QModelIndex index){
    //napisz ze bierzesz kosc
    int kol = index.column();
    int rzd = index.row();
    int Kosc = kol+(rzd*5);
    emit wybierzKosc(QString::number(Kosc));
    // model->item(index.row(),index.column())->setBackground(QColor(Qt::blue));

}

void gra::setup(int pokoje,int gracze){
    lGraczy=0;
    runda=0;
    yourNumber=-1;
    czyPunkty = false;
    std::fill(punkty,punkty+17,0);
    std::fill(wybWyn,wybWyn+17,false);
    ui->gracze->setRowCount(2);
    ui->gracze->setColumnCount(gracze+1);
    pokoj = pokoje;
    model->clear();
    ui->pokoj->setText("Pokoj: "+QString::number(pokoje));
    ui->runda->setText("Runda: 0");
    ui->gracze->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gracze->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    maxRols=2;
    ui->rollLabel->setText("REROLLS LEFT : "+QString::number(maxRols));
}

void gra::usunGracza(QString dane){
    lGraczy--;
    if(yourNumber>dane.toInt()) yourNumber--;
    ui->gracze->removeColumn(dane.toInt());
    model->removeRow(lGraczy);
}

void gra::rzucone(QString dane){
    for(int i=0;i<5;i++){
        for(int j=0;j<lGraczy;j++){
            QString numer = dane[i+j*5];
            QImage image(":/res/resources/side"+numer+".jpeg");
            image = image.scaled(50,50,Qt::KeepAspectRatio);
            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
            // item->setBackground(QColor(Qt::blue));
            model->setItem(j, i, item);
        }
    }
    ui->tableView->setStyle(new QProxyStyle(ui->tableView->style()));
    ui->tableView->setModel(model);

}

void gra::zablokujKosc(QString dane){
    // model->item(index.row(),index.column())->setBackground(QColor(Qt::blue));
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
}

void gra::punktowanie(){
    wybWyn[10]=true;
    pkty->show();
    pkty->setup(wybWyn);
}

void gra::rerolled(QString dane){
    ui->rollLabel->setText("REROLLS LEFT : "+dane);
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
}


void gra::PunktyKoniec(QString dane){

}

void gra::przypiszPunkty(QString dane){

}

void gra::roundNum(QString dane){

}

void gra::zwyciezca(QString dane){

}


void gra::wybrane(int wyn){

}

void gra::dodajKosc(){
}

gra::~gra()
{
    delete ui;
}



#include "gra.h"
#include "ui_gra.h"

int lGraczy;
int pokoj;
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
    ui->setupUi(this);
    connect(ui->tableView,&QTableView::clicked,this,&gra::test);
}

void gra::test(QModelIndex index){
    QMessageBox::critical(this, "Error", QString::number(index.column()));
}

void gra::setup(int pokoje,int gracze){
    ui->gracze->setRowCount(2);
    ui->gracze->setColumnCount(gracze+1);
    lGraczy = gracze+1;
    pokoj = pokoje;
    ui->pokoj->setText(QString::number(pokoje));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setStyle(new QProxyStyle(ui->tableView->style()));
    dodajKosc();
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

void gra::dodajKosc(){
    // auto* widget = new QWidget();
    // auto* layout = new QHBoxLayout();
    // auto* text = new QLabel();
    // QPixmap pix(":/res/resources/side1.jpeg");
    // pix.size().setHeight(50);
    // pix.size().setWidth(50);
    // text->setPixmap(pix);
    // layout->addWidget(text);
    // widget->setLayout(layout);

    // // ui->frame->layout()->addWidget(widget);
    // ui->tableView->setIndexWidget(ui->tableView->model()->index(0,0),widget);

    for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
            QImage image(":/res/resources/side1.jpeg");
            image = image.scaled(50,50,Qt::KeepAspectRatio);
            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
            model->setItem(j, i, item);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->setStyle(new ProxyStyle(ui->tableView->style()));
}

gra::~gra()
{
    delete ui;
}



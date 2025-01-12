#include "punkt.h"
#include "ui_punkt.h"

using namespace std;
string wybNaz[17]={
    "jedynki","dwojki","trojki","czworki","piatki","szóstki",
    "para","dwie pary","trojka","kareta","full","maly strit","duzy strit","parzyste","nieparzyste","poker","szansa"
};

Punkt::Punkt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Punkt)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowCloseButtonHint,false);
    connect(ui->chooseBtn,&QPushButton::clicked,this,&Punkt::sendIt);
    connect(ui->Opcje,&QListWidget::itemDoubleClicked,this,&Punkt::sendIt);
    connect(ui->Opcje,&QListWidget::itemClicked,this,[=]() {ui->chooseBtn->setEnabled(true);});
}

void Punkt::setup(bool wyb[17]){
    ui->chooseBtn->setEnabled(false);
    ui->Opcje->clearSelection();
    for(int i=0;i<17;i++){
        if(wyb[i]==false){
            QString naz = QString::fromStdString(wybNaz[i]);
            auto* item = new QListWidgetItem(naz);
            QVariant v;
            v.setValue(i);
            item->setData(Qt::UserRole,v);
            ui->Opcje->addItem(item);
        }
    }
}

void Punkt::sendIt(){

    auto dana = (ui->Opcje->currentItem()->data(Qt::UserRole)).value<int>();
    QMessageBox::information(this, "Done", QString::number(dana));
}

Punkt::~Punkt()
{
    delete ui;
}

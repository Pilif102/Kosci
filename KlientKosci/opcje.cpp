#include "opcje.h"
#include "ui_opcje.h"

Opcje::Opcje(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Opcje)
{
    ui->setupUi(this);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&Opcje::wybrano);
}

void Opcje::setup(int g,int r,int p){
    ui->Players->setValue(g);
    ui->rounds->setValue(r);
    ui->rerolls->setValue(p);
}

void Opcje::wybrano(){
    emit wybOpcje(ui->Players->value(),ui->rounds->value(),ui->rerolls->value());
}

Opcje::~Opcje()
{
    delete ui;
}

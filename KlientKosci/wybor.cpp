#include "wybor.h"
#include "./ui_wybor.h"

wybor::wybor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wybor)
{
    ui->setupUi(this);
}

wybor::~wybor()
{
    delete ui;
}

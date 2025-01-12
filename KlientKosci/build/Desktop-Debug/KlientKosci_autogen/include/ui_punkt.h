/********************************************************************************
** Form generated from reading UI file 'punkt.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUNKT_H
#define UI_PUNKT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Punkt
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *Opcje;
    QPushButton *chooseBtn;

    void setupUi(QWidget *Punkt)
    {
        if (Punkt->objectName().isEmpty())
            Punkt->setObjectName("Punkt");
        Punkt->resize(400, 300);
        verticalLayout = new QVBoxLayout(Punkt);
        verticalLayout->setObjectName("verticalLayout");
        Opcje = new QListWidget(Punkt);
        Opcje->setObjectName("Opcje");

        verticalLayout->addWidget(Opcje);

        chooseBtn = new QPushButton(Punkt);
        chooseBtn->setObjectName("chooseBtn");

        verticalLayout->addWidget(chooseBtn);


        retranslateUi(Punkt);

        QMetaObject::connectSlotsByName(Punkt);
    } // setupUi

    void retranslateUi(QWidget *Punkt)
    {
        Punkt->setWindowTitle(QCoreApplication::translate("Punkt", "Form", nullptr));
        chooseBtn->setText(QCoreApplication::translate("Punkt", "wybierz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Punkt: public Ui_Punkt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUNKT_H

/********************************************************************************
** Form generated from reading UI file 'opcje.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPCJE_H
#define UI_OPCJE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Opcje
{
public:
    QGridLayout *gridLayout;
    QLabel *MaxRounds;
    QLabel *MaxPlayers;
    QLabel *MaxRolls;
    QSpinBox *Players;
    QSpinBox *rounds;
    QSpinBox *rerolls;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Opcje)
    {
        if (Opcje->objectName().isEmpty())
            Opcje->setObjectName("Opcje");
        Opcje->resize(234, 143);
        gridLayout = new QGridLayout(Opcje);
        gridLayout->setObjectName("gridLayout");
        MaxRounds = new QLabel(Opcje);
        MaxRounds->setObjectName("MaxRounds");
        MaxRounds->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(MaxRounds, 1, 0, 1, 1);

        MaxPlayers = new QLabel(Opcje);
        MaxPlayers->setObjectName("MaxPlayers");
        MaxPlayers->setLayoutDirection(Qt::LeftToRight);
        MaxPlayers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(MaxPlayers, 0, 0, 1, 1);

        MaxRolls = new QLabel(Opcje);
        MaxRolls->setObjectName("MaxRolls");
        MaxRolls->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(MaxRolls, 2, 0, 1, 1);

        Players = new QSpinBox(Opcje);
        Players->setObjectName("Players");
        Players->setMinimum(2);
        Players->setMaximum(4);

        gridLayout->addWidget(Players, 0, 1, 1, 1);

        rounds = new QSpinBox(Opcje);
        rounds->setObjectName("rounds");
        rounds->setMinimum(1);
        rounds->setMaximum(17);

        gridLayout->addWidget(rounds, 1, 1, 1, 1);

        rerolls = new QSpinBox(Opcje);
        rerolls->setObjectName("rerolls");
        rerolls->setMaximum(5);

        gridLayout->addWidget(rerolls, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(Opcje);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(Opcje);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Opcje, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Opcje, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Opcje);
    } // setupUi

    void retranslateUi(QDialog *Opcje)
    {
        Opcje->setWindowTitle(QCoreApplication::translate("Opcje", "Dialog", nullptr));
        MaxRounds->setText(QCoreApplication::translate("Opcje", "Max rounds:", nullptr));
        MaxPlayers->setText(QCoreApplication::translate("Opcje", "Max players:", nullptr));
        MaxRolls->setText(QCoreApplication::translate("Opcje", "Max rerolls:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Opcje: public Ui_Opcje {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPCJE_H

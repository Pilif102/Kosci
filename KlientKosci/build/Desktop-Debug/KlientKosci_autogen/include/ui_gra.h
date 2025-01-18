/********************************************************************************
** Form generated from reading UI file 'gra.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRA_H
#define UI_GRA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gra
{
public:
    QAction *actionOpcje;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *runda;
    QCheckBox *Gotowosc;
    QLabel *pokoj;
    QLabel *MaxGraczy;
    QLabel *MaxRund;
    QLabel *MaxRolls;
    QTableWidget *gracze;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QLabel *rollLabel;
    QPushButton *rollButton;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *wyjdz;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gra)
    {
        if (gra->objectName().isEmpty())
            gra->setObjectName("gra");
        gra->resize(450, 544);
        gra->setMinimumSize(QSize(450, 0));
        actionOpcje = new QAction(gra);
        actionOpcje->setObjectName("actionOpcje");
        centralwidget = new QWidget(gra);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        runda = new QLabel(centralwidget);
        runda->setObjectName("runda");

        gridLayout->addWidget(runda, 0, 1, 1, 1);

        Gotowosc = new QCheckBox(centralwidget);
        Gotowosc->setObjectName("Gotowosc");

        gridLayout->addWidget(Gotowosc, 0, 2, 1, 1);

        pokoj = new QLabel(centralwidget);
        pokoj->setObjectName("pokoj");

        gridLayout->addWidget(pokoj, 0, 0, 1, 1);

        MaxGraczy = new QLabel(centralwidget);
        MaxGraczy->setObjectName("MaxGraczy");

        gridLayout->addWidget(MaxGraczy, 1, 0, 1, 1);

        MaxRund = new QLabel(centralwidget);
        MaxRund->setObjectName("MaxRund");

        gridLayout->addWidget(MaxRund, 1, 1, 1, 1);

        MaxRolls = new QLabel(centralwidget);
        MaxRolls->setObjectName("MaxRolls");

        gridLayout->addWidget(MaxRolls, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gracze = new QTableWidget(centralwidget);
        if (gracze->columnCount() < 4)
            gracze->setColumnCount(4);
        if (gracze->rowCount() < 2)
            gracze->setRowCount(2);
        gracze->setObjectName("gracze");
        gracze->setEnabled(true);
        gracze->setMinimumSize(QSize(0, 84));
        gracze->setMaximumSize(QSize(16777215, 84));
        gracze->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gracze->setRowCount(2);
        gracze->setColumnCount(4);

        verticalLayout->addWidget(gracze);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setEnabled(true);
        tableView->setMinimumSize(QSize(300, 300));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setTabKeyNavigation(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        rollLabel = new QLabel(centralwidget);
        rollLabel->setObjectName("rollLabel");

        horizontalLayout->addWidget(rollLabel);

        rollButton = new QPushButton(centralwidget);
        rollButton->setObjectName("rollButton");

        horizontalLayout->addWidget(rollButton);


        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setMaximum(30);
        progressBar->setValue(5);
        progressBar->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar);

        gra->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gra);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 450, 23));
        wyjdz = new QMenu(menubar);
        wyjdz->setObjectName("wyjdz");
        gra->setMenuBar(menubar);
        statusbar = new QStatusBar(gra);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(true);
        gra->setStatusBar(statusbar);

        menubar->addAction(wyjdz->menuAction());
        wyjdz->addAction(actionOpcje);

        retranslateUi(gra);

        QMetaObject::connectSlotsByName(gra);
    } // setupUi

    void retranslateUi(QMainWindow *gra)
    {
        gra->setWindowTitle(QCoreApplication::translate("gra", "MainWindow", nullptr));
        actionOpcje->setText(QCoreApplication::translate("gra", "Opcje", nullptr));
        runda->setText(QCoreApplication::translate("gra", "Runda:", nullptr));
        Gotowosc->setText(QCoreApplication::translate("gra", "ready", nullptr));
        pokoj->setText(QCoreApplication::translate("gra", "Pok\303\263j:", nullptr));
        MaxGraczy->setText(QCoreApplication::translate("gra", "Max Graczy:", nullptr));
        MaxRund->setText(QCoreApplication::translate("gra", "Max Rund:", nullptr));
        MaxRolls->setText(QCoreApplication::translate("gra", "Max przerzutow: ", nullptr));
        rollLabel->setText(QCoreApplication::translate("gra", "REROLLS LEFT :", nullptr));
        rollButton->setText(QCoreApplication::translate("gra", "REROLL", nullptr));
        progressBar->setFormat(QCoreApplication::translate("gra", "%v s", nullptr));
        wyjdz->setTitle(QCoreApplication::translate("gra", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gra: public Ui_gra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRA_H

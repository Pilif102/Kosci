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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QAction *action_back;
    QAction *action;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *pokoj;
    QLabel *runda;
    QCheckBox *Gotowosc;
    QTableWidget *gracze;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QLabel *rollLabel;
    QPushButton *rollButton;
    QMenuBar *menubar;
    QMenu *wyjdz;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gra)
    {
        if (gra->objectName().isEmpty())
            gra->setObjectName("gra");
        gra->resize(450, 520);
        gra->setMinimumSize(QSize(450, 0));
        action_back = new QAction(gra);
        action_back->setObjectName("action_back");
        action = new QAction(gra);
        action->setObjectName("action");
        centralwidget = new QWidget(gra);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pokoj = new QLabel(centralwidget);
        pokoj->setObjectName("pokoj");

        horizontalLayout_5->addWidget(pokoj);

        runda = new QLabel(centralwidget);
        runda->setObjectName("runda");

        horizontalLayout_5->addWidget(runda);

        Gotowosc = new QCheckBox(centralwidget);
        Gotowosc->setObjectName("Gotowosc");

        horizontalLayout_5->addWidget(Gotowosc);


        verticalLayout->addLayout(horizontalLayout_5);

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

        retranslateUi(gra);

        QMetaObject::connectSlotsByName(gra);
    } // setupUi

    void retranslateUi(QMainWindow *gra)
    {
        gra->setWindowTitle(QCoreApplication::translate("gra", "MainWindow", nullptr));
        action_back->setText(QCoreApplication::translate("gra", "change room", nullptr));
        action->setText(QCoreApplication::translate("gra", "noew", nullptr));
        pokoj->setText(QCoreApplication::translate("gra", "Pok\303\263j:", nullptr));
        runda->setText(QCoreApplication::translate("gra", "Runda:", nullptr));
        Gotowosc->setText(QCoreApplication::translate("gra", "ready", nullptr));
        rollLabel->setText(QCoreApplication::translate("gra", "REROLLS LEFT :", nullptr));
        rollButton->setText(QCoreApplication::translate("gra", "REROLL", nullptr));
        wyjdz->setTitle(QCoreApplication::translate("gra", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gra: public Ui_gra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRA_H

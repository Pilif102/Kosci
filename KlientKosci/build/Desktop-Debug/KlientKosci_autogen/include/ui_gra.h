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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gra
{
public:
    QAction *actiongo_back_to_menu;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *pokoj;
    QTableWidget *gracze;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menumenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gra)
    {
        if (gra->objectName().isEmpty())
            gra->setObjectName("gra");
        gra->resize(800, 600);
        actiongo_back_to_menu = new QAction(gra);
        actiongo_back_to_menu->setObjectName("actiongo_back_to_menu");
        centralwidget = new QWidget(gra);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        pokoj = new QLabel(centralwidget);
        pokoj->setObjectName("pokoj");

        verticalLayout->addWidget(pokoj);

        gracze = new QTableWidget(centralwidget);
        if (gracze->columnCount() < 1)
            gracze->setColumnCount(1);
        if (gracze->rowCount() < 2)
            gracze->setRowCount(2);
        gracze->setObjectName("gracze");
        gracze->setEnabled(true);
        gracze->setMaximumSize(QSize(16777215, 80));
        gracze->setEditTriggers(QAbstractItemView::NoEditTriggers);
        gracze->setRowCount(2);
        gracze->setColumnCount(1);

        verticalLayout->addWidget(gracze);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setEnabled(true);
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        gra->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gra);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menumenu = new QMenu(menubar);
        menumenu->setObjectName("menumenu");
        gra->setMenuBar(menubar);
        statusbar = new QStatusBar(gra);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(true);
        gra->setStatusBar(statusbar);

        menubar->addAction(menumenu->menuAction());
        menumenu->addAction(actiongo_back_to_menu);

        retranslateUi(gra);

        QMetaObject::connectSlotsByName(gra);
    } // setupUi

    void retranslateUi(QMainWindow *gra)
    {
        gra->setWindowTitle(QCoreApplication::translate("gra", "MainWindow", nullptr));
        actiongo_back_to_menu->setText(QCoreApplication::translate("gra", "change room", nullptr));
        pokoj->setText(QCoreApplication::translate("gra", "Pok\303\263j:", nullptr));
        label->setText(QCoreApplication::translate("gra", "REROLLS LEFT :", nullptr));
        pushButton->setText(QCoreApplication::translate("gra", "PushButton", nullptr));
        menumenu->setTitle(QCoreApplication::translate("gra", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gra: public Ui_gra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRA_H

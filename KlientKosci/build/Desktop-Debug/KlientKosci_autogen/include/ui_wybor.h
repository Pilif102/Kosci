/********************************************************************************
** Form generated from reading UI file 'wybor.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYBOR_H
#define UI_WYBOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wybor
{
public:
    QAction *actionclose;
    QAction *actionInfo;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditIP;
    QSpinBox *spinBoxPort;
    QPushButton *PushConnect;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *listView;
    QPushButton *GameButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *wybor)
    {
        if (wybor->objectName().isEmpty())
            wybor->setObjectName("wybor");
        wybor->setEnabled(true);
        wybor->resize(400, 400);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wybor->sizePolicy().hasHeightForWidth());
        wybor->setSizePolicy(sizePolicy);
        wybor->setMinimumSize(QSize(400, 400));
        wybor->setMaximumSize(QSize(4000, 4000));
        actionclose = new QAction(wybor);
        actionclose->setObjectName("actionclose");
        actionclose->setCheckable(false);
        actionInfo = new QAction(wybor);
        actionInfo->setObjectName("actionInfo");
        centralwidget = new QWidget(wybor);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEditIP = new QLineEdit(centralwidget);
        lineEditIP->setObjectName("lineEditIP");

        horizontalLayout->addWidget(lineEditIP);

        spinBoxPort = new QSpinBox(centralwidget);
        spinBoxPort->setObjectName("spinBoxPort");

        horizontalLayout->addWidget(spinBoxPort);

        PushConnect = new QPushButton(centralwidget);
        PushConnect->setObjectName("PushConnect");

        horizontalLayout->addWidget(PushConnect);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout->addWidget(listView);

        GameButton = new QPushButton(centralwidget);
        GameButton->setObjectName("GameButton");
        GameButton->setEnabled(false);

        verticalLayout->addWidget(GameButton);


        verticalLayout_2->addLayout(verticalLayout);

        wybor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(wybor);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 23));
        wybor->setMenuBar(menubar);

        retranslateUi(wybor);

        QMetaObject::connectSlotsByName(wybor);
    } // setupUi

    void retranslateUi(QMainWindow *wybor)
    {
        wybor->setWindowTitle(QCoreApplication::translate("wybor", "Sieci", nullptr));
        actionclose->setText(QCoreApplication::translate("wybor", "Close", nullptr));
        actionInfo->setText(QCoreApplication::translate("wybor", "Info", nullptr));
        PushConnect->setText(QCoreApplication::translate("wybor", "Connect to Server", nullptr));
        label->setText(QCoreApplication::translate("wybor", "<html><head/><body><p>Available games list:</p></body></html>", nullptr));
        GameButton->setText(QCoreApplication::translate("wybor", "Connect to game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wybor: public Ui_wybor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYBOR_H

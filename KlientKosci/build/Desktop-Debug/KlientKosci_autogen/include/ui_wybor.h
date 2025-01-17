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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wybor
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *wybor_2;
    QVBoxLayout *verticalLayout_3;
    QComboBox *Servery;
    QWidget *IpSetter;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditIP;
    QSpinBox *portSpinBox;
    QPushButton *PushConnect;
    QLineEdit *nickEdit;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *refresh;
    QPushButton *newRoom;
    QPushButton *GameButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *wybor)
    {
        if (wybor->objectName().isEmpty())
            wybor->setObjectName("wybor");
        wybor->setEnabled(true);
        wybor->resize(404, 424);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wybor->sizePolicy().hasHeightForWidth());
        wybor->setSizePolicy(sizePolicy);
        wybor->setMinimumSize(QSize(400, 0));
        wybor->setMaximumSize(QSize(4000, 4000));
        centralwidget = new QWidget(wybor);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(0, 0));
        wybor_2 = new QWidget();
        wybor_2->setObjectName("wybor_2");
        verticalLayout_3 = new QVBoxLayout(wybor_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        Servery = new QComboBox(wybor_2);
        Servery->setObjectName("Servery");

        verticalLayout_3->addWidget(Servery);

        tabWidget->addTab(wybor_2, QString());
        IpSetter = new QWidget();
        IpSetter->setObjectName("IpSetter");
        horizontalLayout = new QHBoxLayout(IpSetter);
        horizontalLayout->setObjectName("horizontalLayout");
        lineEditIP = new QLineEdit(IpSetter);
        lineEditIP->setObjectName("lineEditIP");

        horizontalLayout->addWidget(lineEditIP);

        portSpinBox = new QSpinBox(IpSetter);
        portSpinBox->setObjectName("portSpinBox");
        portSpinBox->setMaximum(99999);
        portSpinBox->setValue(9999);

        horizontalLayout->addWidget(portSpinBox);

        PushConnect = new QPushButton(IpSetter);
        PushConnect->setObjectName("PushConnect");

        horizontalLayout->addWidget(PushConnect);

        tabWidget->addTab(IpSetter, QString());

        verticalLayout_2->addWidget(tabWidget);

        nickEdit = new QLineEdit(centralwidget);
        nickEdit->setObjectName("nickEdit");
        nickEdit->setEnabled(false);
        nickEdit->setMaxLength(20);

        verticalLayout_2->addWidget(nickEdit);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setEnabled(false);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout->addWidget(listWidget);

        refresh = new QPushButton(centralwidget);
        refresh->setObjectName("refresh");
        refresh->setEnabled(false);

        verticalLayout->addWidget(refresh);

        newRoom = new QPushButton(centralwidget);
        newRoom->setObjectName("newRoom");
        newRoom->setEnabled(false);

        verticalLayout->addWidget(newRoom);

        GameButton = new QPushButton(centralwidget);
        GameButton->setObjectName("GameButton");
        GameButton->setEnabled(false);

        verticalLayout->addWidget(GameButton);


        verticalLayout_2->addLayout(verticalLayout);

        wybor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(wybor);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 404, 23));
        wybor->setMenuBar(menubar);

        retranslateUi(wybor);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(wybor);
    } // setupUi

    void retranslateUi(QMainWindow *wybor)
    {
        wybor->setWindowTitle(QCoreApplication::translate("wybor", "Sieci", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wybor_2), QCoreApplication::translate("wybor", "Wybor Serwera", nullptr));
        lineEditIP->setInputMask(QString());
        lineEditIP->setText(QCoreApplication::translate("wybor", "127.0.0.1", nullptr));
        lineEditIP->setPlaceholderText(QCoreApplication::translate("wybor", "server ip", nullptr));
        PushConnect->setText(QCoreApplication::translate("wybor", "Connect to Server", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(IpSetter), QCoreApplication::translate("wybor", "Wpisywanie r\304\231czne", nullptr));
        nickEdit->setPlaceholderText(QCoreApplication::translate("wybor", "nick", nullptr));
        label->setText(QCoreApplication::translate("wybor", "<html><head/><body><p>Available games list:</p></body></html>", nullptr));
        refresh->setText(QCoreApplication::translate("wybor", "Refresh", nullptr));
        newRoom->setText(QCoreApplication::translate("wybor", "New Room", nullptr));
        GameButton->setText(QCoreApplication::translate("wybor", "Connect to game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wybor: public Ui_wybor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYBOR_H

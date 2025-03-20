/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QLineEdit *loginUsername;
    QLineEdit *loginPassword;
    QPushButton *loginButton;
    QPushButton *switchToRegister;
    QWidget *page_2;
    QLineEdit *registerUsername;
    QLineEdit *confirmPassword;
    QLineEdit *registerPassword;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(180, 70, 341, 241));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        page_1->setMinimumSize(QSize(341, 241));
        loginUsername = new QLineEdit(page_1);
        loginUsername->setObjectName(QString::fromUtf8("loginUsername"));
        loginUsername->setGeometry(QRect(60, 40, 113, 20));
        loginPassword = new QLineEdit(page_1);
        loginPassword->setObjectName(QString::fromUtf8("loginPassword"));
        loginPassword->setGeometry(QRect(60, 90, 113, 20));
        loginButton = new QPushButton(page_1);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(50, 160, 56, 18));
        loginButton->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}"));
        switchToRegister = new QPushButton(page_1);
        switchToRegister->setObjectName(QString::fromUtf8("switchToRegister"));
        switchToRegister->setGeometry(QRect(140, 160, 56, 18));
        switchToRegister->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}"));
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        registerUsername = new QLineEdit(page_2);
        registerUsername->setObjectName(QString::fromUtf8("registerUsername"));
        registerUsername->setGeometry(QRect(40, 40, 113, 20));
        confirmPassword = new QLineEdit(page_2);
        confirmPassword->setObjectName(QString::fromUtf8("confirmPassword"));
        confirmPassword->setGeometry(QRect(50, 90, 113, 20));
        registerPassword = new QLineEdit(page_2);
        registerPassword->setObjectName(QString::fromUtf8("registerPassword"));
        registerPassword->setGeometry(QRect(60, 130, 113, 20));
        pushButton = new QPushButton(page_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 190, 56, 18));
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\205\245", nullptr));
        switchToRegister->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

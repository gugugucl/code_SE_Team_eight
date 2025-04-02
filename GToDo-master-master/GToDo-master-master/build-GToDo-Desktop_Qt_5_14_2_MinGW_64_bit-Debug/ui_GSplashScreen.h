/********************************************************************************
** Form generated from reading UI file 'GSplashScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSPLASHSCREEN_H
#define UI_GSPLASHSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GSplashScreen
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QLabel *Startlabel_1;
    QLabel *label_5;
    QLabel *Slabel_title_2;
    QLabel *Slabel_title;
    QWidget *page_2;
    QLabel *Startlabel_2;
    QLabel *Slabel_title_4;
    QLabel *Slabel_title_3;
    QLabel *label_7;
    QWidget *page_3;
    QLabel *Startlabel_3;
    QLabel *Slabel_title_6;
    QLabel *label_10;
    QLabel *Slabel_title_5;
    QPushButton *INkown;
    QPushButton *pushButton_2;
    QPushButton *pushButton_1;
    QPushButton *pushButton_3;
    QPushButton *Start_logo;
    QLabel *label_time;
    QLabel *label;
    QPushButton *INkown_close;

    void setupUi(QWidget *GSplashScreen)
    {
        if (GSplashScreen->objectName().isEmpty())
            GSplashScreen->setObjectName(QString::fromUtf8("GSplashScreen"));
        GSplashScreen->resize(832, 472);
        stackedWidget = new QStackedWidget(GSplashScreen);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 50, 811, 411));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        Startlabel_1 = new QLabel(page_1);
        Startlabel_1->setObjectName(QString::fromUtf8("Startlabel_1"));
        Startlabel_1->setGeometry(QRect(410, 0, 360, 340));
        Startlabel_1->setPixmap(QPixmap(QString::fromUtf8(":/bg/b.png")));
        Startlabel_1->setScaledContents(true);
        label_5 = new QLabel(page_1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 220, 331, 81));
        label_5->setWordWrap(true);
        Slabel_title_2 = new QLabel(page_1);
        Slabel_title_2->setObjectName(QString::fromUtf8("Slabel_title_2"));
        Slabel_title_2->setGeometry(QRect(80, 130, 491, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font.setPointSize(18);
        Slabel_title_2->setFont(font);
        Slabel_title = new QLabel(page_1);
        Slabel_title->setObjectName(QString::fromUtf8("Slabel_title"));
        Slabel_title->setGeometry(QRect(80, 170, 491, 71));
        Slabel_title->setFont(font);
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        Startlabel_2 = new QLabel(page_2);
        Startlabel_2->setObjectName(QString::fromUtf8("Startlabel_2"));
        Startlabel_2->setGeometry(QRect(430, 10, 360, 340));
        Startlabel_2->setPixmap(QPixmap(QString::fromUtf8(":/bg/a.png")));
        Startlabel_2->setScaledContents(true);
        Slabel_title_4 = new QLabel(page_2);
        Slabel_title_4->setObjectName(QString::fromUtf8("Slabel_title_4"));
        Slabel_title_4->setGeometry(QRect(80, 170, 371, 71));
        Slabel_title_4->setFont(font);
        Slabel_title_3 = new QLabel(page_2);
        Slabel_title_3->setObjectName(QString::fromUtf8("Slabel_title_3"));
        Slabel_title_3->setGeometry(QRect(80, 130, 371, 51));
        Slabel_title_3->setFont(font);
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(80, 220, 341, 81));
        label_7->setWordWrap(true);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        Startlabel_3 = new QLabel(page_3);
        Startlabel_3->setObjectName(QString::fromUtf8("Startlabel_3"));
        Startlabel_3->setGeometry(QRect(430, 10, 360, 340));
        Startlabel_3->setPixmap(QPixmap(QString::fromUtf8(":/bg/c.png")));
        Startlabel_3->setScaledContents(true);
        Slabel_title_6 = new QLabel(page_3);
        Slabel_title_6->setObjectName(QString::fromUtf8("Slabel_title_6"));
        Slabel_title_6->setGeometry(QRect(80, 170, 331, 71));
        Slabel_title_6->setFont(font);
        label_10 = new QLabel(page_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(80, 220, 381, 81));
        label_10->setWordWrap(true);
        Slabel_title_5 = new QLabel(page_3);
        Slabel_title_5->setObjectName(QString::fromUtf8("Slabel_title_5"));
        Slabel_title_5->setGeometry(QRect(80, 130, 331, 51));
        Slabel_title_5->setFont(font);
        stackedWidget->addWidget(page_3);
        INkown = new QPushButton(GSplashScreen);
        INkown->setObjectName(QString::fromUtf8("INkown"));
        INkown->setGeometry(QRect(533, 350, 141, 40));
        INkown->setMinimumSize(QSize(0, 0));
        INkown->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2 = new QPushButton(GSplashScreen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 370, 16, 16));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_1 = new QPushButton(GSplashScreen);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(80, 370, 16, 16));
        pushButton_1->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_3 = new QPushButton(GSplashScreen);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(140, 370, 16, 16));
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        Start_logo = new QPushButton(GSplashScreen);
        Start_logo->setObjectName(QString::fromUtf8("Start_logo"));
        Start_logo->setGeometry(QRect(80, 60, 80, 80));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        Start_logo->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Start_logo->setIcon(icon);
        Start_logo->setIconSize(QSize(80, 80));
        label_time = new QLabel(GSplashScreen);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(560, 354, 32, 32));
        label = new QLabel(GSplashScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(355, 120, 480, 280));
        label->setLineWidth(0);
        label->setPixmap(QPixmap(QString::fromUtf8(":/bg/wbg.png")));
        INkown_close = new QPushButton(GSplashScreen);
        INkown_close->setObjectName(QString::fromUtf8("INkown_close"));
        INkown_close->setGeometry(QRect(678, 350, 40, 40));
        INkown_close->setMinimumSize(QSize(0, 0));
        INkown_close->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        INkown_close->setIcon(icon1);
        label->raise();
        stackedWidget->raise();
        INkown->raise();
        pushButton_2->raise();
        pushButton_1->raise();
        pushButton_3->raise();
        Start_logo->raise();
        label_time->raise();
        INkown_close->raise();

        retranslateUi(GSplashScreen);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GSplashScreen);
    } // setupUi

    void retranslateUi(QWidget *GSplashScreen)
    {
        GSplashScreen->setWindowTitle(QCoreApplication::translate("GSplashScreen", "Form", nullptr));
        Startlabel_1->setText(QString());
        label_5->setText(QCoreApplication::translate("GSplashScreen", "<html><head/><body><p>\344\273\216\346\255\244\345\221\212\345\210\253\346\213\226\345\273\266\345\222\214\345\277\230\350\256\260\357\274\201\344\277\235\346\214\201\351\253\230\346\225\210\345\222\214\346\270\205\346\231\260\347\232\204\345\244\264\350\204\221\343\200\202</p></body></html>", nullptr));
        Slabel_title_2->setText(QCoreApplication::translate("GSplashScreen", "\346\254\242\350\277\216\344\275\277\347\224\250\357\274\201", nullptr));
        Slabel_title->setText(QCoreApplication::translate("GSplashScreen", "QTDO\345\276\205\345\212\236\344\270\223\345\256\266", nullptr));
        Startlabel_2->setText(QString());
        Slabel_title_4->setText(QCoreApplication::translate("GSplashScreen", "\350\256\251\344\275\240\350\275\273\346\235\276\347\256\241\347\220\206", nullptr));
        Slabel_title_3->setText(QCoreApplication::translate("GSplashScreen", "\351\253\230\346\225\210\347\233\256\346\240\207", nullptr));
        label_7->setText(QCoreApplication::translate("GSplashScreen", "<html><head/><body><p>\345\210\233\345\273\272\350\207\252\345\267\261\347\232\204\344\272\213\351\241\271\346\270\205\345\215\225\357\274\214\345\256\211\346\216\222\345\245\275\346\257\217\344\270\200\345\244\251\347\232\204\344\273\267\345\200\274\357\274\201</p></body></html>", nullptr));
        Startlabel_3->setText(QString());
        Slabel_title_6->setText(QCoreApplication::translate("GSplashScreen", "\346\212\244\344\275\240\344\276\277\346\215\267\350\264\264\345\277\203", nullptr));
        label_10->setText(QCoreApplication::translate("GSplashScreen", "<html><head/><body><p>\350\256\251\346\202\250\347\232\204\347\224\237\346\264\273\346\233\264\345\212\240\346\234\211\346\235\241\344\270\215\347\264\212\357\274\201\350\256\251\346\202\250\347\232\204\345\267\245\344\275\234\346\225\210\347\216\207\347\277\273\345\200\215\343\200\202</p></body></html>", nullptr));
        Slabel_title_5->setText(QCoreApplication::translate("GSplashScreen", "\345\210\260\347\202\271\346\217\220\351\206\222", nullptr));
#if QT_CONFIG(tooltip)
        INkown->setToolTip(QCoreApplication::translate("GSplashScreen", "\344\270\215\347\255\211\345\276\205\357\274\214\347\253\213\345\215\263\345\211\215\345\276\200", nullptr));
#endif // QT_CONFIG(tooltip)
        INkown->setText(QCoreApplication::translate("GSplashScreen", "      \345\211\215\345\276\200 >", nullptr));
        pushButton_2->setText(QString());
        pushButton_1->setText(QString());
        pushButton_3->setText(QString());
#if QT_CONFIG(tooltip)
        Start_logo->setToolTip(QCoreApplication::translate("GSplashScreen", "GTDO\345\276\205\345\212\236\344\270\223\345\256\266", nullptr));
#endif // QT_CONFIG(tooltip)
        Start_logo->setText(QString());
        label_time->setText(QString());
        label->setText(QString());
#if QT_CONFIG(tooltip)
        INkown_close->setToolTip(QCoreApplication::translate("GSplashScreen", "\345\217\226\346\266\210\347\255\211\345\276\205\357\274\214\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
#endif // QT_CONFIG(tooltip)
        INkown_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GSplashScreen: public Ui_GSplashScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSPLASHSCREEN_H

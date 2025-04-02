/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start;
    QPushButton *pushButton_rest;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_setting;
    QPushButton *pushButton_hide;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(280, 163);
        Widget->setMaximumSize(QSize(280, 16777215));
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMaximumSize(QSize(300, 16777215));
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setDigitCount(5);
        lcdNumber->setMode(QLCDNumber::Dec);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber->setProperty("value", QVariant(0.000000000000000));
        lcdNumber->setProperty("intValue", QVariant(0));

        verticalLayout->addWidget(lcdNumber);

        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 5));
        progressBar->setMaximumSize(QSize(16777215, 5));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_start = new QPushButton(Widget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton_start);

        pushButton_rest = new QPushButton(Widget);
        pushButton_rest->setObjectName(QString::fromUtf8("pushButton_rest"));
        pushButton_rest->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton_rest);

        pushButton_reset = new QPushButton(Widget);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));
        pushButton_reset->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton_reset);

        pushButton_setting = new QPushButton(Widget);
        pushButton_setting->setObjectName(QString::fromUtf8("pushButton_setting"));
        pushButton_setting->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton_setting);

        pushButton_hide = new QPushButton(Widget);
        pushButton_hide->setObjectName(QString::fromUtf8("pushButton_hide"));
        pushButton_hide->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton_hide);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_start->setText(QCoreApplication::translate("Widget", "\345\267\245\344\275\234", nullptr));
        pushButton_rest->setText(QCoreApplication::translate("Widget", "\344\274\221\346\201\257", nullptr));
        pushButton_reset->setText(QCoreApplication::translate("Widget", "\351\207\215\347\275\256", nullptr));
        pushButton_setting->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        pushButton_hide->setText(QCoreApplication::translate("Widget", "\346\265\256\347\252\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

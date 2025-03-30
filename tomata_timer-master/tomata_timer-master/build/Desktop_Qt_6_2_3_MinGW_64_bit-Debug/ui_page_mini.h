/********************************************************************************
** Form generated from reading UI file 'page_mini.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_MINI_H
#define UI_PAGE_MINI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PageMini
{
public:
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber;
    QGridLayout *gridLayout;
    QPushButton *pushButton_work;
    QPushButton *pushButton_rest;
    QPushButton *pushButton_normal;
    QPushButton *pushButton_close;

    void setupUi(QDialog *PageMini)
    {
        if (PageMini->objectName().isEmpty())
            PageMini->setObjectName(QString::fromUtf8("PageMini"));
        PageMini->resize(194, 55);
        horizontalLayout = new QHBoxLayout(PageMini);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        lcdNumber = new QLCDNumber(PageMini);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        horizontalLayout->addWidget(lcdNumber);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setVerticalSpacing(3);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        pushButton_work = new QPushButton(PageMini);
        pushButton_work->setObjectName(QString::fromUtf8("pushButton_work"));
        pushButton_work->setMinimumSize(QSize(25, 25));
        pushButton_work->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(pushButton_work, 0, 0, 1, 1);

        pushButton_rest = new QPushButton(PageMini);
        pushButton_rest->setObjectName(QString::fromUtf8("pushButton_rest"));
        pushButton_rest->setMinimumSize(QSize(25, 25));
        pushButton_rest->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(pushButton_rest, 0, 1, 1, 1);

        pushButton_normal = new QPushButton(PageMini);
        pushButton_normal->setObjectName(QString::fromUtf8("pushButton_normal"));
        pushButton_normal->setMinimumSize(QSize(25, 25));
        pushButton_normal->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(pushButton_normal, 1, 0, 1, 1);

        pushButton_close = new QPushButton(PageMini);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setMinimumSize(QSize(25, 25));
        pushButton_close->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(pushButton_close, 1, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnMinimumWidth(0, 1);
        gridLayout->setColumnMinimumWidth(1, 1);
        gridLayout->setRowMinimumHeight(0, 1);
        gridLayout->setRowMinimumHeight(1, 1);

        horizontalLayout->addLayout(gridLayout);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(PageMini);

        QMetaObject::connectSlotsByName(PageMini);
    } // setupUi

    void retranslateUi(QDialog *PageMini)
    {
        PageMini->setWindowTitle(QCoreApplication::translate("PageMini", "Dialog", nullptr));
        pushButton_work->setText(QString());
        pushButton_rest->setText(QString());
        pushButton_normal->setText(QString());
        pushButton_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PageMini: public Ui_PageMini {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_MINI_H

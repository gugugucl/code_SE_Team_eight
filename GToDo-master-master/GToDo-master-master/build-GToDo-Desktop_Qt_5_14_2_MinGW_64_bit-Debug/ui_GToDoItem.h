/********************************************************************************
** Form generated from reading UI file 'GToDoItem.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GTODOITEM_H
#define UI_GTODOITEM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GToDoitem
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *lbIcon;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *lbTitle;
    QPushButton *pushButton_icon;
    QHBoxLayout *horizontalLayout;
    QLabel *lbDdl;
    QLabel *lbRepate;
    QLabel *lbRemind;
    QLabel *lbCrontab;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_download;
    QPushButton *pushButton_del;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnAlter;
    QVBoxLayout *verticalLayout;
    QPushButton *btnFinish;

    void setupUi(QWidget *GToDoitem)
    {
        if (GToDoitem->objectName().isEmpty())
            GToDoitem->setObjectName(QString::fromUtf8("GToDoitem"));
        GToDoitem->setWindowModality(Qt::NonModal);
        GToDoitem->resize(566, 70);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GToDoitem->sizePolicy().hasHeightForWidth());
        GToDoitem->setSizePolicy(sizePolicy);
        GToDoitem->setMinimumSize(QSize(0, 70));
        GToDoitem->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_3 = new QHBoxLayout(GToDoitem);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 2, -1, 2);
        lbIcon = new QPushButton(GToDoitem);
        lbIcon->setObjectName(QString::fromUtf8("lbIcon"));
        lbIcon->setMinimumSize(QSize(50, 55));
        lbIcon->setMaximumSize(QSize(55, 55));
        lbIcon->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/Finished.png"), QSize(), QIcon::Normal, QIcon::Off);
        lbIcon->setIcon(icon);
        lbIcon->setIconSize(QSize(40, 40));

        horizontalLayout_7->addWidget(lbIcon);


        horizontalLayout_3->addLayout(horizontalLayout_7);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 4, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(4, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lbTitle = new QPushButton(GToDoitem);
        lbTitle->setObjectName(QString::fromUtf8("lbTitle"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        lbTitle->setFont(font);
        lbTitle->setCursor(QCursor(Qt::PointingHandCursor));
        lbTitle->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(lbTitle);

        pushButton_icon = new QPushButton(GToDoitem);
        pushButton_icon->setObjectName(QString::fromUtf8("pushButton_icon"));

        horizontalLayout_2->addWidget(pushButton_icon);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        lbDdl = new QLabel(GToDoitem);
        lbDdl->setObjectName(QString::fromUtf8("lbDdl"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbDdl->sizePolicy().hasHeightForWidth());
        lbDdl->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lbDdl);

        lbRepate = new QLabel(GToDoitem);
        lbRepate->setObjectName(QString::fromUtf8("lbRepate"));
        sizePolicy1.setHeightForWidth(lbRepate->sizePolicy().hasHeightForWidth());
        lbRepate->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lbRepate);

        lbRemind = new QLabel(GToDoitem);
        lbRemind->setObjectName(QString::fromUtf8("lbRemind"));
        sizePolicy1.setHeightForWidth(lbRemind->sizePolicy().hasHeightForWidth());
        lbRemind->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lbRemind);

        lbCrontab = new QLabel(GToDoitem);
        lbCrontab->setObjectName(QString::fromUtf8("lbCrontab"));

        horizontalLayout->addWidget(lbCrontab);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout->setLayout(1, QFormLayout::SpanningRole, horizontalLayout);


        horizontalLayout_3->addLayout(formLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_download = new QPushButton(GToDoitem);
        pushButton_download->setObjectName(QString::fromUtf8("pushButton_download"));
        pushButton_download->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_download->setIcon(icon1);

        horizontalLayout_6->addWidget(pushButton_download);


        horizontalLayout_5->addLayout(horizontalLayout_6);

        pushButton_del = new QPushButton(GToDoitem);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_del->setIcon(icon2);

        horizontalLayout_5->addWidget(pushButton_del);


        horizontalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnAlter = new QPushButton(GToDoitem);
        btnAlter->setObjectName(QString::fromUtf8("btnAlter"));
        btnAlter->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/write.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAlter->setIcon(icon3);

        horizontalLayout_4->addWidget(btnAlter);


        horizontalLayout_3->addLayout(horizontalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnFinish = new QPushButton(GToDoitem);
        btnFinish->setObjectName(QString::fromUtf8("btnFinish"));
        btnFinish->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFinish->setIcon(icon4);

        verticalLayout->addWidget(btnFinish);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(GToDoitem);

        QMetaObject::connectSlotsByName(GToDoitem);
    } // setupUi

    void retranslateUi(QWidget *GToDoitem)
    {
        GToDoitem->setWindowTitle(QString());
        lbIcon->setText(QString());
        lbTitle->setText(QCoreApplication::translate("GToDoitem", "\344\272\213\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_icon->setToolTip(QCoreApplication::translate("GToDoitem", "\346\211\247\350\241\214\350\207\252\345\212\250\344\273\273\345\212\241", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_icon->setText(QString());
#if QT_CONFIG(tooltip)
        lbDdl->setToolTip(QCoreApplication::translate("GToDoitem", "\350\256\276\347\275\256\347\232\204\346\210\252\346\255\242\346\227\245\346\234\237", nullptr));
#endif // QT_CONFIG(tooltip)
        lbDdl->setText(QCoreApplication::translate("GToDoitem", "\346\227\240\346\210\252\346\255\242\346\227\266\351\227\264", nullptr));
#if QT_CONFIG(tooltip)
        lbRepate->setToolTip(QCoreApplication::translate("GToDoitem", "\350\256\276\347\275\256\347\232\204\351\207\215\345\244\215\345\221\250\346\234\237", nullptr));
#endif // QT_CONFIG(tooltip)
        lbRepate->setText(QCoreApplication::translate("GToDoitem", "\344\270\215\351\207\215\345\244\215", nullptr));
#if QT_CONFIG(tooltip)
        lbRemind->setToolTip(QCoreApplication::translate("GToDoitem", "\350\256\276\347\275\256\347\232\204\346\217\220\351\206\222\346\227\266\351\227\264", nullptr));
#endif // QT_CONFIG(tooltip)
        lbRemind->setText(QCoreApplication::translate("GToDoitem", "\346\234\252\350\256\276\347\275\256\346\217\220\351\206\222", nullptr));
#if QT_CONFIG(tooltip)
        lbCrontab->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        lbCrontab->setText(QCoreApplication::translate("GToDoitem", "\346\234\252\345\220\257\347\224\250", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_download->setToolTip(QCoreApplication::translate("GToDoitem", "\344\270\213\350\275\275\350\257\245\350\256\260\345\275\225\357\274\214\346\224\257\346\214\201DOC\343\200\201RTF\343\200\201TXT\346\226\207\346\241\243\347\261\273\345\236\213", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_download->setText(QString());
#if QT_CONFIG(tooltip)
        pushButton_del->setToolTip(QCoreApplication::translate("GToDoitem", "\345\210\240\351\231\244\350\257\245\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pushButton_del->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pushButton_del->setText(QString());
#if QT_CONFIG(tooltip)
        btnAlter->setToolTip(QCoreApplication::translate("GToDoitem", "\347\274\226\350\276\221\345\206\205\345\256\271\350\257\246\346\203\205", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        btnAlter->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        btnAlter->setText(QString());
#if QT_CONFIG(tooltip)
        btnFinish->setToolTip(QCoreApplication::translate("GToDoitem", "\346\240\207\346\263\250\344\270\272\345\267\262\345\256\214\346\210\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        btnFinish->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        btnFinish->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GToDoitem: public Ui_GToDoitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GTODOITEM_H

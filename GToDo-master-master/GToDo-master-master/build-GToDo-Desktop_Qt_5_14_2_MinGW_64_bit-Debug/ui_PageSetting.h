/********************************************************************************
** Form generated from reading UI file 'PageSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGESETTING_H
#define UI_PAGESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PageSetting
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcdNumbe_work_tim;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_work_tim_add;
    QPushButton *pushButton_work_tim_reduce;
    QSlider *horizontalSlider_work_tim;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *lcdNumber_rest_tim;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_rest_tim_add;
    QPushButton *pushButton_rest_tim_reduce;
    QSlider *horizontalSlider_rest_tim;
    QLabel *label_3;
    QSlider *horizontalSlider_transparency;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancle;

    void setupUi(QDialog *PageSetting)
    {
        if (PageSetting->objectName().isEmpty())
            PageSetting->setObjectName(QString::fromUtf8("PageSetting"));
        PageSetting->resize(260, 364);
        verticalLayout_3 = new QVBoxLayout(PageSetting);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(PageSetting);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lcdNumbe_work_tim = new QLCDNumber(PageSetting);
        lcdNumbe_work_tim->setObjectName(QString::fromUtf8("lcdNumbe_work_tim"));

        horizontalLayout_2->addWidget(lcdNumbe_work_tim);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_work_tim_add = new QPushButton(PageSetting);
        pushButton_work_tim_add->setObjectName(QString::fromUtf8("pushButton_work_tim_add"));
        pushButton_work_tim_add->setMinimumSize(QSize(50, 30));
        pushButton_work_tim_add->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(pushButton_work_tim_add);

        pushButton_work_tim_reduce = new QPushButton(PageSetting);
        pushButton_work_tim_reduce->setObjectName(QString::fromUtf8("pushButton_work_tim_reduce"));
        pushButton_work_tim_reduce->setMinimumSize(QSize(50, 30));
        pushButton_work_tim_reduce->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(pushButton_work_tim_reduce);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalSlider_work_tim = new QSlider(PageSetting);
        horizontalSlider_work_tim->setObjectName(QString::fromUtf8("horizontalSlider_work_tim"));
        horizontalSlider_work_tim->setMaximum(3600);
        horizontalSlider_work_tim->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_work_tim);

        label_2 = new QLabel(PageSetting);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lcdNumber_rest_tim = new QLCDNumber(PageSetting);
        lcdNumber_rest_tim->setObjectName(QString::fromUtf8("lcdNumber_rest_tim"));

        horizontalLayout_3->addWidget(lcdNumber_rest_tim);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_rest_tim_add = new QPushButton(PageSetting);
        pushButton_rest_tim_add->setObjectName(QString::fromUtf8("pushButton_rest_tim_add"));
        pushButton_rest_tim_add->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_add->setMaximumSize(QSize(50, 50));

        verticalLayout_2->addWidget(pushButton_rest_tim_add);

        pushButton_rest_tim_reduce = new QPushButton(PageSetting);
        pushButton_rest_tim_reduce->setObjectName(QString::fromUtf8("pushButton_rest_tim_reduce"));
        pushButton_rest_tim_reduce->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_reduce->setMaximumSize(QSize(50, 50));

        verticalLayout_2->addWidget(pushButton_rest_tim_reduce);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 5);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalSlider_rest_tim = new QSlider(PageSetting);
        horizontalSlider_rest_tim->setObjectName(QString::fromUtf8("horizontalSlider_rest_tim"));
        horizontalSlider_rest_tim->setMaximum(1200);
        horizontalSlider_rest_tim->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_rest_tim);

        label_3 = new QLabel(PageSetting);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        horizontalSlider_transparency = new QSlider(PageSetting);
        horizontalSlider_transparency->setObjectName(QString::fromUtf8("horizontalSlider_transparency"));
        horizontalSlider_transparency->setMaximum(100);
        horizontalSlider_transparency->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_transparency);

        line = new QFrame(PageSetting);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_save = new QPushButton(PageSetting);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_cancle = new QPushButton(PageSetting);
        pushButton_cancle->setObjectName(QString::fromUtf8("pushButton_cancle"));

        horizontalLayout->addWidget(pushButton_cancle);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(PageSetting);

        QMetaObject::connectSlotsByName(PageSetting);
    } // setupUi

    void retranslateUi(QDialog *PageSetting)
    {
        PageSetting->setWindowTitle(QCoreApplication::translate("PageSetting", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("PageSetting", "\345\267\245\344\275\234\346\227\266\351\227\264\357\274\232", nullptr));
        pushButton_work_tim_add->setText(QCoreApplication::translate("PageSetting", "+", nullptr));
        pushButton_work_tim_reduce->setText(QCoreApplication::translate("PageSetting", "-", nullptr));
        label_2->setText(QCoreApplication::translate("PageSetting", "\344\274\221\346\201\257\346\227\266\351\227\264\357\274\232", nullptr));
        pushButton_rest_tim_add->setText(QCoreApplication::translate("PageSetting", "+", nullptr));
        pushButton_rest_tim_reduce->setText(QCoreApplication::translate("PageSetting", "-", nullptr));
        label_3->setText(QCoreApplication::translate("PageSetting", "\351\200\217\346\230\216\345\272\246\357\274\232", nullptr));
        pushButton_save->setText(QCoreApplication::translate("PageSetting", "\344\277\235\345\255\230", nullptr));
        pushButton_cancle->setText(QCoreApplication::translate("PageSetting", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSetting: public Ui_PageSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGESETTING_H

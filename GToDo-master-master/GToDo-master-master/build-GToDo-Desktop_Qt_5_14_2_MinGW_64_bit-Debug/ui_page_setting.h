/********************************************************************************
** Form generated from reading UI file 'page_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_SETTING_H
#define UI_PAGE_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_page_setting
{
public:
    QSlider *horizontalSlider_work_tim;
    QLabel *label_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_save_3;
    QPushButton *pushButton_cancle_3;
    QFrame *line;
    QLabel *label_2;
    QSlider *horizontalSlider_transparency;
    QSlider *horizontalSlider_rest_tim;
    QLabel *label;
    QLCDNumber *lcdNumber_rest_tim_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton_rest_tim_add_3;
    QPushButton *pushButton_rest_tim_reduce_3;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButton_rest_tim_add_4;
    QPushButton *pushButton_rest_tim_reduce_4;
    QLCDNumber *lcdNumbe_work_tim_3;

    void setupUi(QWidget *page_setting)
    {
        if (page_setting->objectName().isEmpty())
            page_setting->setObjectName(QString::fromUtf8("page_setting"));
        page_setting->resize(259, 364);
        horizontalSlider_work_tim = new QSlider(page_setting);
        horizontalSlider_work_tim->setObjectName(QString::fromUtf8("horizontalSlider_work_tim"));
        horizontalSlider_work_tim->setGeometry(QRect(9, 126, 242, 15));
        horizontalSlider_work_tim->setMaximum(3600);
        horizontalSlider_work_tim->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(page_setting);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(9, 285, 242, 12));
        layoutWidget = new QWidget(page_setting);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 330, 168, 22));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        pushButton_save_3 = new QPushButton(layoutWidget);
        pushButton_save_3->setObjectName(QString::fromUtf8("pushButton_save_3"));

        horizontalLayout_7->addWidget(pushButton_save_3);

        pushButton_cancle_3 = new QPushButton(layoutWidget);
        pushButton_cancle_3->setObjectName(QString::fromUtf8("pushButton_cancle_3"));

        horizontalLayout_7->addWidget(pushButton_cancle_3);

        line = new QFrame(page_setting);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(9, 324, 242, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(page_setting);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(9, 147, 242, 12));
        horizontalSlider_transparency = new QSlider(page_setting);
        horizontalSlider_transparency->setObjectName(QString::fromUtf8("horizontalSlider_transparency"));
        horizontalSlider_transparency->setGeometry(QRect(9, 303, 242, 15));
        horizontalSlider_transparency->setMaximum(100);
        horizontalSlider_transparency->setOrientation(Qt::Horizontal);
        horizontalSlider_rest_tim = new QSlider(page_setting);
        horizontalSlider_rest_tim->setObjectName(QString::fromUtf8("horizontalSlider_rest_tim"));
        horizontalSlider_rest_tim->setGeometry(QRect(9, 264, 242, 15));
        horizontalSlider_rest_tim->setMaximum(1200);
        horizontalSlider_rest_tim->setOrientation(Qt::Horizontal);
        label = new QLabel(page_setting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 242, 12));
        lcdNumber_rest_tim_3 = new QLCDNumber(page_setting);
        lcdNumber_rest_tim_3->setObjectName(QString::fromUtf8("lcdNumber_rest_tim_3"));
        lcdNumber_rest_tim_3->setGeometry(QRect(10, 160, 182, 91));
        widget = new QWidget(page_setting);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(190, 160, 51, 91));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setSpacing(1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        pushButton_rest_tim_add_3 = new QPushButton(widget);
        pushButton_rest_tim_add_3->setObjectName(QString::fromUtf8("pushButton_rest_tim_add_3"));
        pushButton_rest_tim_add_3->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_add_3->setMaximumSize(QSize(50, 50));

        verticalLayout_6->addWidget(pushButton_rest_tim_add_3);

        pushButton_rest_tim_reduce_3 = new QPushButton(widget);
        pushButton_rest_tim_reduce_3->setObjectName(QString::fromUtf8("pushButton_rest_tim_reduce_3"));
        pushButton_rest_tim_reduce_3->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_reduce_3->setMaximumSize(QSize(50, 50));

        verticalLayout_6->addWidget(pushButton_rest_tim_reduce_3);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 1);
        layoutWidget_2 = new QWidget(page_setting);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(190, 30, 52, 91));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        pushButton_rest_tim_add_4 = new QPushButton(layoutWidget_2);
        pushButton_rest_tim_add_4->setObjectName(QString::fromUtf8("pushButton_rest_tim_add_4"));
        pushButton_rest_tim_add_4->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_add_4->setMaximumSize(QSize(50, 50));

        verticalLayout_7->addWidget(pushButton_rest_tim_add_4);

        pushButton_rest_tim_reduce_4 = new QPushButton(layoutWidget_2);
        pushButton_rest_tim_reduce_4->setObjectName(QString::fromUtf8("pushButton_rest_tim_reduce_4"));
        pushButton_rest_tim_reduce_4->setMinimumSize(QSize(50, 30));
        pushButton_rest_tim_reduce_4->setMaximumSize(QSize(50, 50));

        verticalLayout_7->addWidget(pushButton_rest_tim_reduce_4);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 1);
        lcdNumbe_work_tim_3 = new QLCDNumber(page_setting);
        lcdNumbe_work_tim_3->setObjectName(QString::fromUtf8("lcdNumbe_work_tim_3"));
        lcdNumbe_work_tim_3->setGeometry(QRect(10, 30, 182, 91));

        retranslateUi(page_setting);

        QMetaObject::connectSlotsByName(page_setting);
    } // setupUi

    void retranslateUi(QWidget *page_setting)
    {
        page_setting->setWindowTitle(QCoreApplication::translate("page_setting", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("page_setting", "\351\200\217\346\230\216\345\272\246\357\274\232", nullptr));
        pushButton_save_3->setText(QCoreApplication::translate("page_setting", "\344\277\235\345\255\230", nullptr));
        pushButton_cancle_3->setText(QCoreApplication::translate("page_setting", "\345\217\226\346\266\210", nullptr));
        label_2->setText(QCoreApplication::translate("page_setting", "\344\274\221\346\201\257\346\227\266\351\227\264\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("page_setting", "\345\267\245\344\275\234\346\227\266\351\227\264\357\274\232", nullptr));
        pushButton_rest_tim_add_3->setText(QCoreApplication::translate("page_setting", "+", nullptr));
        pushButton_rest_tim_reduce_3->setText(QCoreApplication::translate("page_setting", "-", nullptr));
        pushButton_rest_tim_add_4->setText(QCoreApplication::translate("page_setting", "+", nullptr));
        pushButton_rest_tim_reduce_4->setText(QCoreApplication::translate("page_setting", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class page_setting: public Ui_page_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_SETTING_H

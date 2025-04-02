/********************************************************************************
** Form generated from reading UI file 'GNotifyMessage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GNOTIFYMESSAGE_H
#define UI_GNOTIFYMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMessageNotification
{
public:
    QLabel *Notification_title;
    QLabel *Note_date;
    QPushButton *CloseOK;
    QPushButton *Close_pushButton_2;

    void setupUi(QWidget *QMessageNotification)
    {
        if (QMessageNotification->objectName().isEmpty())
            QMessageNotification->setObjectName(QString::fromUtf8("QMessageNotification"));
        QMessageNotification->resize(600, 120);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QMessageNotification->sizePolicy().hasHeightForWidth());
        QMessageNotification->setSizePolicy(sizePolicy);
        QMessageNotification->setMinimumSize(QSize(600, 120));
        QMessageNotification->setMaximumSize(QSize(600, 120));
        Notification_title = new QLabel(QMessageNotification);
        Notification_title->setObjectName(QString::fromUtf8("Notification_title"));
        Notification_title->setGeometry(QRect(120, 20, 311, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        Notification_title->setFont(font);
        Notification_title->setLineWidth(0);
        Note_date = new QLabel(QMessageNotification);
        Note_date->setObjectName(QString::fromUtf8("Note_date"));
        Note_date->setGeometry(QRect(120, 70, 201, 21));
        CloseOK = new QPushButton(QMessageNotification);
        CloseOK->setObjectName(QString::fromUtf8("CloseOK"));
        CloseOK->setGeometry(QRect(460, 33, 111, 51));
        CloseOK->setCursor(QCursor(Qt::PointingHandCursor));
        Close_pushButton_2 = new QPushButton(QMessageNotification);
        Close_pushButton_2->setObjectName(QString::fromUtf8("Close_pushButton_2"));
        Close_pushButton_2->setGeometry(QRect(10, 10, 100, 100));
        Close_pushButton_2->setIconSize(QSize(50, 50));

        retranslateUi(QMessageNotification);

        QMetaObject::connectSlotsByName(QMessageNotification);
    } // setupUi

    void retranslateUi(QWidget *QMessageNotification)
    {
        QMessageNotification->setWindowTitle(QCoreApplication::translate("QMessageNotification", "QWidget", nullptr));
        Notification_title->setText(QCoreApplication::translate("QMessageNotification", "\344\270\200\344\270\252\344\272\277\345\260\217\347\233\256\346\240\207", nullptr));
        Note_date->setText(QCoreApplication::translate("QMessageNotification", "\346\217\220\351\206\222\346\227\266\351\227\264\345\210\260\344\272\206", nullptr));
        CloseOK->setText(QCoreApplication::translate("QMessageNotification", "\346\210\221\347\237\245\351\201\223\344\272\206", nullptr));
        Close_pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QMessageNotification: public Ui_QMessageNotification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GNOTIFYMESSAGE_H

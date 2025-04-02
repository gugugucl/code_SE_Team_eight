/********************************************************************************
** Form generated from reading UI file 'GBtnRroup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GBTNRROUP_H
#define UI_GBTNRROUP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GBtnGroup
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *GBtnGroup)
    {
        if (GBtnGroup->objectName().isEmpty())
            GBtnGroup->setObjectName(QString::fromUtf8("GBtnGroup"));
        GBtnGroup->resize(200, 40);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GBtnGroup->sizePolicy().hasHeightForWidth());
        GBtnGroup->setSizePolicy(sizePolicy);
        GBtnGroup->setMinimumSize(QSize(0, 40));
        horizontalLayout_2 = new QHBoxLayout(GBtnGroup);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        pushButton = new QPushButton(GBtnGroup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 36));
        pushButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(GBtnGroup);

        QMetaObject::connectSlotsByName(GBtnGroup);
    } // setupUi

    void retranslateUi(QWidget *GBtnGroup)
    {
        GBtnGroup->setWindowTitle(QString());
#if QT_CONFIG(tooltip)
        pushButton->setToolTip(QCoreApplication::translate("GBtnGroup", "\345\217\214\345\207\273\345\217\257\347\274\226\350\276\221", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QCoreApplication::translate("GBtnGroup", "\347\273\204\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GBtnGroup: public Ui_GBtnGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GBTNRROUP_H

#include "widget.h"
#include "ui_widget.h"
#include "STDateWidget.h"
#include "STCalandarWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    calandar_ = new STCalandarWidget(this);
    connect(calandar_, SIGNAL(DateSelectSignal(QDate)), this, SLOT(HaveDateChose(QDate)));
    calandar_->show();
    calandar_->exec();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::HaveDateChose(QDate c_dates)
{
    //ui->dateedit->setDate(c_dates);
    calandar_->accepted();

    //


    calandar_->deleteLater();
}

#include "GSplashScreen.h"
#include "ui_GSplashScreen.h"
#include <QStackedWidget>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include "GToDo.h"
GSplashScreen::GSplashScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GSplashScreen)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint| Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    timer = new QTimer(this);
    m_nPageCount = ui->stackedWidget->count();
    m_nCurrentPage = ui->stackedWidget->currentIndex();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Startlabel_1,"geometry");
    animation->setDuration(800);
    animation->setStartValue(QRect(440, 40, 340, 320));
    animation->setEndValue(QRect(430, 10,360, 340));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(2000);

        timer2 = new QTimer(this);
        connect(timer2, SIGNAL(timeout()), this, SLOT(updateTime()));
        timer2->start(1000);

        endTime = QDateTime::currentDateTime().addSecs(1);

}
void GSplashScreen::updateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
       int secondsRemaining = currentTime.secsTo(endTime);

       if (secondsRemaining <= 0) {
           ui->label_time->setText(tr("0"));
           timer2->stop();
       } else {
          ui->label_time->setText(QString("<font color='red'>%1</font>").arg(secondsRemaining));
       }
}
void GSplashScreen::onTimer()
{
    m_nCurrentPage = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex((m_nCurrentPage + 1) % m_nPageCount);
    int index = ui->stackedWidget->currentIndex();
    QPropertyAnimation *animation = new QPropertyAnimation(ui->Startlabel_1,"geometry");
    animation->setDuration(800);
    animation->setStartValue(QRect(440, 40, 340, 320));
    animation->setEndValue(QRect(430, 10,360, 340));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->Startlabel_2,"geometry");
    animation2->setDuration(800);
    animation2->setStartValue(QRect(440, 40, 340, 320));
    animation2->setEndValue(QRect(430, 10,360, 340));
    animation2->setEasingCurve(QEasingCurve::InOutQuad);
    animation2->start();
    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->Startlabel_3,"geometry");
    animation3->setDuration(800);
    animation3->setStartValue(QRect(440, 40,340, 320));
    animation3->setEndValue(QRect(430, 10,360, 340));
    animation3->setEasingCurve(QEasingCurve::InOutQuad);
    animation3->start();

    static int count = 0;
    count++;
    if(count >= 15)
    {
        timer->stop();
        this->close();
        GToDo *w = new GToDo();
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        QPropertyAnimation *animation = new QPropertyAnimation(w,"windowOpacity");
        animation->setDuration(300);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->start();
        w->show();
    }
    switch (index)
    {
    case 0:
        ui->pushButton_1->setStyleSheet("background:#0ea80e;color:#ffffff;");
        ui->pushButton_2->setStyleSheet("");
        ui->pushButton_3->setStyleSheet("");
        break;
    case 1:
        ui->pushButton_1->setStyleSheet("");
        ui->pushButton_2->setStyleSheet("background:#0ea80e;color:#ffffff;");
        ui->pushButton_3->setStyleSheet("");
        break;
    case 2:
        ui->pushButton_1->setStyleSheet("");
        ui->pushButton_2->setStyleSheet("");
        ui->pushButton_3->setStyleSheet("background:#0ea80e;color:#ffffff;");
        break;
    default:
        break;
    }
}
void GSplashScreen::on_INkown_clicked()
{
    timer->stop();
    this->close();
    GToDo *w = new GToDo();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    QPropertyAnimation *animation = new QPropertyAnimation(w,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
    w->show();
}
void GSplashScreen::on_INkown_close_clicked(){
    qApp->quit();
}
void GSplashScreen::on_pushButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_1->setStyleSheet("background:#0ea80e;color:#ffffff;");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_3->setStyleSheet("");

}
void GSplashScreen::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_1->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("background:#0ea80e;color:#ffffff;");
    ui->pushButton_3->setStyleSheet("");
}
void GSplashScreen::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_1->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_3->setStyleSheet("background:#0ea80e;color:#ffffff;");
}
void GSplashScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPoint topLeft(10, 10);
    QSize size(width() - 20, height() - 20);
    QRectF rect(topLeft, size);

    QPainterPath path;
    path.addRoundedRect(rect, 10, 10);

    painter.setClipPath(path);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor color(0, 0, 0, 220);
    for (int i = 10; i > 0; i--)
    {
        QColor color(0, 0, 0, 30 - i * 3);
        painter.setPen(color);
        painter.setClipping(false);
        painter.drawRoundedRect(rect.adjusted(-i, -i, i, i), 10, 10);

        painter.setClipPath(path);
    }

    painter.fillRect(rect, Qt::white);
}

void GSplashScreen::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        mouseStartPoint = event->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void GSplashScreen::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        QPoint distance = event->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void GSplashScreen::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}
GSplashScreen::~GSplashScreen()
{
    timer2->stop();
    delete ui;
    delete timer;
}

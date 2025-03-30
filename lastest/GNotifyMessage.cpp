#include "GNotifyMessage.h"
#include "ui_GNotifyMessage.h"
#include <QPushButton>
#include <QDesktopWidget>
#include <QFontDatabase>
QFont loadCustomFont3(const QString &fontFilePath, qreal pointSize)
{
    static QHash<QString, QFont> loadedFonts;
    if (loadedFonts.contains(fontFilePath)) {
        return loadedFonts.value(fontFilePath);
    }
    int fontId = QFontDatabase::addApplicationFont(fontFilePath);

    if (fontId == -1) {
        return QFont();
    }
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, pointSize);
    loadedFonts.insert(fontFilePath, customFont);
    return customFont;
}

// 构造函数的实现
QMessageNotification::QMessageNotification(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::QMessageNotification)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

   // QFont customFont3 = loadCustomFont3(":/font/Aa.otf", 10);
   //   ui->Notification_title->setFont(customFont3);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->availableGeometry(desktop->primaryScreen());
    move(rect.width() - width() - 50, rect.height() - height() - 50);
}

void QMessageNotification::setNotificationTitle(QString title)
{
    ui->Notification_title->setText(title);
}

void QMessageNotification::setNotificationDate(QString ddlText)
{
    ui->Note_date->setText(ddlText);
}
void QMessageNotification::setNotificationIcon(QIcon lbIcon)
{
    ui->Close_pushButton_2->setIcon(lbIcon);
}
void QMessageNotification::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        mouseStartPoint = event->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void QMessageNotification::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        QPoint distance = event->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void QMessageNotification::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}
void QMessageNotification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPoint topLeft(10, 10);
    QSize size(width() - 20, height() - 20);
    QRectF rect(topLeft, size);

    QPainterPath path;
    path.addRoundedRect(rect, 0, 0);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor color(0, 0, 0, 220);
    for (int i = 10; i > 0; i--)
    {
        QColor color(0, 0, 0, 30 - i * 3);
        painter.setPen(color);
        painter.setClipping(false);
        painter.drawRoundedRect(rect.adjusted(-i, -i, i, i), 0, 0);

        painter.setClipPath(path);
    }

    painter.fillRect(rect, Qt::white);
}
QMessageNotification::~QMessageNotification()
{
    delete ui;
}

void QMessageNotification::on_CloseOK_clicked()
{
    close();
}

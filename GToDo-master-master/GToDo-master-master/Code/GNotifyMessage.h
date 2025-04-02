#ifndef QMESSAGENOTIFICATION_H
#define QMESSAGENOTIFICATION_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QPixmap>
#include <QMouseEvent>
#include<GToDoItem.h>
namespace Ui {
class QMessageNotification;
}

class QMessageNotification : public QWidget
{
    Q_OBJECT

public:
  explicit QMessageNotification(QWidget *parent);
    ~QMessageNotification();
    void closeDialog();

    // 在QMessageNotification类的头文件中添加下面这个函数。
    public:
    void setNotificationTitle(QString title);
    void setNotificationDate(QString ddlText);
  void setNotificationIcon(QIcon lbIcon);
protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_CloseOK_clicked();
private:
    Ui::QMessageNotification *ui;
    QLabel *TitleLabel;
    bool       m_bDrag;
    QPoint     mouseStartPoint;
    QPoint     windowTopLeftPoint;
    QPoint     last;
};

#endif // QMESSAGENOTIFICATION_H

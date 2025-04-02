void on_pushButton_download_clicked();
void on_lbTitle_clicked();
void on_pushButton_del_clicked();
#ifndef _GTODOITEM_H_
#define _GTODOITEM_H_
#include <QWidget>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include "GQstringDate.h"
#include <QMouseEvent>
#include<QPainter>
#include<GNotifyMessage.h>
class QMessageNotification;
namespace Ui {
class GToDoitem;
}

class GToDoitem : public QWidget
{
    Q_OBJECT

public:
    explicit GToDoitem(QWidget *parent = 0);
    ~GToDoitem();
    void setTitle(QString Title,int priority = 0);
    void setDDL(QString date);
    void setRepeat(int Repeat);
    void setCrontab(int Crontab);
    void setRemind(QString datetime);
    void setFinishDate(QString date);
    void hideBtn();
    void deleteTask();
private slots:
    void on_btnFinish_clicked();
    void on_btnAlter_clicked();
    void on_lbIcon_clicked();
    void on_lbTitle_clicked();
    void on_pushButton_download_clicked();
    void sltShowPopMenu(const QPoint& );
    void on_pushButton_del_clicked();

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setPen(QColor(0, 0, 0, 10));
        painter.drawLine(0, height() - 1, width(), height() - 1);
    }
signals:
    void showSettingPanel(QString Title,QString Deadline);

private:
    Ui::GToDoitem *ui;
    QString m_ddl;//截止日期
    int m_priority;//优先级
    int m_repeat;//重复次数
    int m_Crontab;
    void init();
    QMenu *popMenu;
    QMessageNotification *notificationDialog;
    QWidget *m_parent;
};
#endif

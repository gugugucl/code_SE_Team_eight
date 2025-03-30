#ifndef GSPLASHSCREEN_H
#define GSPLASHSCREEN_H
#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QDateTime>
#include <QPropertyAnimation>
namespace Ui {
    class GSplashScreen;
}

class GSplashScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit GSplashScreen(QWidget *parent = nullptr);
    ~GSplashScreen();

private slots:
    void onTimer();
    void on_INkown_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void updateTime(); // 更新倒计时
    void on_INkown_close_clicked();

private:
    Ui::GSplashScreen *ui;
    QTimer *timer;
    QTimer *timer2; // 倒计时定时器
    QDateTime endTime; // 倒计时结束时间
    bool m_bDrag;
    QPoint mouseStartPoint;
    QPoint windowTopLeftPoint;
    int m_nCurrentPage;
    int m_nPageCount;
};

#endif

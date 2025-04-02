#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include "PageSetting.h"
#include "page_mini.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum MODE
    {
        MODE_WORK,
        MODE_REST,
    };

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    int m_work_time_sec;
    int m_rest_time_sec;
    int m_clock_point;

    int m_widget_tran;

    int m_timer_set_cnt;
    int m_timer_cnt;

    PageMini * m_page_mini = nullptr;

    QTimer * m_timer = nullptr;

    enum MODE m_work_mode = MODE_WORK;

    QSystemTrayIcon * m_tray_icon  = nullptr;
    QMenu   * m_menu               = nullptr;
    QAction * m_mini_size_action   = nullptr;
    QAction * m_max_size_action    = nullptr;
    QAction * m_restore_win_action = nullptr;
    QAction * m_quit_action        = nullptr;


private:
    void styleInit(void);
    void showLcdTime(int time_stamp, bool show_point);
    void readSetting(int & work_tim, int & rest_tim, int & tran);

    void createTrayMenu();
    void createTrayIcon();

    void createMiniPage(void);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_timeout_callback(void);
    void slot_update_timer(void);
    void slot_update_widget(int);
    void slot_tray_msg_clicked(void);

    void slot_icon_activated(QSystemTrayIcon::ActivationReason reason);

    void slot_start_work(void);
    void slot_start_rest(void);

    void on_pushButton_start_clicked();
    void on_pushButton_rest_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_setting_clicked();
    void on_pushButton_hide_clicked();

signals:
    void signal_update_mini_page(int time_stamp, bool show_point);

    void signal_start_work(void);
    void signal_start_rest(void);
};
#endif // WIDGET_H

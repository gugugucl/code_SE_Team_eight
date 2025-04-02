#include "widget.h"
#include "ui_widget.h"

#include <algorithm>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QSystemTrayIcon>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle(QStringLiteral("番茄时钟"));

    this->readSetting(this->m_work_time_sec, this->m_rest_time_sec, this->m_widget_tran);

    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_WState_WindowOpacitySet);

    this->m_timer_cnt = 0;
    this->m_clock_point = 0;

    this->showLcdTime(m_work_time_sec, true);

    this->m_timer = new QTimer(this);
    this->m_timer->setSingleShot(false);
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(slot_timeout_callback()));

    this->createTrayIcon();

    this->setWindowFlags(windowFlags() & (~Qt::WindowMinMaxButtonsHint|Qt::WindowMaximizeButtonHint));
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    this->styleInit();

    connect(this, SIGNAL(signal_start_work()), this, SLOT(slot_start_work()));
    connect(this, SIGNAL(signal_start_rest()), this, SLOT(slot_start_rest()));
}

Widget::~Widget()
{
    if (this->m_timer->isActive())
    {
        this->m_timer->stop();
    }

    if (this->m_timer != nullptr)
    {
        delete this->m_timer;
    }

    if (this->m_tray_icon != nullptr)
    {
        delete this->m_tray_icon;
    }
    if (this->m_menu != nullptr)
    {
        delete this->m_menu;
    }
    if (this->m_mini_size_action != nullptr)
    {
        delete this->m_mini_size_action;
    }
    if (this->m_max_size_action != nullptr)
    {
        delete this->m_max_size_action;
    }

    if (this->m_restore_win_action != nullptr)
    {
        delete this->m_restore_win_action;
    }
    if (this->m_quit_action != nullptr)
    {
        delete this->m_quit_action;
    }

    delete ui;
}

void Widget::styleInit()
{
    QString qss;
    qss.clear();

    qss.push_back("QPushButton{"
                  "border-style:none;"
                  "border-radius:3px;"
                  "border-width:5px;"
                  "border-color:blue;"
                  "font-family:Microsoft Yahei;"
                  "font-size:12px;"
                  "color:black;"
                  //"background-color:white;"
                  "}");
    qss.push_back("QPushButton:hover{"
                  "color:white;"
                  "background-color:green;}");
    qss.push_back("QPushButton:pressed{"
                  "color:white;"
                  "background-color:blue;}");

    this->setStyleSheet(qss);
}

void Widget::showLcdTime(int time_stamp, bool show_point)
{
    if (show_point)
    {
        ui->lcdNumber->display(QDateTime::fromTime_t(time_stamp).toString("mm:ss"));
    }
    else
    {
        ui->lcdNumber->display(QDateTime::fromTime_t(time_stamp).toString("mm ss"));
    }

}

void Widget::readSetting(int & work_tim, int & rest_tim, int & tran)
{
    QString setting_file_path = "./setting.ini";
    QFile setting_file(setting_file_path);

    if (setting_file.exists() == false)
    {
        setting_file.open(QIODevice::ReadWrite);
        setting_file.close();
    }

    std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    work_tim = settings_file->value("Timer/work_time", 2700).toInt();
    rest_tim = settings_file->value("Timer/rest_time", 300).toInt();
    tran     = settings_file->value("Widget/transparency", 100).toInt();
}

void Widget::createTrayMenu()
{
    /* 右键功能 */
    m_mini_size_action   = new QAction(QStringLiteral("最小化 (&N)"), this);
    m_max_size_action    = new QAction(QStringLiteral("最大化 (&X)"), this);
    m_restore_win_action = new QAction(QStringLiteral("还原 (&R)"), this);
    m_quit_action        = new QAction(QStringLiteral("关闭 (&X)"), this);

    /* 为菜单选项添加图标 */
//    m_mini_size_action->setIcon(QIcon(":/mini_ico.ico"));

    /* 关联槽函数 */
    connect(m_mini_size_action,  SIGNAL(triggered()), this, SLOT(hide()));
    connect(m_max_size_action,   SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(m_restore_win_action,SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(m_quit_action,       SIGNAL(triggered()), qApp, SLOT(quit()));

    /* 创建菜单 */
    m_menu = new QMenu((QWidget *)QApplication::desktop());
    m_menu->addAction(m_mini_size_action);
    m_menu->addAction(m_max_size_action);
    m_menu->addAction(m_restore_win_action);
    m_menu->addSeparator(); //插入分隔符
    m_menu->addAction(m_quit_action);
}

void Widget::createTrayIcon()
{
    /* 创建右键功能 */
    this->createTrayMenu();

    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        return;
    }

    if (m_tray_icon == nullptr)
    {
        m_tray_icon = new QSystemTrayIcon(this);
    }

    /* 创建托盘显示的图标 */
    m_tray_icon->setIcon(QIcon(":/logo.ico"));
    this->setWindowIcon(QIcon(":/logo.ico"));
    /* 鼠标悬浮与图标上时显示的文本 */
    m_tray_icon->setToolTip(QStringLiteral("番茄时钟"));
    /* 消息显示 */
    m_tray_icon->showMessage(QStringLiteral("番茄时钟"), QStringLiteral(""), QSystemTrayIcon::Information,10000);
    /* 创建菜单 */
    m_tray_icon->setContextMenu(m_menu);
    m_tray_icon->show();

    connect(m_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_icon_activated(QSystemTrayIcon::ActivationReason)));
    connect(m_tray_icon, SIGNAL(messageClicked()), this, SLOT(slot_tray_msg_clicked()));
}

void Widget::createMiniPage()
{
    if (m_page_mini == nullptr)
    {
        m_page_mini = new PageMini();
    }

    connect(this, SIGNAL(signal_update_mini_page(int, bool)), m_page_mini, SLOT(slot_update_timer(int, bool)));
}

void Widget::closeEvent(QCloseEvent *event)
{
    if (m_tray_icon->isVisible())
    {
        m_tray_icon->showMessage(QStringLiteral("番茄时钟"), QStringLiteral("隐藏至托盘"), QSystemTrayIcon::Information,1000);
        hide();
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void Widget::slot_timeout_callback()
{
    bool point_show = false;
    this->m_clock_point = this->m_clock_point ^ 0x01;

    if (this->m_clock_point)
    {
        this->m_timer_set_cnt --;
        this->m_timer_cnt ++;
        point_show = false;
    }
    else
    {
        point_show = true;
    }

    this->showLcdTime(this->m_timer_set_cnt, point_show);
    emit signal_update_mini_page(this->m_timer_set_cnt, point_show);

    if (this->m_work_mode == MODE_WORK)
    {
        if (this->m_timer_set_cnt > 0)
        {
            ui->progressBar->setValue(this->m_timer_cnt * 100 / this->m_timer_set_cnt);
        }
        else
        {
            ui->progressBar->setValue(100);
        }

    }
    else
    {
        if (this->m_timer_set_cnt > 0)
        {
            ui->progressBar->setValue((this->m_timer_set_cnt - this->m_timer_cnt) * 100 / this->m_timer_set_cnt);
        }
        else
        {
            ui->progressBar->setValue(0);
        }

    }

    if (this->m_timer_set_cnt == 0)
    {
        this->showLcdTime(0, true);
        this->m_timer->stop();

        if (this->m_work_mode == MODE_WORK)
        {
            m_tray_icon->showMessage(QStringLiteral("番茄时钟"), QStringLiteral("工作时间结束，该休息了"), QSystemTrayIcon::Information,10000);
        }
        else
        {
            m_tray_icon->showMessage(QStringLiteral("番茄时钟"), QStringLiteral("开始摸鱼"), QSystemTrayIcon::Information,10000);
        }
    }
}

void Widget::slot_update_timer()
{
    this->readSetting(m_work_time_sec, m_rest_time_sec, m_widget_tran);
    this->showLcdTime(m_work_time_sec, true);
    this->setWindowOpacity(1);

}

void Widget::slot_update_widget(int value)
{
    this->setWindowOpacity((float)(value / 100.0f));
}

void Widget::slot_tray_msg_clicked()
{
    if (isHidden())
    {
        showNormal();
    }

}

void Widget::slot_icon_activated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    {
//        setWindowState(Qt::WindowActive);

        if (m_work_mode == MODE_WORK)
        {
            QString show_msg;
            show_msg.push_back(QStringLiteral("工作时间\r\n"));
            show_msg.push_back(QDateTime::fromTime_t(m_timer_cnt).toString("mm:ss"));
            m_tray_icon->showMessage("番茄时钟", show_msg);
        }
        else
        {
            QString show_msg;
            show_msg.push_back(QStringLiteral("休息时间\r\n"));
            show_msg.push_back(QDateTime::fromTime_t(m_timer_cnt).toString("mm:ss"));
            m_tray_icon->showMessage("番茄时钟", show_msg);
        }
        break;
    }
    case QSystemTrayIcon::DoubleClick:
    {
        showNormal();
        break;
    }
    default:
        break;
    }
}

void Widget::slot_start_work()
{
    this->m_clock_point = 0;
    this->m_timer_cnt   = 0;
    this->m_timer_set_cnt = this->m_work_time_sec;
    this->m_work_mode = MODE_WORK;
    ui->progressBar->setValue(0);

    if (this->m_timer->isActive() == false)
    {
        this->m_timer->start(500);
    }
}

void Widget::slot_start_rest()
{
    this->m_clock_point = 0;
    this->m_timer_cnt   = 0;
    this->m_timer_set_cnt = this->m_rest_time_sec;
    this->m_work_mode = MODE_REST;
    ui->progressBar->setValue(100);

    if (this->m_timer->isActive() == false)
    {
        this->m_timer->start(500);
    }
}


void Widget::on_pushButton_start_clicked()
{
    emit signal_start_work();
}

void Widget::on_pushButton_rest_clicked()
{
    emit signal_start_rest();
}

void Widget::on_pushButton_reset_clicked()
{
    this->m_timer->stop();
    this->readSetting(m_work_time_sec, m_rest_time_sec, m_widget_tran);

    if (m_work_mode == MODE_REST)
    {
        this->showLcdTime(m_rest_time_sec, true);
        ui->progressBar->setValue(100);
    }
    else
    {
        this->showLcdTime(m_work_time_sec, true);
        ui->progressBar->setValue(0);
    }

}

void Widget::on_pushButton_setting_clicked()
{
    PageSetting * page_setting = new PageSetting();
    connect(page_setting, SIGNAL(signal_save_file()), this, SLOT(slot_update_timer()));
    connect(page_setting, SIGNAL(signal_update_tran(int)), this, SLOT(slot_update_widget(int)));
    page_setting->exec();
    disconnect(page_setting, SIGNAL(signal_save_file()), this, SLOT(slot_update_timer()));
    disconnect(page_setting, SIGNAL(signal_update_tran(int)), this, SLOT(slot_update_widget(int)));
    delete page_setting;
}


void Widget::on_pushButton_hide_clicked()
{
    m_tray_icon->showMessage(QStringLiteral("番茄时钟"), QStringLiteral("隐藏至托盘"), QSystemTrayIcon::Information,1000);
    hide();

    PageMini * page_mini = new PageMini();
    connect(this, SIGNAL(signal_update_mini_page(int, bool)), page_mini, SLOT(slot_update_timer(int, bool)));
    connect(page_mini, SIGNAL(signal_close_mini()), this, SLOT(showNormal()));
    connect(page_mini, SIGNAL(signal_start_work()), this, SIGNAL(signal_start_work()));
    connect(page_mini, SIGNAL(signal_start_rest()), this, SIGNAL(signal_start_rest()));
    page_mini->exec();
    qDebug() << "page delete" << endl;
    disconnect(this, SIGNAL(signal_update_mini_page(int, bool)), page_mini, SLOT(slot_update_timer(int, bool)));
    disconnect(page_mini, SIGNAL(signal_close_mini()), this, SLOT(showNormal()));
    disconnect(page_mini, SIGNAL(signal_start_work()), this, SIGNAL(signal_start_work()));
    disconnect(page_mini, SIGNAL(signal_start_rest()), this, SIGNAL(signal_start_rest()));
    delete page_mini;
}

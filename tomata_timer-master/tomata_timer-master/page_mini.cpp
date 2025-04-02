#include "page_mini.h"
#include "ui_page_mini.h"

#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <QPalette>
#include <QScreen>

PageMini::PageMini(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageMini)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setWindowOpacity(0);
    this->setAttribute(Qt::WA_WState_WindowOpacitySet);

    this->styleInit();

    readSettings();

    this->setWindowOpacity((float)(m_widget_tran/100.f));

    this->move(m_pose_x, m_pose_y);
}

PageMini::~PageMini()
{
    delete ui;
}

void PageMini::slot_update_timer(int time_stamp, bool show_point)
{
    this->showLcdTime(time_stamp, show_point);
}

void PageMini::showLcdTime(int time_stamp, bool show_point)
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

void PageMini::styleInit()
{
    QStringList qss;
    qss.clear();

    qss.push_back("QPushButton{border-image:url(:/img/max.png);}");
    qss.push_back("QPushButton:hover{border-image:url(:/img/max_hover.png);}");
    qss.push_back("QPushButton:pressed{border-image:url(:/img/max_press.png);}");
    ui->pushButton_normal->setStyleSheet(qss.join(""));
    ui->pushButton_normal->setToolTip(QStringLiteral("放大窗口"));

    qss.clear();

    qss.push_back("QPushButton{border-image:url(:/img/work.png);}"
                  "QPushButton:hover{border-image:url(:/img/work_hover.png);}"
                  "QPushButton:pressed{border-image:url(:/img/work_press.png);}");
    ui->pushButton_work->setStyleSheet(qss.join(""));
    ui->pushButton_work->setToolTip(QStringLiteral("开始工作"));
    qss.clear();

    qss.push_back("QPushButton{border-image:url(:/img/rest.png);}");
    qss.push_back("QPushButton:hover{border-image:url(:/img/rest_hover.png);}");
    qss.push_back("QPushButton:pressed{border-image:url(:/img/rest_press.png);}");
    ui->pushButton_rest->setStyleSheet(qss.join(""));
    ui->pushButton_rest->setToolTip(QStringLiteral("休息一下"));
    qss.clear();

    qss.push_back("QPushButton{border-image:url(:/img/close.png);}"
                  "QPushButton:hover{border-image:url(:/img/close_hover.png);}"
                  "QPushButton:pressed{border-image:url(:/img/close_press.png);}");
    ui->pushButton_close->setStyleSheet(qss.join(""));
    ui->pushButton_close->setToolTip(QStringLiteral("关闭浮窗"));

    this->setStyleSheet("background-color: #333333;");

    QPalette lcd_pale = ui->lcdNumber->palette();
    lcd_pale.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setPalette(lcd_pale);

}

void PageMini::readSettings()
{
    QString setting_file_path = "./setting.ini";
    QFile setting_file(setting_file_path);

    if (setting_file.exists() == false)
    {
        setting_file.open(QIODevice::ReadWrite);
        setting_file.close();
    }

    std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    m_pose_x = settings_file->value("PageMini/pose_x", 1550).toInt();
    m_pose_y = settings_file->value("PageMini/pose_y", 0).toInt();
    m_widget_tran = settings_file->value("Widget/transparency", 50).toInt();
}

void PageMini::savePoseToSettings(int &pose_x, int &pose_y)
{
    QString setting_file_path = "./setting.ini";
    QFile setting_file(setting_file_path);

    std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    settings_file->setValue("PageMini/pose_x", pose_x);
    settings_file->setValue("PageMini/pose_y", pose_y);
}

void PageMini::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint point;
        point = event->globalPos() - m_offset;
        QPoint last_pose = m_win_top_left + point;
        QScreen * srceen = QGuiApplication::primaryScreen();
        int width  = srceen->availableGeometry().width();
        int height = srceen->availableGeometry().height();
        QSize page_size = this->size();

        if (last_pose.y() <= 0)
        {
            last_pose.setY(0);
        }
        else if (last_pose.y() > height - page_size.height())
        {
            last_pose.setY(height - page_size.height());
        }

        if (last_pose.x() <= 0)
        {
            last_pose.setX(0);
        }
        else if (last_pose.x() > width - page_size.width())
        {
            last_pose.setX(width - page_size.width());
        }
        move(last_pose);
        int pose_x = last_pose.x();
        int pose_y = last_pose.y();
        savePoseToSettings(pose_x, pose_y);
    }
    else
    {
        QWidget::mouseMoveEvent(event);
    }
}

void PageMini::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (m_mouse_pressed == false)
        {
            m_offset = event->globalPos();
            m_win_top_left = this->frameGeometry().topLeft();
        }
        m_mouse_pressed = true;

    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void PageMini::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        m_mouse_pressed = false;
    }
    else
    {
        QWidget::mouseReleaseEvent(event);
    }
}

void PageMini::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        this->close();
        emit signal_close_mini();
    }
    else
    {
        QWidget::mouseDoubleClickEvent(event);
    }
}

void PageMini::on_pushButton_normal_clicked()
{
    this->close();
    emit signal_close_mini();
}

void PageMini::on_pushButton_work_clicked()
{
    emit signal_start_work();
}

void PageMini::on_pushButton_rest_clicked()
{
    emit signal_start_rest();
}

void PageMini::on_pushButton_close_clicked()
{
    this->close();
}

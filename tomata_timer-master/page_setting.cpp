#include "page_setting.h"
#include "ui_page_setting.h"

#include <QDebug>
#include <QDateTime>
#include <QFile>

PageSetting::PageSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageSetting)
{
    ui->setupUi(this);

    this->setWindowTitle(QStringLiteral("设置"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(300, 350);

    this->readSetting(m_set_work_value, m_set_rest_value, m_set_tran);

    this->showWorkTime(m_set_work_value);
    this->showRestTime(m_set_rest_value);

    this->setWorkSlider(m_set_work_value);
    this->setRestSlider(m_set_rest_value);

    ui->horizontalSlider_transparency->setValue(m_set_tran);
}

PageSetting::~PageSetting()
{
    delete ui;
}

void PageSetting::on_horizontalSlider_work_tim_sliderMoved(int position)
{
    m_set_work_value = position;
    this->showWorkTime(m_set_work_value);
}

void PageSetting::on_horizontalSlider_rest_tim_sliderMoved(int position)
{
    m_set_rest_value = position;
    this->showRestTime(m_set_rest_value);
}

void PageSetting::showWorkTime(unsigned int time)
{
    ui->lcdNumbe_work_tim->display(QDateTime::fromTime_t(time).toString("mm:ss"));
}

void PageSetting::showRestTime(unsigned int time)
{
    ui->lcdNumber_rest_tim->display(QDateTime::fromTime_t(time).toString("mm:ss"));
}

void PageSetting::setWorkSlider(unsigned int value)
{
    ui->horizontalSlider_work_tim->setValue(value);
}

void PageSetting::setRestSlider(unsigned int value)
{
    ui->horizontalSlider_rest_tim->setValue(value);
}

void PageSetting::readSetting(int & work_tim, int & rest_tim, int & tran)
{
    QString setting_file_path = "./setting.ini";
    QFile setting_file(setting_file_path);

    if (setting_file.exists() == false)
    {
        setting_file.open(QIODevice::ReadWrite);
        setting_file.close();
        std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    }

    std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    work_tim = settings_file->value("Timer/work_time", 2700).toInt();
    rest_tim = settings_file->value("Timer/rest_time", 300).toInt();
    tran     = settings_file->value("Widget/transparency", 100).toInt();

}

void PageSetting::saveSetting(int &work_tim, int &rest_tim, int & tran)
{
    QString setting_file_path = "./setting.ini";
    QFile setting_file(setting_file_path);

    if (setting_file.exists() == false)
    {
        setting_file.open(QIODevice::ReadWrite);
        setting_file.close();
    }

    std::unique_ptr<QSettings> settings_file(new QSettings(setting_file_path, QSettings::IniFormat));
    settings_file->beginGroup("Timer");
    settings_file->setValue("work_time", work_tim);
    settings_file->setValue("rest_time", rest_tim);
    settings_file->endGroup();
    settings_file->beginGroup("Widget");
    settings_file->setValue("transparency", tran);
    settings_file->endGroup();
}

void PageSetting::on_pushButton_work_tim_add_clicked()
{
    if (m_set_work_value < 3600)
    {
        m_set_work_value ++;
        this->showWorkTime(m_set_work_value);
        this->setWorkSlider(m_set_work_value);
    }
}

void PageSetting::on_pushButton_work_tim_reduce_clicked()
{
    if (m_set_work_value > 0)
    {
        m_set_work_value --;
        this->showWorkTime(m_set_work_value);
        this->setWorkSlider(m_set_work_value);
    }
}

void PageSetting::on_pushButton_rest_tim_add_clicked()
{
    if (m_set_rest_value < 1200)
    {
        m_set_rest_value ++;
        this->showRestTime(m_set_rest_value);
        this->setRestSlider(m_set_rest_value);
    }
}

void PageSetting::on_pushButton_rest_tim_reduce_clicked()
{
    if (m_set_rest_value > 0)
    {
        m_set_rest_value --;
        this->showRestTime(m_set_rest_value);
        this->setRestSlider(m_set_rest_value);
    }
}

void PageSetting::on_pushButton_cancle_clicked()
{
    this->close();
}

void PageSetting::on_pushButton_save_clicked()
{
    this->saveSetting(m_set_work_value, m_set_rest_value, m_set_tran);
    emit signal_save_file();
    this->close();
}

void PageSetting::on_horizontalSlider_transparency_valueChanged(int value)
{
    m_set_tran = value;
    emit signal_update_tran(value);
}

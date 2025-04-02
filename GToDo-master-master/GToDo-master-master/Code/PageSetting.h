#ifndef PAGE_SETTING_H
#define PAGE_SETTING_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class PageSetting;
}

class PageSetting : public QDialog
{
    Q_OBJECT

public:
    explicit PageSetting(QWidget *parent = nullptr);
    ~PageSetting();

private slots:
    void on_horizontalSlider_work_tim_sliderMoved(int position);

    void on_horizontalSlider_rest_tim_sliderMoved(int position);

    void on_pushButton_work_tim_add_clicked();

    void on_pushButton_work_tim_reduce_clicked();

    void on_pushButton_rest_tim_add_clicked();

    void on_pushButton_rest_tim_reduce_clicked();

    void on_pushButton_cancle_clicked();

    void on_pushButton_save_clicked();

    void on_horizontalSlider_transparency_valueChanged(int value);

private:
    Ui::PageSetting *ui;

    int m_set_work_value;
    int m_set_rest_value;
    int m_set_tran;

signals:
    void signal_save_file(void);
    void signal_update_tran(int);

private:
    void showWorkTime(unsigned int time);
    void showRestTime(unsigned int time);

    void setWorkSlider(unsigned int value);
    void setRestSlider(unsigned int value);

    void readSetting(int & work_tim, int & rest_tim, int & tran);
    void saveSetting(int & work_tim, int & rest_tim, int & tran);
};

#endif // PAGE_SETTING_H

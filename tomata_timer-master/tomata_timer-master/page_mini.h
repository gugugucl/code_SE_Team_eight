#ifndef PAGE_MINI_H
#define PAGE_MINI_H

#include <QDialog>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Ui {
class PageMini;
}

class PageMini : public QDialog
{
    Q_OBJECT

public:
    explicit PageMini(QWidget *parent = nullptr);
    ~PageMini();

private:
    Ui::PageMini *ui;

    bool m_mouse_pressed = false;
    QPoint m_offset;
    QPoint m_win_top_left;

    int m_pose_x;
    int m_pose_y;
    int m_widget_tran;

private slots:
    void slot_update_timer(int time_stamp, bool show_point);

    void on_pushButton_normal_clicked();

    void on_pushButton_work_clicked();

    void on_pushButton_rest_clicked();

    void on_pushButton_close_clicked();

private:
    void showLcdTime(int time_stamp, bool show_point);
    void styleInit(void);

    void readSettings(void);
    void savePoseToSettings(int & pose_x, int & pose_y);

signals:
    void signal_close_mini(void);
    void signal_start_work(void);
    void signal_start_rest(void);

protected:
    /* 鼠标移动 */
    void mouseMoveEvent(QMouseEvent * event);
    /* 鼠标单击 */
    void mousePressEvent(QMouseEvent * event);
    /* 鼠标松开按键 */
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
};

#endif // PAGE_MINI_H

#ifndef _GTODO_H_
#define _GTODO_H_
//#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QBoxLayout>
#include <QLabel>
#include <string>
#include <QCalendarWidget>
#include <QPushButton>
#include <QScrollArea>
#include "GToDoItem.h"
#include "GQstringDate.h"
#include "GBtnRroup.h"
#include <QPushButton>
#include <QIcon>
#include <QStackedWidget>
#include <QFile>
#include <QApplication>
#include <QTranslator>
#include <QMouseEvent>
#include<QPainter>
#include <QSqlError>
#include <QSystemTrayIcon>

// 在头文件中定义版本号常量
#define MY_APP_VERSION "1.0.0"

namespace Ui {
class GToDo;
}

class GToDo : public QWidget
{
    Q_OBJECT

public:
    explicit GToDo(QWidget *parent = 0);
    ~GToDo();
    void update();
    //void statusBar();
public:
    static void setStyle();
public:
    // 声明成员变量
    QString loggedInUser;//登录的用户名
    void setLoggedInUser(const QString& username) {
        loggedInUser = username;
    }
public:
    QTranslator *translator;
    void listLayoutClear();
    void loadGroup();
    void on_btnShowFinished_clicked();
private slots:
    void on_btnRefresh_clicked();
    void openSettingPanel(QString Title, QString Deadline);
    void groupSwitch(QString group);
    void on_editTitle_editingFinished();
    void on_btnDetail_clicked();
    void on_boxPriority_currentIndexChanged(int index);
    void on_boxRepeat_currentIndexChanged(int index);
    void on_Crontab_currentIndexChanged(int index);
    void on_btnSetDdl_clicked();
    void on_btnSetRemind_clicked();
    void on_btnMyTask_clicked();
    void on_editAddGroup_editingFinished();
    void on_editAddItem_editingFinished();
    void on_boxOrder_currentIndexChanged(int);
    void on_pushButton_background_color_clicked();
    void on_pushButton_color_clicked();
    void on_pushButton_textbold_clicked();
    void on_pushButton_textitalic_clicked();
    void on_pushButton_textunder_clicked();
    void on_pushButton_textright_clicked();
    void on_pushButton_textleft_clicked();
    void on_pushButton_textjustify_clicked();
    void on_pushButton_textcenter_clicked();
    void on_comboBox_activated(int);
    void on_comboBox_activated(const QString &arg1);
    void on_pushButton_exit_clicked();
    void on_pushButton_login_clicked();
    void on_pushButton_min_clicked();
    void on_pushButton_menu_clicked();
    // void on_loginSuccess(const QString &username, bool);
    void on_pushButton_login_img_clicked();


    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_reg_clicked();
    void on_pushButton_longinbtn_clicked();
    void on_pushButton_regbtn_clicked();
    void on_btn_signin_clicked();

signals:
    //Q_SIGNAL void loginSuccess(const QString& username, bool is_logged_in);

private slots:
    void on_selectButton_clicked();
    void on_saveButton_clicked();
    void on_QPushButton_out_clicked();
    // 头文件中添加：
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason); // 状态栏图标被单击的槽函数
    void on_update_img_clicked();
    void on_Clear_btn_clicked();


    //void on_checkBox_shutdown_clicked();

    void on_Selection_Audio_clicked();

    void on_Selection_Audio_ok_clicked();

protected:
    void  paintEvent(QPaintEvent *event);
private:
    QString currentUsername;
    QString currentPassword;
    Ui::GToDo *ui;
    bool       m_bDrag;
    QPoint     mouseStartPoint;
    QPoint     windowTopLeftPoint;
    QPoint     last;
    QSqlDatabase db;
    QWidget *  widget;
    QVBoxLayout * todoLayout;
    QSystemTrayIcon *trayIcon;
};

#endif

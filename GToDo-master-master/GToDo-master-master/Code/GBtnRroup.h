#ifndef _GBTNGROUP_H_
#define _GBTNGROUP_H_
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QMenu>
#include <QMessageBox>
#include "GQstringDate.h"

namespace Ui {
class GBtnGroup;
}

class GBtnGroup : public QWidget
{
    Q_OBJECT

public:
    explicit GBtnGroup(QWidget *parent = 0);
    ~GBtnGroup();
    void setText(QString name);

signals:
    void groupSwitch(QString group);//发出切换组信号
private slots:
    void on_pushButton_clicked();//处理点击按钮事件
    void on_btnDelete_clicked();//处理点击删除按钮事件
    void sltShowPopMenu(const QPoint& );//显式右键菜单
    void on_btnModify_clicked();//处理点击修改键

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;//过滤事件，特别是鼠标事件
    //void keyPressEvent(QKeyEvent *event) override;//处理键盘按键事件

private slots:
    void on_button_doubleClicked(QPushButton *button);//处理双击

private:
    QPushButton *m_editingButton = nullptr;
    Ui::GBtnGroup *ui;
    QMenu *popMenu;
};
#endif

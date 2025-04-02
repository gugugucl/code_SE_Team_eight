#pragma once

#include <QtWidgets/QWidget>
#include <QFontDatabase>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QMenu>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlRecord>
#include <QMap>
#include <QCursor>
#include <QCheckBox>
#include <QDateTime>
#include <QPalette>
#include <QCalendarWidget>
#include <QTimeEdit>
#include "ui_kmainwindow.h"
#include "koperatedatabase.h"


class KMainWindow : public QWidget
{
    Q_OBJECT


public:
    KMainWindow(QWidget *parent = Q_NULLPTR);

    void initUI();

	void remind(const QString& str);

	void initGroupTableView();                        //GroupTableView初始化

    QFrame* initGroupItemWidget(QModelIndex& index);  // 初始化GroupTableView单元格窗口

    void initTodoTableVIew();                         //TodoTableView初始化

    QFrame* initTodoitemWidget(QModelIndex& index,int& row);  //初始化TodoTableView单元格窗口

    void initTodoDoneTableVIew();                     //TodoDoneTableView初始化

    QFrame* initTodoDoneItemWidget(QModelIndex& index, int& row);//初始化TodoDoneTableView单元格窗口

    void initHomeTableView();            //homeTableView初始化

    QFrame* initHomeItemWidget(QModelIndex& index, int& row); //homeTableVieww单元格窗口

	void refreshHomeTableView(int flag);         //刷新首页tableView





public slots:
    void onNOArrangeBtnClicked(); //未安排

    void onLaterBtnClicked();     //以后

    void onOneWeekBtnClicked();   //未来七天

    void onHomePageBtnClicked();  //我的首页

    void onAddGroupBtnClicked(); // 添加分组

    void onGroupBtnClicked(); // 分组待办任务显示

    void onRenameActionTriggered(); //更新分组名称

    void onDeleteActionTriggered(); //删除分组

    void refreshGroupTableView();   //刷新分组显示

    void refeshTodoTableView(); //刷新待办显示

    void refeshDoneTableView();  //刷新以完成待办显示
    
    void onEditGroupBtnReleased(); // 编辑按钮槽函数

    void onTodoDoneBtnClicked();   //显示完成待办按钮

    void onMyTodoBtnClicked();     //我的待办

    void onTodoCheckBoxStateChanged(); //完成待办

    void onAddTodoItem();             //添加待办事件

    void onTodoTableViewClicked(const QModelIndex& index);    //todoTableView行点击槽函数

    void onDoneTableViewClicked(const QModelIndex& index);    //doneTableView行点击槽函数


    void onEditEndDateBtnClicked();   //待办结束时间编辑

    void onEditRemindTimeClicked();   //提醒时间编辑

    void onDescribBtnClicked();       //描述编辑

    void onAddressBtnClicked();       //地点编辑

    void onRemarkBtnClicked();        //备注编辑

    void onTodoDoneCheckBoxStateChanged(); //待办完成编辑

    void onPriorityComboBoxIndexChanged(); //优先级改变

    void onRefreshBtnClicked();           //主页刷新按钮

    void onEndDateOrderActionTriggered();          //按照结束时间排序

    void onCreateDateOrderActionTriggered();       //创建时间排序

    void onPriorityOrderActionTriggered();         //优先权排序





private:
    Ui::KMainWindowClass ui;

    int m_homeDisplay;              //1:未安排，2：未来七天，3：以后

    QSqlTableModel* m_groupModel;   //分组表model

    int m_currentGroupRow;          //当前选中组的行数

    int m_TodoTableViewRow;         //选中待办的行数

    QSqlTableModel* m_homeModel;    //首页表model

    QSqlTableModel* m_todoModel;    //待办表model

    QSqlTableModel* m_todoDoneModel; //待办完成表model

    int m_tableViewFlag;             //tableview标志




};

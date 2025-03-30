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

	void initGroupTableView();                        //GroupTableView��ʼ��

    QFrame* initGroupItemWidget(QModelIndex& index);  // ��ʼ��GroupTableView��Ԫ�񴰿�

    void initTodoTableVIew();                         //TodoTableView��ʼ��

    QFrame* initTodoitemWidget(QModelIndex& index,int& row);  //��ʼ��TodoTableView��Ԫ�񴰿�

    void initTodoDoneTableVIew();                     //TodoDoneTableView��ʼ��

    QFrame* initTodoDoneItemWidget(QModelIndex& index, int& row);//��ʼ��TodoDoneTableView��Ԫ�񴰿�

    void initHomeTableView();            //homeTableView��ʼ��

    QFrame* initHomeItemWidget(QModelIndex& index, int& row); //homeTableVieww��Ԫ�񴰿�

	void refreshHomeTableView(int flag);         //ˢ����ҳtableView





public slots:
    void onNOArrangeBtnClicked(); //δ����

    void onLaterBtnClicked();     //�Ժ�

    void onOneWeekBtnClicked();   //δ������

    void onHomePageBtnClicked();  //�ҵ���ҳ

    void onAddGroupBtnClicked(); // ��ӷ���

    void onGroupBtnClicked(); // �������������ʾ

    void onRenameActionTriggered(); //���·�������

    void onDeleteActionTriggered(); //ɾ������

    void refreshGroupTableView();   //ˢ�·�����ʾ

    void refeshTodoTableView(); //ˢ�´�����ʾ

    void refeshDoneTableView();  //ˢ������ɴ�����ʾ
    
    void onEditGroupBtnReleased(); // �༭��ť�ۺ���

    void onTodoDoneBtnClicked();   //��ʾ��ɴ��찴ť

    void onMyTodoBtnClicked();     //�ҵĴ���

    void onTodoCheckBoxStateChanged(); //��ɴ���

    void onAddTodoItem();             //��Ӵ����¼�

    void onTodoTableViewClicked(const QModelIndex& index);    //todoTableView�е���ۺ���

    void onDoneTableViewClicked(const QModelIndex& index);    //doneTableView�е���ۺ���


    void onEditEndDateBtnClicked();   //�������ʱ��༭

    void onEditRemindTimeClicked();   //����ʱ��༭

    void onDescribBtnClicked();       //�����༭

    void onAddressBtnClicked();       //�ص�༭

    void onRemarkBtnClicked();        //��ע�༭

    void onTodoDoneCheckBoxStateChanged(); //������ɱ༭

    void onPriorityComboBoxIndexChanged(); //���ȼ��ı�

    void onRefreshBtnClicked();           //��ҳˢ�°�ť

    void onEndDateOrderActionTriggered();          //���ս���ʱ������

    void onCreateDateOrderActionTriggered();       //����ʱ������

    void onPriorityOrderActionTriggered();         //����Ȩ����





private:
    Ui::KMainWindowClass ui;

    int m_homeDisplay;              //1:δ���ţ�2��δ�����죬3���Ժ�

    QSqlTableModel* m_groupModel;   //�����model

    int m_currentGroupRow;          //��ǰѡ���������

    int m_TodoTableViewRow;         //ѡ�д��������

    QSqlTableModel* m_homeModel;    //��ҳ��model

    QSqlTableModel* m_todoModel;    //�����model

    QSqlTableModel* m_todoDoneModel; //������ɱ�model

    int m_tableViewFlag;             //tableview��־




};

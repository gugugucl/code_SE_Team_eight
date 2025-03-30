#ifndef __KOPERATEDATABASE_H__
#define __KOPERATEDATABASE_H__
#include <QSqlDatabase>
#include <QMessageBox>
#include <QMutex>
#include <QDebug>


class KOperateDataBase
{
public:
	static KOperateDataBase* getInstance(); //����ģʽ

	bool isOpen(); //���ݿ��Ƿ��

	void close();  //�ر����ݿ�


private:
	KOperateDataBase();

	static KOperateDataBase* s_dataBaseInstance;

	QSqlDatabase m_db;

	bool m_dbOpen;

	static QMutex s_mutex;





};

#endif __KOPERATEDATABASE_H__

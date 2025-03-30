#ifndef __KOPERATEDATABASE_H__
#define __KOPERATEDATABASE_H__
#include <QSqlDatabase>
#include <QMessageBox>
#include <QMutex>
#include <QDebug>


class KOperateDataBase
{
public:
	static KOperateDataBase* getInstance(); //单例模式

	bool isOpen(); //数据库是否打开

	void close();  //关闭数据库


private:
	KOperateDataBase();

	static KOperateDataBase* s_dataBaseInstance;

	QSqlDatabase m_db;

	bool m_dbOpen;

	static QMutex s_mutex;





};

#endif __KOPERATEDATABASE_H__

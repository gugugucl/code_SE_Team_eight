#include "koperatedatabase.h"

KOperateDataBase* KOperateDataBase::s_dataBaseInstance = Q_NULLPTR;
QMutex KOperateDataBase::s_mutex;

//连接数据库
KOperateDataBase::KOperateDataBase()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("backlog.db");
	m_dbOpen = m_db.open();
	if (!m_dbOpen)
		QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("数据库连接失败！请联系管理人员！"), QMessageBox::Yes);
	else qDebug() << "db connect sucess!";
}

//关闭数据库
void KOperateDataBase::close()
{
	if (nullptr != s_dataBaseInstance)
	{
		s_mutex.lock();
		m_db.close();
		delete s_dataBaseInstance;
		s_mutex.unlock();
	}
}

//获取数据库对象实例
KOperateDataBase* KOperateDataBase::getInstance()
{
	if (nullptr == s_dataBaseInstance)
	{
		s_mutex.lock();
		if (nullptr == s_dataBaseInstance)
		{
			s_dataBaseInstance = new KOperateDataBase();
		}
		s_mutex.unlock();
	}
	return s_dataBaseInstance;
}

//数据库是否打开
bool KOperateDataBase::isOpen()
{
	return m_dbOpen ? true : false;
}


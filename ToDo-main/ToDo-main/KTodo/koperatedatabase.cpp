#include "koperatedatabase.h"

KOperateDataBase* KOperateDataBase::s_dataBaseInstance = Q_NULLPTR;
QMutex KOperateDataBase::s_mutex;

//连接数据库
// 连接 MySQL 数据库
KOperateDataBase::KOperateDataBase()
{
	m_db = QSqlDatabase::addDatabase("QMYSQL");  // 使用 QMYSQL 代替 QSQLITE
	m_db.setHostName("49.235.140.182"); // 远程 MySQL 服务器 IP 或域名
	m_db.setPort(3306); // MySQL 端口
	m_db.setDatabaseName("user_db"); // 数据库名称
	m_db.setUserName("root"); // MySQL 用户名
	m_db.setPassword(""); // MySQL 密码

	m_dbOpen = m_db.open();
	if (!m_dbOpen)
		QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("数据库连接失败！请联系管理人员！"), QMessageBox::Yes);
	else
		qDebug() << "db connect success!";
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


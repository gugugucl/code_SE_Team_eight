#include "koperatedatabase.h"

KOperateDataBase* KOperateDataBase::s_dataBaseInstance = Q_NULLPTR;
QMutex KOperateDataBase::s_mutex;

//�������ݿ�
// ���� MySQL ���ݿ�
KOperateDataBase::KOperateDataBase()
{
	m_db = QSqlDatabase::addDatabase("QMYSQL");  // ʹ�� QMYSQL ���� QSQLITE
	m_db.setHostName("49.235.140.182"); // Զ�� MySQL ������ IP ������
	m_db.setPort(3306); // MySQL �˿�
	m_db.setDatabaseName("user_db"); // ���ݿ�����
	m_db.setUserName("root"); // MySQL �û���
	m_db.setPassword(""); // MySQL ����

	m_dbOpen = m_db.open();
	if (!m_dbOpen)
		QMessageBox::warning(NULL, QStringLiteral("����"), QStringLiteral("���ݿ�����ʧ�ܣ�����ϵ������Ա��"), QMessageBox::Yes);
	else
		qDebug() << "db connect success!";
}

//�ر����ݿ�
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

//��ȡ���ݿ����ʵ��
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

//���ݿ��Ƿ��
bool KOperateDataBase::isOpen()
{
	return m_dbOpen ? true : false;
}


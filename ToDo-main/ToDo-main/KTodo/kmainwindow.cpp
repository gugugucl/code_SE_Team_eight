#include "kmainwindow.h"



KMainWindow::KMainWindow(QWidget* parent)
	: QWidget(parent)
	, m_groupModel(Q_NULLPTR)
	, m_currentGroupRow(-1)
	, m_homeDisplay(1)
{
	ui.setupUi(this);
	initUI();
	KOperateDataBase::getInstance(); //��ʼ�����ݿ��������
	initGroupTableView();
	initTodoTableVIew();
	initTodoDoneTableVIew();
	initHomeTableView();


	//-------------------------�ź����---------------------------------
	(void)connect(ui.btn_addGroup, &QPushButton::clicked, this, &KMainWindow::onAddGroupBtnClicked);
	//��ҳ���ҵĴ��찴ť
	(void)connect(ui.btn_homePage, &QPushButton::clicked, this, &KMainWindow::onHomePageBtnClicked);
	(void)connect(ui.btn_myBacklog, &QPushButton::clicked, this, &KMainWindow::onMyTodoBtnClicked);
	//���غ���ʾ����ɰ�ť
	(void)connect(ui.btn_doneTodo, &QPushButton::clicked, this, &KMainWindow::onTodoDoneBtnClicked);
	//��Ӵ���lienEidt
	(void)connect(ui.lineEdit_addtodo, &QLineEdit::returnPressed, this, &KMainWindow::onAddTodoItem);
	//TodoTableVIew
	(void)connect(ui.todo_tableView, &QTableView::clicked, this, &KMainWindow::onTodoTableViewClicked);
	//TodoDoneTableView
	(void)connect(ui.done_tableView, &QTableView::clicked, this, &KMainWindow::onDoneTableViewClicked);
	//����ʱ�䰴ť
	(void)connect(ui.btn_endDate, &QPushButton::clicked, this, &KMainWindow::onEditEndDateBtnClicked);
	//����ʱ�䰴ť
	(void)connect(ui.btn_remind, &QPushButton::clicked, this, &KMainWindow::onEditRemindTimeClicked);
	//�����༭
	(void)connect(ui.btn_describ, &QPushButton::clicked, this, &KMainWindow::onDescribBtnClicked);
	//��ַ�༭
	(void)connect(ui.btn_address, &QPushButton::clicked, this, &KMainWindow::onAddressBtnClicked);
	//��ע�༭
	(void)connect(ui.btn_remark, &QPushButton::clicked, this, &KMainWindow::onRemarkBtnClicked);
	//�༭checkbox
	(void)connect(ui.checkBox_name, &QCheckBox::stateChanged, this, &KMainWindow::onTodoDoneCheckBoxStateChanged);
	//�༭���ȼ�
	(void)connect(ui.comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &KMainWindow::onPriorityComboBoxIndexChanged);
	//δ���š�δ�����졢�Ժ�
	(void)connect(ui.btn_noArrange, &QPushButton::clicked, this, &KMainWindow::onNOArrangeBtnClicked);
	(void)connect(ui.btn_later, &QPushButton::clicked, this, &KMainWindow::onLaterBtnClicked);
	(void)connect(ui.btn_oneWeek, &QPushButton::clicked, this, &KMainWindow::onOneWeekBtnClicked);
	//ˢ�°�ť������
	(void)connect(ui.btn_refresh, &QPushButton::clicked, this,&KMainWindow::onRefreshBtnClicked);


}

//UI��ʼ��
void KMainWindow::initUI()
{
	ui.frame_edit->setVisible(false);
	ui.btn_order->setVisible(false);
	QMenu* menu = new QMenu(this);
	QAction* endDateAction =  menu->addAction(QStringLiteral("����ʱ������"));
	QAction* createDateAction =  menu->addAction(QStringLiteral("����ʱ��"));
	QAction* priorityAction =  menu->addAction(QStringLiteral("���ȼ�����"));

	ui.btn_order->setStyleSheet("QPushButton::menu-indicator{image:none}");
	ui.btn_order->setMenu(menu);

	(void)connect(endDateAction, &QAction::triggered, this, &KMainWindow::onEndDateOrderActionTriggered);
	(void)connect(createDateAction, &QAction::triggered, this, &KMainWindow::onCreateDateOrderActionTriggered);
	(void)connect(priorityAction, &QAction::triggered, this, &KMainWindow::onPriorityOrderActionTriggered);

	ui.btn_noArrange->setStyleSheet("QPushButton{color:rgb(139,151,175);}");
	ui.btn_oneWeek->setStyleSheet("QPushButton{color:rgb(139,151,175);}");
	ui.btn_later->setStyleSheet("QPushButton{color:rgb(139,151,175);}");

}

//δ����
void KMainWindow::onNOArrangeBtnClicked()
{
	ui.btn_noArrange->setIcon(QIcon(":/images/unfold.png"));
	ui.btn_noArrange->setStyleSheet("QPushButton{color:rgb(4,184,174);}");

	ui.btn_oneWeek->setIcon(QIcon(":/images/fold.png"));
	ui.btn_oneWeek->setStyleSheet("QPushButton{color:rgb(139,151,175);}");

	ui.btn_later->setIcon(QIcon(":/images/fold.png"));
	ui.btn_later->setStyleSheet("QPushButton{color:rgb(139,151,175);}");

	refreshHomeTableView(1);


}

//δ������
void KMainWindow::onOneWeekBtnClicked()
{
	ui.btn_noArrange->setIcon(QIcon(":/images/fold.png"));
	ui.btn_noArrange->setStyleSheet("QPushButton{color:rgb(139,151,175);}");


	ui.btn_oneWeek->setIcon(QIcon(":/images/unfold.png"));
	ui.btn_oneWeek->setStyleSheet("QPushButton{color:rgb(4,184,174);}");

	ui.btn_later->setIcon(QIcon(":/images/fold.png"));
	ui.btn_later->setStyleSheet("QPushButton{color:rgb(139,151,175);}");

	refreshHomeTableView(2);


}

//�Ժ�
void KMainWindow::onLaterBtnClicked()
{
	ui.btn_noArrange->setIcon(QIcon(":/images/fold.png"));
	ui.btn_noArrange->setStyleSheet("QPushButton{color:rgb(139,151,175);}");


	ui.btn_oneWeek->setIcon(QIcon(":/images/fold.png"));
	ui.btn_oneWeek->setStyleSheet("QPushButton{color:rgb(139,151,175);}");


	ui.btn_later->setIcon(QIcon(":/images/unfold.png"));
	ui.btn_later->setStyleSheet("QPushButton{color:rgb(4,184,174);}");

	refreshHomeTableView(3);


 }

//������Ϣ��
void KMainWindow::remind(const QString& str)
{
	QMessageBox::question(this, QStringLiteral("��ʾ"), str, QMessageBox::Yes);
}

//��ʾ��ɴ��찴ť�ۺ���
void KMainWindow::onTodoDoneBtnClicked()
{
	if (ui.done_tableView->isVisible())
	{
		ui.done_tableView->setVisible(false);
		ui.btn_doneTodo->setIcon(QIcon(":/images/unfold.png"));
		ui.btn_doneTodo->setText(QStringLiteral("��ʾ�����"));
	}
	else
	{
		
		ui.done_tableView->setVisible(true);
		refeshDoneTableView();
		ui.btn_doneTodo->setIcon(QIcon(":/images/fold.png"));
		ui.btn_doneTodo->setText(QStringLiteral("���������"));
	}
}

//�ҵ���ҳ
void KMainWindow::onHomePageBtnClicked()
{
	m_currentGroupRow = -1;
	ui.stackedWidget->setCurrentIndex(0);
	if (ui.frame_edit->isVisible())
	{
		ui.frame_edit->setVisible(false);
	}
	if (ui.btn_order->isVisible())
	{
		ui.btn_order->setVisible(false);
	}
}

//�ҵĴ��찴ť�ۺ���
void KMainWindow::onMyTodoBtnClicked()
{
	if (!ui.btn_order->isVisible())
	{
		ui.btn_order->setVisible(true);
	}
	ui.label_title->setText(QStringLiteral("�ҵĴ���"));
	ui.stackedWidget->setCurrentIndex(1); 
	m_currentGroupRow = -1; refeshTodoTableView();

}

//GroupTableView��ʼ��
void KMainWindow::initGroupTableView()
{
	//��ʼ��group������ģ��
	m_groupModel = new QSqlTableModel(this);	
	m_groupModel->setTable("groups");
	m_groupModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_groupModel->select();

	//tableView����
	ui.groupTableView->setModel(m_groupModel);
	ui.groupTableView->setColumnWidth(1, 300);
	ui.groupTableView->setColumnHidden(0, true);
	ui.groupTableView->setSelectionMode(QAbstractItemView::NoSelection);


	//����tableview��ʾ����
	for (int row = 0; row < m_groupModel->rowCount(); row++)
	{
		QModelIndex index = m_groupModel->index(row, 1);
		
		//int id = m_groupModel->index(row, 0).data().toInt();
		QFrame* frame = initGroupItemWidget(index);
		//m_group[id] = frame;
		ui.groupTableView->setIndexWidget(index, frame);
	}
}

//��ʼ��GroupTableView��Ԫ�񴰿�
QFrame* KMainWindow::initGroupItemWidget(QModelIndex& index)
{
	//tableView����
	QFrame* frame = new QFrame(ui.groupTableView);
	frame->setGeometry(0, 0, 300, 40);
	frame->setStyleSheet("QFrame:hover{background-color: rgb(244,245,247);}");
	
	//1.���鰴ť
	QPushButton* btnGroup = new QPushButton(index.data().toString(), frame);
	btnGroup->setFixedWidth(270);
	btnGroup->setFixedHeight(40);
	btnGroup->setIcon(QIcon(":/images/group.png"));
	btnGroup->setIconSize(QSize(24, 24));
	btnGroup->setStyleSheet("QPushButton{font-size:14pt;font-family:Microsoft YaHei;padding-left:30px;}");

	//2.�༭��ť
	QPushButton* btnEdit = new QPushButton(frame);
	btnEdit->setFixedWidth(30);
	btnEdit->setFixedHeight(40);
	btnEdit->setIcon(QIcon(":/images/more.png"));
	btnEdit->setIconSize(QSize(20,20));
	//��Ӳ˵�
	QMenu* menu = new QMenu(frame);
	QAction*renameAction =  menu->addAction(QStringLiteral("������"));
	menu->addSeparator();
	QAction* deleteAction = menu->addAction(QStringLiteral("ɾ��"));
	btnEdit->setMenu(menu);
	btnEdit->setStyleSheet("QPushButton::menu-indicator{image:none}");
	

	//3.��Ӳ���
	QHBoxLayout* layout = new QHBoxLayout(frame);
	layout->setContentsMargins(0, 5, 0, 5);
	layout->addWidget(btnGroup);
	layout->addWidget(btnEdit);
	
	//4.�ź����
	(void)connect(btnGroup, &QPushButton::clicked, this, &KMainWindow::onGroupBtnClicked);
	(void)connect(btnEdit, &QPushButton::released, this, &KMainWindow::onEditGroupBtnReleased);
	(void)connect(renameAction, &QAction::triggered, this, &KMainWindow::onRenameActionTriggered);
	(void)connect(deleteAction, &QAction::triggered, this, &KMainWindow::onDeleteActionTriggered);

	return frame;
}

//ˢ��groupTableView��ʾ����
void KMainWindow::refreshGroupTableView()
{

	for (int row = 0; row < m_groupModel->rowCount(); row++)
	{
		QModelIndex index = m_groupModel->index(row, 1);

		QFrame* frame = initGroupItemWidget(index);
		ui.groupTableView->setIndexWidget(index, frame);
	}
}

//��ӷ���ۺ���
void KMainWindow::onAddGroupBtnClicked()
{
	bool ok;
	QString str = QInputDialog::getText(this, QStringLiteral("�½��������"), QStringLiteral("������"),
		QLineEdit::Normal, "", &ok);
	if (!ok)
		return;
	//�������ݿ�
	QSqlRecord record = m_groupModel->record();
	if (str.isEmpty())
	{
		remind(QStringLiteral("������Ϊ�գ��������ʧ�ܣ�"));
		return;
	}
	record.setValue("g_name", str);
	bool insertModelOk = m_groupModel->insertRecord(-1, record);
	bool insertDbOk = m_groupModel->submitAll();
	refreshGroupTableView();
}

//���鰴ť�ۺ���
void KMainWindow::onGroupBtnClicked()
{
	if (!ui.btn_order->isVisible())
	{
		ui.btn_order->setVisible(true);
	}

	QPushButton* button = qobject_cast<QPushButton*>(sender());
	QPoint pos = button->mapTo(ui.groupTableView, QPoint(0, 0));
	m_currentGroupRow = ui.groupTableView->rowAt(pos.y());
	
	//������ʾ
	QString groupName = m_groupModel->record(m_currentGroupRow).value("g_name").toString();
	ui.label_title->setText(groupName);
	ui.stackedWidget->setCurrentIndex(1);
		
	refeshTodoTableView();

}

//�����������ۺ���
void KMainWindow::onRenameActionTriggered()
{
	bool ok;
	QString str = QInputDialog::getText(this, QStringLiteral("����������"), QStringLiteral("������"),
		QLineEdit::Normal, "", &ok);
	if (!ok)
		return;

	QModelIndex index = m_groupModel->index(m_currentGroupRow, 1);
	m_groupModel->setData(index, str);
	m_groupModel->submitAll();
	refreshGroupTableView();
}

//ɾ������ۺ���
void KMainWindow::onDeleteActionTriggered()
{
	int res = QMessageBox::question(this, QStringLiteral("ɾ��"), QStringLiteral("�Ƿ�ɾ����"), QMessageBox::Yes, QMessageBox::No);
	if (QMessageBox::Yes != res)
	{
		remind(QStringLiteral("ɾ��ʧ�ܣ�"));
		return;
	}
	m_groupModel->removeRow(m_currentGroupRow);

	if (m_groupModel->submitAll())
		refreshGroupTableView();
}

//�༭��ť�ۺ���
void KMainWindow::onEditGroupBtnReleased()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	QPoint pos = button->mapTo(ui.groupTableView, QPoint(0, 0));
	m_currentGroupRow = ui.groupTableView->rowAt(pos.y());
	qDebug() << m_currentGroupRow;

}

//TodoTableView��ʼ��
void KMainWindow::initTodoTableVIew()
{
	//��ʼ��todo������ģ��
	m_todoModel = new QSqlTableModel(this);
	m_todoModel->setTable("todo");
	m_todoModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_todoModel->select();

	//tableView����
	ui.todo_tableView->setModel(m_todoModel);
	ui.todo_tableView->setColumnWidth(1, 830);
	ui.todo_tableView->setColumnHidden(0, true);
	ui.todo_tableView->setColumnHidden(2, true);
	ui.todo_tableView->setColumnHidden(3, true);
	ui.todo_tableView->setColumnHidden(4, true);
	ui.todo_tableView->setColumnHidden(5, true);
	ui.todo_tableView->setColumnHidden(6, true);
	ui.todo_tableView->setColumnHidden(7, true);
	ui.todo_tableView->setColumnHidden(8, true);
	ui.todo_tableView->setColumnHidden(9, true);
	ui.todo_tableView->setColumnHidden(10, true);
	ui.todo_tableView->setColumnHidden(11, true);
	ui.todo_tableView->setSelectionMode(QAbstractItemView::NoSelection);




}

//��ʼ��todoTableView��Ԫ�񴰿�
QFrame* KMainWindow::initTodoitemWidget(QModelIndex& index,int& row)
{
	QSqlRecord record = m_todoModel->record(row);
	QString endDateStr = record.value("t_enddate").toString();
	QString repStr = record.value("t_repetition").toString();
	QString remindDateStr = record.value("t_reminddate").toString();
	int priority = record.value("t_priority").toInt();
	QString priStr;
	switch (priority)
	{
	case 1:
		priStr = "!!! ";
		break;
	case 2:
		priStr = "!! ";
		break;
	case 3:
		priStr = "! ";
		break;
	default:
		break;
	}

	QFrame* frame = new QFrame(ui.todo_tableView);
	frame->setGeometry(0, 0, 830, 90);
	frame->setStyleSheet("QFrame:hover{background-color: rgb(244,245,247);}"
						"QCheckBox,QLabel,QPushButton{font-size:9pt;font-family:Microsoft YaHei;}"
						"QLabel,QPushButton{color:#8B97AF;}");

	//1.checkBox
	QCheckBox* checkBox = new QCheckBox(priStr+index.data().toString(), frame);
	checkBox->setFixedSize(QSize(150, 30));

	//2.����ʱ��label
	QLabel* endDateLabel = new QLabel(frame);
	endDateLabel->setFixedSize(QSize(150, 30));
	if (endDateStr.isEmpty())
	{
		endDateLabel->setVisible(false);
	}
	else
	{
		endDateLabel->setVisible(true);
		endDateLabel->setText(endDateStr);
	}


	//3.�����ظ�btn
	QPushButton* btnrep = new QPushButton(frame);
	btnrep->setFixedSize(QSize(170, 30));
	btnrep->setIcon(QIcon(":/images/remind.png"));
	btnrep->setIconSize(QSize(22, 22));
	btnrep->setEnabled(false);
	if (repStr.isEmpty())
	{
		btnrep->setVisible(false);
	}
	else
	{
		btnrep->setVisible(true);
		btnrep->setText(repStr);
	}

	//4.�����¼�btn
	QPushButton* btnRemind = new QPushButton(frame);
	btnRemind->setFixedSize(QSize(170, 30));
	btnRemind->setIcon(QIcon(":/images/notice.png"));
	btnRemind->setIconSize(QSize(22, 22));
	btnrep->setEnabled(false);
	if (remindDateStr.isEmpty())
	{
		btnRemind->setVisible(false);
	}
	else
	{
		btnRemind->setVisible(true);
		btnRemind->setText(remindDateStr);
	}

	//5.���ò���
	QHBoxLayout* hLayoutUp = new QHBoxLayout();
	QSpacerItem* hspacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hLayoutUp->addWidget(checkBox);
	hLayoutUp->addSpacerItem(hspacer1);
	hLayoutUp->setContentsMargins(15, 0, 0, 0);

	QHBoxLayout* hLayoutDown = new QHBoxLayout();
	QSpacerItem* hspacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hLayoutDown->addWidget(endDateLabel);
	hLayoutDown->addWidget(btnrep);
	hLayoutDown->addWidget(btnRemind);
	hLayoutDown->addSpacerItem(hspacer2);
	hLayoutDown->setContentsMargins(35, 0, 0, 0);

	QVBoxLayout* vLayout = new QVBoxLayout(frame);
	vLayout->addLayout(hLayoutUp);
	vLayout->addLayout(hLayoutDown);
	vLayout->setContentsMargins(0, 10, 0, 10);
	
	frame->setLayout(vLayout);

	//�ź����
	(void)connect(checkBox, &QCheckBox::stateChanged, this, &KMainWindow::onTodoCheckBoxStateChanged);
	return frame;
}

//ˢ�´�����ʾ
void KMainWindow::refeshTodoTableView()
{
	int currentGroupId = -1 == m_currentGroupRow ? -1 : m_groupModel->record(m_currentGroupRow).value("id").toInt();
	m_todoModel->setFilter(QString("t_done = \'0\' and t_groupid = \'%1\'").arg(currentGroupId));
	m_todoModel->select();

	for (int row=0;row<m_todoModel->rowCount();++row)
	{
		QModelIndex index = m_todoModel->index(row,1);
		QFrame* frame = initTodoitemWidget(index,row);
		ui.todo_tableView->setIndexWidget(index, frame);

	}
}


//TodoDoneTableView��ʼ��
void KMainWindow::initTodoDoneTableVIew()
{

	m_todoDoneModel = new QSqlTableModel(this);
	m_todoDoneModel->setTable("todo");
	m_todoDoneModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_todoDoneModel->select();

	ui.done_tableView->setVisible(false);
	ui.done_tableView->setSelectionMode(QAbstractItemView::NoSelection);
	ui.done_tableView->setModel(m_todoDoneModel);
	ui.done_tableView->setColumnWidth(1, 830);
	ui.done_tableView->setColumnHidden(0, true);
	ui.done_tableView->setColumnHidden(2, true);
	ui.done_tableView->setColumnHidden(3, true);
	ui.done_tableView->setColumnHidden(4, true);
	ui.done_tableView->setColumnHidden(5, true);
	ui.done_tableView->setColumnHidden(6, true);
	ui.done_tableView->setColumnHidden(7, true);
	ui.done_tableView->setColumnHidden(8, true);
	ui.done_tableView->setColumnHidden(9, true);
	ui.done_tableView->setColumnHidden(10, true);
	ui.done_tableView->setColumnHidden(11, true);


}

//��ʼ��TodoDoneTableView��Ԫ�񴰿�
QFrame* KMainWindow::initTodoDoneItemWidget(QModelIndex& index,int& row)
{
	
	QSqlRecord record = m_todoDoneModel->record(row);
	QString labelText = record.value("t_donedate").toString() + QStringLiteral("�������");

	QFrame* frame = new QFrame(ui.done_tableView);
	frame->setStyleSheet("QFrame:hover{background-color: rgb(244,245,247);}"
						 "QCheckBox,QLabel{font-size:9pt;font-family:Microsoft YaHei;color:#8B97AF;}"
						 "QCheckBox{text-decoration: line-through;}");


	QCheckBox* checkBox = new QCheckBox(frame);
	checkBox->setFixedSize(QSize(150, 30));
	checkBox->setChecked(true);
	checkBox->setEnabled(false);
	checkBox->setText(index.data().toString());

	QLabel* label = new QLabel(frame);
	label->setFixedSize(QSize(200, 30));
	label->setText(labelText);

	QHBoxLayout* hLayout = new QHBoxLayout(frame);
	QSpacerItem* hspacer = new QSpacerItem(40, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hLayout->addWidget(checkBox);
	hLayout->addWidget(label);
	hLayout->addSpacerItem(hspacer);
	hLayout->setContentsMargins(15, 5, 0, 5);

	frame->setLayout(hLayout);
	return frame;
}

//ˢ������ɴ�����ʾ
void KMainWindow::refeshDoneTableView()
{
	int currentGroupId = -1 == m_currentGroupRow ? -1 : m_groupModel->record(m_currentGroupRow).value("id").toInt();
	m_todoDoneModel->setFilter(QString("t_done = \'1\' and t_groupid = \'%1\'").arg(currentGroupId));
	m_todoDoneModel->select();

	for (int row = 0;row< m_todoDoneModel->rowCount();++row)
	{
		QModelIndex index = m_todoDoneModel->index(row, 1);
		QFrame* frame = initTodoDoneItemWidget(index,row);
		ui.done_tableView->setIndexWidget(index, frame);

	}

}

//��ɴ���
void KMainWindow::onTodoCheckBoxStateChanged()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString formatTime = currentTime.toString(QStringLiteral("MM��dd��dddd"));

	QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
	QPoint pos = checkBox->mapTo(ui.todo_tableView, QPoint(0, 0));
	int currentTodoTableRow = ui.todo_tableView->rowAt(pos.y());

	QModelIndex doneFlagIndex = m_todoModel->index(currentTodoTableRow, 7);
	QModelIndex doneTimeIndex = m_todoModel->index(currentTodoTableRow, 11);


	m_todoModel->setData(doneFlagIndex, 1);
	m_todoModel->setData(doneTimeIndex, formatTime);
	m_todoModel->submitAll();

	refeshTodoTableView();
	refeshDoneTableView();

}

//��Ӵ����¼�
void KMainWindow::onAddTodoItem()
{
	QString todoName = ui.lineEdit_addtodo->text().simplified();
	int groupId = m_currentGroupRow == -1 ? -1 : m_groupModel->record(m_currentGroupRow).value("id").toInt();
	if (todoName.isEmpty())
		return;
	
	QSqlRecord record = m_todoModel->record();
	record.setValue("t_name", todoName);
	record.setValue("t_done", 0);
	record.setValue("t_groupid", groupId);
	
	m_todoModel->insertRecord(-1, record);
	m_todoModel->submitAll();
	refeshTodoTableView();

	ui.lineEdit_addtodo->setText("");



}

//todoTableView�е���ۺ���
void KMainWindow::onTodoTableViewClicked(const QModelIndex& index)
{
	m_tableViewFlag = 0;

	if (!ui.frame_edit->isVisible())
	{
		ui.frame_edit->setVisible(true);
	}

	m_TodoTableViewRow = index.row();

	QSqlRecord record = m_todoModel->record(index.row());
	QString name = record.value("t_name").toString();
	int todoPriority = record.value("t_priority").toInt();
	QString endDate = record.value("t_enddate").toString();
	QString remindDate = record.value("t_reminddate").toString();
	QString description = record.value("t_descr").toString();
	QString address = record.value("t_add").toString();
	QString remark = record.value("t_remark").toString();

	ui.checkBox_name->setText(name);
	ui.comboBox->setCurrentIndex(todoPriority);
	if(!endDate.isEmpty())
		ui.btn_endDate->setText(endDate);
	else
		ui.btn_endDate->setText(QStringLiteral("���õ���ʱ��"));
	
	if (!remindDate.isEmpty())
		ui.btn_remind->setText(remindDate);
	else
		ui.btn_remind->setText(QStringLiteral("��������"));
	
	if (!description.isEmpty())
		ui.btn_describ->setText(description);
	else
		ui.btn_describ->setText(QStringLiteral("�������"));
	
	if (!address.isEmpty())
		ui.btn_address->setText(address);
	else
		ui.btn_address->setText(QStringLiteral("��ӵص�"));

	
	if (!remark.isEmpty())
		ui.btn_remark->setText(remark);
	else
		ui.btn_remark->setText(QStringLiteral("��ӱ�ע"));

	//refeshTodoTableView();




}

//doneTableView�е���ۺ���
void KMainWindow::onDoneTableViewClicked(const QModelIndex& index)
{


	m_tableViewFlag = 1;

	if (!ui.frame_edit->isVisible())
	{
		ui.frame_edit->setVisible(true);
	}

	m_TodoTableViewRow = index.row();



	ui.checkBox_name->setChecked(true);
	QSqlRecord record = m_todoDoneModel->record(index.row());
	QString name = record.value("t_name").toString();
	int todoPriority = record.value("t_priority").toInt();
	QString endDate = record.value("t_enddate").toString();
	QString remindDate = record.value("t_reminddate").toString();
	QString description = record.value("t_descr").toString();
	QString address = record.value("t_add").toString();
	QString remark = record.value("t_remark").toString();

	ui.checkBox_name->setText(name);
	ui.comboBox->setCurrentIndex(todoPriority);
	if (!endDate.isEmpty())
		ui.btn_endDate->setText(endDate);
	else
		ui.btn_endDate->setText(QStringLiteral("���õ���ʱ��"));

	if (!remindDate.isEmpty())
		ui.btn_remind->setText(remindDate);
	else
		ui.btn_remind->setText(QStringLiteral("��������"));

	if (!description.isEmpty())
		ui.btn_describ->setText(description);
	else
		ui.btn_describ->setText(QStringLiteral("�������"));

	if (!address.isEmpty())
		ui.btn_address->setText(address);
	else
		ui.btn_address->setText(QStringLiteral("��ӵص�"));


	if (!remark.isEmpty())
		ui.btn_remark->setText(remark);
	else
		ui.btn_remark->setText(QStringLiteral("��ӱ�ע"));

	if (!ui.frame_edit->isVisible())
	{
		ui.frame_edit->setVisible(true);
	}
	refeshDoneTableView();
}

//�������ʱ��༭
void KMainWindow::onEditEndDateBtnClicked()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	QDialog* dialog = new QDialog(this);
	dialog->setWindowTitle(QStringLiteral("���õ���ʱ��"));
	dialog->setGeometry(1460,360, 270, 370);
	dialog->setFixedSize(270, 370);
	dialog->setStyleSheet("*{background-color:white;}"
						"QDialog{border:1px solid rgb(232,235,239);}"
						"QPushButton{border-radius:3px;font-size:10pt;font-family:Microsoft YaHei;border:1px solid rgb(232,235,239);text-align: center;}");
	//dialog->setWindowFlags(Qt::FramelessWindowHint);
	
	QCalendarWidget* calendar = new QCalendarWidget(dialog);
	calendar->setGeometry(0, 0, 270, 270);
	calendar->setFixedSize(260, 260);


	QComboBox* comboBox = new QComboBox(dialog);
	QStringList strList{ QStringLiteral("�����ظ�"), QStringLiteral("ÿ���ظ�"),QStringLiteral("ÿ���ظ�"),QStringLiteral("ÿ���ظ�") };
	comboBox->setGeometry(10, 280, 150, 30);
	comboBox->setFixedSize(100, 30);
	comboBox->addItems(strList);
	
	QPushButton* btnOk = new QPushButton(dialog);
	btnOk->setText(QStringLiteral("ȷ��"));
	btnOk->setGeometry(10, 320, 120, 40);
	btnOk->setFixedSize(120, 40);
	btnOk->setStyleSheet("QPushButton{background-color:rgb(4,184,174);}");
	QPushButton* btnCancle = new QPushButton(dialog);
	btnCancle->setText(QStringLiteral("ȡ��"));
	btnCancle->setGeometry(140, 320, 120,40);
	btnCancle->setFixedSize(120, 40);


	//�ź����
	connect(btnOk, &QPushButton::clicked, [&] 
		{
			QDate selectDate = calendar->selectedDate();
			QString endDate= selectDate.toString(QStringLiteral("MM��dd��dddd"));
			QString repStr;
			if (0 != comboBox->currentIndex())
				repStr = comboBox->currentText();
			else
				repStr = "";
			QModelIndex indexEndDate = model->index(m_TodoTableViewRow, 2);
			model->setData(indexEndDate, endDate);
				
			QModelIndex indexRep = model->index(m_TodoTableViewRow, 8);
			model->setData(indexRep, repStr);

			model->submitAll();
			refeshTodoTableView();
			dialog->close();

		});
	connect(btnCancle, &QPushButton::clicked, [&] {dialog->close(); });
	dialog->exec();
}

//��������ʱ�䰴ť�ۺ���
void KMainWindow::onEditRemindTimeClicked()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	QDialog* dialog = new QDialog(this);
	dialog->setWindowTitle(QStringLiteral("��������ʱ��"));
	dialog->setGeometry(1460, 410, 270, 370);
	dialog->setFixedSize(270, 370);
	dialog->setStyleSheet("*{background-color:white;}"
		"QDialog{border:1px solid rgb(232,235,239);}"
		"QPushButton{border-radius:3px;font-size:10pt;font-family:Microsoft YaHei;border:1px solid rgb(232,235,239);text-align: center;}");
	//dialog->setWindowFlags(Qt::FramelessWindowHint);

	QCalendarWidget* calendar = new QCalendarWidget(dialog);
	calendar->setGeometry(0, 0, 270, 270);
	calendar->setFixedSize(260, 260);


	QLabel* label = new QLabel(QStringLiteral("����ʱ��"), dialog);
	label->setGeometry(10, 280, 70, 30);
	label->setFixedSize(100, 30);

	QTimeEdit* timeEdit = new QTimeEdit(dialog);
	timeEdit->setGeometry(90, 280, 100, 30);
	timeEdit->setFixedSize(100, 30);

	QPushButton* btnOk = new QPushButton(dialog);
	btnOk->setText(QStringLiteral("ȷ��"));
	btnOk->setGeometry(10, 320, 120, 40);
	btnOk->setFixedSize(120, 40);
	btnOk->setStyleSheet("QPushButton{background-color:rgb(4,184,174);}");
	QPushButton* btnCancle = new QPushButton(dialog);
	btnCancle->setText(QStringLiteral("ȡ��"));
	btnCancle->setGeometry(140, 320, 120, 40);
	btnCancle->setFixedSize(120, 40);

	//�ź����
	(void)connect(btnOk, &QPushButton::clicked, [&]
		{
			QDate selectDate = calendar->selectedDate();
			QString remindDate = selectDate.toString(QStringLiteral("MM��dd��"));
			QTime time = timeEdit->time();
			QString timeStr = time.toString("HH:mm");

			QModelIndex index = model->index(m_TodoTableViewRow, 3);
			model->setData(index, remindDate+timeStr);
			model->submitAll();
			refeshTodoTableView();
			dialog->close();

		});
	(void)connect(btnCancle, &QPushButton::clicked, [&] {dialog->close(); });

	dialog->exec();


}

//�����༭
void KMainWindow::onDescribBtnClicked()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	bool ok;
	QString str = QInputDialog::getText(this, QStringLiteral("�������"), QStringLiteral("����"),
		QLineEdit::Normal, "", &ok);
	if (!ok)
		return;
	QModelIndex index = model->index(m_TodoTableViewRow, 4);
	model->setData(index, str);
	model->submitAll();
	refeshTodoTableView();
	ui.btn_describ->setText(str);

}

//�ص�༭
void KMainWindow::onAddressBtnClicked()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	bool ok;
	QString str = QInputDialog::getText(this, QStringLiteral("��ӵص�"), QStringLiteral("�ص�"),
		QLineEdit::Normal, "", &ok);
	if (!ok)
		return;
	QModelIndex index = model->index(m_TodoTableViewRow, 5);
	model->setData(index, str);
	model->submitAll();
	refeshTodoTableView();
	ui.btn_address->setText(str);

}

//��ע�༭
void KMainWindow::onRemarkBtnClicked()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	bool ok;
	QString str = QInputDialog::getText(this, QStringLiteral("��ӱ�ע"), QStringLiteral("��ע"),
		QLineEdit::Normal, "", &ok);
	if (!ok)
		return;
	QModelIndex index = model->index(m_TodoTableViewRow, 6);
	model->setData(index, str);
	model->submitAll();
	refeshTodoTableView();
	ui.btn_remark->setText(str);

}

//������ɱ༭
void KMainWindow::onTodoDoneCheckBoxStateChanged()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	QDateTime currentTime = QDateTime::currentDateTime();
	QString formatTime = currentTime.toString(QStringLiteral("MM��dd��dddd"));
	int done;
	if (ui.checkBox_name->isChecked())
	{
		done = 1;
	}
	else
	{
		done = 0;
		formatTime = "";
	}
	QModelIndex index = model->index(m_TodoTableViewRow, 7);
	model->setData(index, done);
	model->submitAll();
	refeshTodoTableView();
	m_TodoTableViewRow = -1;  //�ı��Ƿ���ɺ����ڱ༭,��Ҫ����ѡ��
	ui.frame_edit->setVisible(false);
	refeshTodoTableView();
	refeshDoneTableView();
}

//�༭����Ȩ
void KMainWindow::onPriorityComboBoxIndexChanged()
{
	QSqlTableModel* model;
	if (0 == m_tableViewFlag)
		model = m_todoModel;
	else
		model = m_todoDoneModel;

	int comboboxIndex = ui.comboBox->currentIndex();
	QModelIndex index = model->index(m_TodoTableViewRow, 10);
	model->setData(index, comboboxIndex);
	model->submitAll();
	refeshTodoTableView();

}

//homeTableView��ʼ��
void KMainWindow::initHomeTableView()
{
	//tableView����
	m_homeModel = new QSqlTableModel(this);
	m_homeModel->setTable("todo");
	m_homeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_homeModel->select();

	ui.home_tableView->setModel(m_homeModel);

	ui.home_tableView->setColumnWidth(1, 830);
	ui.home_tableView->setColumnHidden(0, true);
	ui.home_tableView->setColumnHidden(2, true);
	ui.home_tableView->setColumnHidden(3, true);
	ui.home_tableView->setColumnHidden(4, true);
	ui.home_tableView->setColumnHidden(5, true);
	ui.home_tableView->setColumnHidden(6, true);
	ui.home_tableView->setColumnHidden(7, true);
	ui.home_tableView->setColumnHidden(8, true);
	ui.home_tableView->setColumnHidden(9, true);
	ui.home_tableView->setColumnHidden(10, true);
	ui.home_tableView->setColumnHidden(11, true);
	ui.home_tableView->setSelectionMode(QAbstractItemView::NoSelection);


}

//��ʼ����Ԫ�񴰿�
QFrame* KMainWindow::initHomeItemWidget(QModelIndex& index, int& row)
{
	QSqlRecord record = m_homeModel->record(row);
	QString endDateStr = record.value("t_enddate").toString();
	QString repStr = record.value("t_repetition").toString();
	QString remindDateStr = record.value("t_reminddate").toString();
	int priority = record.value("t_priority").toInt();
	QString priStr;
	switch (priority)
	{
	case 1:
		priStr = "!!! ";
		break;
	case 2:
		priStr = "!! ";
		break;
	case 3:
		priStr = "! ";
		break;
	default:
		break;
	}

	QFrame* frame = new QFrame(ui.home_tableView);
	frame->setGeometry(0, 0, 830, 90);
	frame->setStyleSheet("QFrame:hover{background-color: rgb(244,245,247);}"
		"QCheckBox,QLabel,QPushButton{font-size:9pt;font-family:Microsoft YaHei;}"
		"QLabel,QPushButton{color:#8B97AF;}");

	//1.checkBox
	QCheckBox* checkBox = new QCheckBox(priStr+index.data().toString(), frame);
	checkBox->setFixedSize(QSize(150, 30));
	checkBox->setCheckable(false);

	//2.����ʱ��label
	QLabel* endDateLabel = new QLabel(frame);
	endDateLabel->setFixedSize(QSize(150, 30));
	if (endDateStr.isEmpty())
	{
		endDateLabel->setVisible(false);
	}
	else
	{
		endDateLabel->setVisible(true);
		endDateLabel->setText(endDateStr);
	}


	//3.�����ظ�btn
	QPushButton* btnrep = new QPushButton(frame);
	btnrep->setFixedSize(QSize(170, 30));
	btnrep->setIcon(QIcon(":/images/remind.png"));
	btnrep->setIconSize(QSize(22, 22));
	btnrep->setEnabled(false);
	if (repStr.isEmpty())
	{
		btnrep->setVisible(false);
	}
	else
	{
		btnrep->setVisible(true);
		btnrep->setText(repStr);
	}

	//4.�����¼�btn
	QPushButton* btnRemind = new QPushButton(frame);
	btnRemind->setFixedSize(QSize(170, 30));
	btnRemind->setIcon(QIcon(":/images/notice.png"));
	btnRemind->setIconSize(QSize(22, 22));
	btnrep->setEnabled(false);
	if (remindDateStr.isEmpty())
	{
		btnRemind->setVisible(false);
	}
	else
	{
		btnRemind->setVisible(true);
		btnRemind->setText(remindDateStr);
	}

	//5.���ò���
	QHBoxLayout* hLayoutUp = new QHBoxLayout();
	QSpacerItem* hspacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hLayoutUp->addWidget(checkBox);
	hLayoutUp->addSpacerItem(hspacer1);
	hLayoutUp->setContentsMargins(15, 0, 0, 0);

	QHBoxLayout* hLayoutDown = new QHBoxLayout();
	QSpacerItem* hspacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hLayoutDown->addWidget(endDateLabel);
	hLayoutDown->addWidget(btnrep);
	hLayoutDown->addWidget(btnRemind);
	hLayoutDown->addSpacerItem(hspacer2);
	hLayoutDown->setContentsMargins(35, 0, 0, 0);

	QVBoxLayout* vLayout = new QVBoxLayout(frame);
	vLayout->addLayout(hLayoutUp);
	vLayout->addLayout(hLayoutDown);
	vLayout->setContentsMargins(0, 10, 0, 10);

	frame->setLayout(vLayout);

	//�ź����
	return frame;
}

void KMainWindow::refreshHomeTableView(int flag)
{
	// ��ȡ��ǰ����
	QDate currentDate = QDate::currentDate();
	// ��������������
	QDate sevenDaysAgo = currentDate.addDays(7);
	switch (flag)
	{
	case 1:
		m_homeModel->setFilter(QString("t_done = \'0\' and t_groupid = \'-1\' and t_enddate IS NULL "));
		m_homeModel->select();
		break;
	case 2:
		m_homeModel->setFilter(QString("t_done = \'0\' and t_groupid = \'-1\'and t_enddate <= \'%1\'").arg(sevenDaysAgo.toString(QStringLiteral("MM��dd��ddd"))));
		m_homeModel->select();
		break;
	case 3:
		m_homeModel->setFilter(QString("t_done = \'0\' and t_groupid = \'-1\'and t_enddate > \'%1\'").arg(sevenDaysAgo.toString(QStringLiteral("MM��dd��ddd"))));
		m_homeModel->select();
		break;
	default:
		break;
	}

	qDebug() << m_homeModel->rowCount();
	for (int row = 0; row < m_homeModel->rowCount(); ++row)
	{
		QModelIndex index = m_homeModel->index(row, 1);
		QFrame* frame = initHomeItemWidget(index, row);
		ui.home_tableView->setIndexWidget(index, frame);

	}
}

//��ҳˢ��
void KMainWindow::onRefreshBtnClicked()
{
	int currentIndex = ui.stackedWidget->currentIndex();
	switch (currentIndex)
	{
	case 0:
		onNOArrangeBtnClicked();
		refreshHomeTableView(1);
		break;
	case 1:		
		refeshTodoTableView();
		break;
	default:
		break;
	}

}

//����ʱ������
void KMainWindow::onEndDateOrderActionTriggered()
{
	m_todoModel->setSort(2, Qt::AscendingOrder);
	refeshTodoTableView();
}

//����ʱ������
void KMainWindow::onCreateDateOrderActionTriggered()
{

	m_todoModel->setSort(0, Qt::AscendingOrder);
	refeshTodoTableView();

}

//����Ȩ����
void KMainWindow::onPriorityOrderActionTriggered()
{
	m_todoModel->setSort(10, Qt::AscendingOrder);
	refeshTodoTableView();
}
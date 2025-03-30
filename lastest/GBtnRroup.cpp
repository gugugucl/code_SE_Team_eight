#include "GBtnRroup.h"
#include "ui_GBtnRroup.h"
#include <QKeyEvent>
#include <QDebug>
#include <QSqlError>
#include <QLineEdit>
GBtnGroup::GBtnGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GBtnGroup)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    popMenu = new QMenu(this);

    // 添加“修改该组”菜单项
    QAction *modifyGroup = new QAction(popMenu);
    modifyGroup->setIcon(QIcon(":/image/mod.png"));
    modifyGroup->setText(tr("修改该组"));
    connect(modifyGroup, SIGNAL(triggered()), this, SLOT(on_btnModify_clicked()));

    // 添加“删除该记录”菜单项
    QAction *deleteRecord = new QAction(popMenu);
    deleteRecord->setIcon(QIcon(":/image/del.png"));
    deleteRecord->setText(tr("删除该记录"));
    connect(deleteRecord, SIGNAL(triggered(bool)), this, SLOT(on_btnDelete_clicked()));

    // 在两个菜单项之间添加一个分隔符
    popMenu->addAction(modifyGroup);
    popMenu->insertSeparator(deleteRecord);
    popMenu->addAction(deleteRecord);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(sltShowPopMenu(const QPoint&)));
    ui->pushButton->installEventFilter(this);

}
void GBtnGroup::on_btnModify_clicked()
{
    qDebug() << "sltPopMenuTriggered is called";
    if(!popMenu) return;

    // 获取当前绑定的按钮对象指针
    QWidget* parentWidget = popMenu->parentWidget();
    QPushButton* button = nullptr;
    if(parentWidget)
    {
        QList<QPushButton*> buttons = parentWidget->findChildren<QPushButton*>();
        if(!buttons.isEmpty())
        {
            button = buttons.first();
        }
    }

    if(button)
    {
        QString text = button->text();

        QLineEdit *lineEdit = new QLineEdit(text, this);
        QFont font = button->font();
        lineEdit->setFont(font);
        lineEdit->setAlignment(Qt::AlignCenter);

        QRect geom = button->geometry();
        lineEdit->move(geom.topLeft());
        lineEdit->resize(geom.width(), geom.height());

        lineEdit->show();
        lineEdit->setFocus();

        connect(lineEdit, &QLineEdit::editingFinished, [=]() {
            QString newText = lineEdit->text();

            // 将 newText 更新到数据库中
            QSqlQuery query;
            if(query.exec(QString("update groupName set groupName='%1' where groupName='%2'")
                        .arg(newText).arg(text)))
            {
                button->setText(newText);

                lineEdit->hide();
                lineEdit->deleteLater();

                m_editingButton = nullptr;
            }
            else
            {
                qDebug() << "update failed:" << query.lastError().text();
                QMessageBox::information(this,tr("更新提示"),tr("更新失败"));
            }

        });

        m_editingButton = button;
    }
}
bool GBtnGroup::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        QPushButton *button = qobject_cast<QPushButton*>(obj);
        if (button != nullptr) {
            on_button_doubleClicked(button);
            return true;
        }
    }
    return false;
}

void GBtnGroup::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (m_editingButton != nullptr) {
            QString newText = m_editingButton->text();

            // 将 newText 更新到数据库中
            // ...

            m_editingButton = nullptr;
        }
    } else {
        QWidget::keyPressEvent(event);
    }
}


void GBtnGroup::on_button_doubleClicked(QPushButton *button)
{
    QString text = button->text();

    QLineEdit *lineEdit = new QLineEdit(text, this);
    QFont font = button->font();
    lineEdit->setFont(font);
    lineEdit->setAlignment(Qt::AlignCenter);

    QRect geom = button->geometry();
    lineEdit->move(geom.topLeft());
    lineEdit->resize(geom.width(), geom.height());

    lineEdit->show();
    lineEdit->setFocus();

    connect(lineEdit, &QLineEdit::editingFinished, [=]() {
        QString newText = lineEdit->text();

        // 将 newText 更新到数据库中
        QSqlQuery query;
        if(query.exec(QString("update groupName set groupName='%1' where groupName='%2'")
                      .arg(newText).arg(text)))
        {
            button->setText(newText);

            lineEdit->hide();
            lineEdit->deleteLater();

            m_editingButton = nullptr;
        }
        else
        {
            qDebug() << "update failed:" << query.lastError().text();
            QMessageBox::information(this,tr("更新提示"),tr("更新失败"));
        }

    });

    m_editingButton = button;
}
void GBtnGroup::sltShowPopMenu(const QPoint& )//槽函数
{
    if(popMenu){
        popMenu->exec(QCursor::pos());
    }
}
GBtnGroup::~GBtnGroup()
{
    delete ui;
}

void GBtnGroup::setText(QString name)
{
    ui->pushButton->setText(name);
}

void GBtnGroup::on_pushButton_clicked()
{
    emit groupSwitch(ui->pushButton->text());
}

void GBtnGroup::on_btnDelete_clicked()
{
    QMessageBox mm(QMessageBox::Warning,QString(tr("警告")),QString(tr("你确定要删除吗？")),QMessageBox::Yes| QMessageBox::No);
    mm.setButtonText(QMessageBox::Yes,QString(tr("确认")));
    mm.button(QMessageBox::No)->setText(tr("取消"));
    int Ret = mm.exec();
    if(Ret == QMessageBox::Yes)
    {

        QSqlQuery query;
        if(query.exec(QString("delete from todolist where GpName = '%1';").arg(ui->pushButton->text())))
        {
            query.exec(QString("delete from groupName where groupName = '%1';").arg(ui->pushButton->text()));
            this->close();
        }
        else
        {
            QMessageBox::information(this,tr("删除提示"),tr("删除失败"));
        }
    }
}

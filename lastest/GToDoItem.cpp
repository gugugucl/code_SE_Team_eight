#include "GToDoItem.h"
#include "ui_GToDoItem.h"
#include "GToDo.h"
#include <QHash>
#include <QLabel>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTextCodec>
#include <QTextStream>
#include <QMenu>
#include <QSound>
#include <QTextCursor>
#include <QTemporaryFile>
#include <QAxObject>
#include <QThread>

extern QSqlDatabase db;
GToDoitem::GToDoitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GToDoitem)
{
    ui->setupUi(this);
    m_parent = parent;
    popMenu = new QMenu(this);
    QAction *aafilish = popMenu->addAction(QIcon(":/image/ok.png"), tr("完成标记"));

    connect(aafilish, &QAction::triggered, this, [=](){
        on_btnFinish_clicked();
    });
    QAction *addDir = popMenu->addAction(QIcon(":/image/write.png"), tr("修改该记录"));
    connect(addDir, &QAction::triggered, this, [=](){
        on_lbTitle_clicked();
    });
    QAction *addTemplate = popMenu->addAction(QIcon(":/image/del.png"), tr("删除该记录"));
    connect(addTemplate, &QAction::triggered, this, [=](){
        QMessageBox mm(QMessageBox::Warning,QString(tr("警告")),QString(tr("你确定要删除吗？")),QMessageBox::Yes| QMessageBox::No);
        mm.setButtonText(QMessageBox::Yes,QString(tr("确认")));
        mm.button(QMessageBox::No)->setText(tr("取消"));
        int Ret = mm.exec();
        if(Ret == QMessageBox::Yes)
        {
            QDate date;
            date=date.currentDate();

            QSqlQuery query;
            if(query.exec(QString("delete from todolist where Title = '%1';").arg(ui->lbTitle->text()))){

                this->close();
            }
            else
            {
                QMessageBox::information(this,tr("删除提示"),tr("删除失败"));
            }
        }
    });
    QAction *addDownload = popMenu->addAction(QIcon(":/image/download.png"), tr("下载该记录"));
    connect(addDownload, &QAction::triggered, this, [=](){
        on_pushButton_download_clicked();
    });
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(sltShowPopMenu(const QPoint&)));



}
void GToDoitem::sltShowPopMenu(const QPoint& )//槽函数
{
    if(popMenu){
        popMenu->exec(QCursor::pos());
    }
}
GToDoitem::~GToDoitem()
{
    delete ui;
}

void GToDoitem::setTitle(QString Title, int priority)
{
    ui->lbTitle->setText(Title);
    ui->lbTitle->setToolTip(Title);
    QPixmap icon;
    switch (priority) {
    case 0:
        icon.load(":/image/attention.png");
        ui->lbIcon->setToolTip("普通优先级任务");
        break;
    case 1:
        icon.load(":/image/attention_a.png");
         ui->lbIcon->setToolTip("低等优先级任务");
        break;
    case 2:
        icon.load(":/image/attention_b.png");
         ui->lbIcon->setToolTip("中等优先级任务");
        break;
    case 3:
        icon.load(":/image/attention_c.png");
         ui->lbIcon->setToolTip("高等优先级任务");
        break;
    default:
        break;
    }
    if(priority != -1)
    {
        icon = icon.scaled(40,40);
        ui->lbIcon->setIcon(icon);
        m_priority = priority;
    }
    else
    {
        icon.load(":/image/Finished.png");
        icon = icon.scaled(40,40);
        ui->lbTitle->setStyleSheet("color:gray");
        ui->lbDdl->setStyleSheet("color:gray");
        ui->lbRepate->setStyleSheet("color:gray");
        ui->lbRemind->setStyleSheet("color:gray");
        ui->lbIcon->setIcon(icon);
    }
}
void GToDoitem::setDDL(QString date)
{
    QDate deadline = QDate::fromString(date, "yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();

    qint64 daysDiff = currentDate.daysTo(deadline);

    if (daysDiff < 0) {
        ui->lbDdl->setText(tr("已过截止日期"));
    } else {
        QString dateString = deadline.toString("yyyy-MM-dd");
        QString year = dateString.left(4);
        dateString.replace(0, 4, year);
        QString ddlText = dateString;
        ui->lbDdl->setText(ddlText);
        if (daysDiff == 0) {
            ui->lbDdl->setStyleSheet("color: red");
        }
    }
    m_ddl = date;
}
void GToDoitem::setRepeat(int Repeat)
{
    switch (Repeat) {
    case 1:
        ui->lbRepate->setText(tr("每日重复"));
        break;
    case 2:
        ui->lbRepate->setText(tr("每周重复"));
        break;
    case 3:
        ui->lbRepate->setText(tr("每月重复"));
        break;
    case 4:
        ui->lbRepate->setText(tr("每年重复"));
        break;
    default:
        ui->lbRepate->setText(tr("不重复"));
        break;
    }
    m_repeat = Repeat;
}
void GToDoitem::setCrontab(int Crontab)
{

    switch (Crontab) {
    case 1:
        ui->pushButton_icon->setIcon(QIcon(":/image/a.png"));
        ui->lbCrontab->setToolTip("定时关机");
        ui->pushButton_icon->setToolTip("定时关机");
        ui->lbCrontab->setText(tr("关机"));
        break;
    case 2:
        ui->pushButton_icon->setIcon(QIcon(":/image/b.png"));
        ui->pushButton_icon->setToolTip("定时清理");
        ui->lbCrontab->setToolTip("定时清理");
        ui->lbCrontab->setText(tr("清理"));
        break;
    case 3:
        ui->pushButton_icon->setIcon(QIcon(":/image/c.png"));
        ui->lbCrontab->setText(tr("应用"));
             ui->lbCrontab->setToolTip("定时应用");
        ui->pushButton_icon->setToolTip("定时应用");
        break;
    case 4:
        ui->pushButton_icon->setIcon(QIcon(":/image/d.png"));
        ui->pushButton_icon->setToolTip("自定义任务");
         ui->lbCrontab->setToolTip("自定义任务");
        ui->lbCrontab->setText(tr("自定义"));
        break;
    default:
        ui->pushButton_icon->setIcon(QIcon(":/image/e.png"));
        ui->lbCrontab->setText(tr("不启用"));
          ui->pushButton_icon->setToolTip("不启用定时任务");
        ui->lbCrontab->setToolTip("不启用定时任务");
        break;
    }
    m_Crontab = Crontab;
}
void GToDoitem::setRemind(QString _datetime)
{
    QDateTime datetime = QDateTime::fromString(_datetime, "yyyy-MM-dd hh:mm");
    qint64 currentTimestamp = QDateTime::currentDateTimeUtc().toTime_t();
    qint64 RemindTimestamp = datetime.toTime_t();
    qint64 secDiff = RemindTimestamp - currentTimestamp;
    if (secDiff > 0) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]() {
            static QMessageNotification* notification = nullptr;
            static int timerCount = 0;
            if (notification != nullptr) {
                notification->close();
                notification = nullptr;
            }
            if (timerCount % 2 == 0) {
                timer->start(15000);
            } else {
                ui->lbRemind->setText(tr("将不再提醒该任务！"));
                timer->stop();
            }
            QSound::play(":/tips.wav");
            QIcon lbIcon =  ui->lbIcon->icon();
            QString title = ui->lbTitle->text();
            QString ddlText = ui->lbRemind->text();
            notification = new QMessageNotification(m_parent);
            notification->setNotificationIcon(lbIcon);
            notification->setNotificationTitle(title);
            notification->setNotificationDate(ddlText);
            notification->show();
            timerCount++;
        });
        timer->start(30000);
        ui->lbRemind->setText(datetime.toString("yyyy-MM-dd hh:mm"));
    } else {
        ui->lbRemind->setText(tr("已过提醒时间"));
    }
}
void GToDoitem::setFinishDate(QString date)
{
    ui->lbDdl->setText(GQStringToQDate::QStringFromat(date)+tr("完成"));
}
void GToDoitem::hideBtn()
{
    //ui->btnAlter->hide();
   // ui->btnFinish->hide();
}
void GToDoitem::init()
{

}

void GToDoitem::on_btnFinish_clicked()  // 点击打勾完成事项
{
    QDate date = QDate::currentDate();  // 获取当前日期  111修改  带小时分钟
    QSqlQuery query; //使用默認數據庫

    // 任务没有截止时间的情况
    if (ui->lbDdl->text() == tr("无截止时间"))
    {
        query.prepare("UPDATE todolist SET Finished = 1, FinishDate = :finishDate "
                      "WHERE Title = :title AND Deadline IS NULL AND Finished = 0;");
        query.bindValue(":finishDate", date.toString("yyyy-MM-dd"));  //改
        query.bindValue(":title", ui->lbTitle->text());

        if (query.exec())
        {
            this->close();
            if (ui->lbRepate->text() != tr("不重复"))
            {
                QMessageBox::information(this, tr("新建重复事件提示"), tr("新建失败，没有设置截止日期"));
            }
        }
        else
        {
            QMessageBox::information(this, tr("完成提示"), tr("完成失败：") + query.lastError().text());
            return;
        }
    }
    else
    {
        QString ddl = m_ddl;  // 任务的截止日期

        // 更新任务状态为已完成
        query.prepare("UPDATE todolist SET Finished = 1, FinishDate = :finishDate "
                      "WHERE Title = :title AND Deadline = :deadline AND Finished = 0;");
        query.bindValue(":finishDate", date.toString("yyyy-MM-dd"));//改
        query.bindValue(":title", ui->lbTitle->text());
        query.bindValue(":deadline", ddl);

        if (query.exec())
        {
            this->close();

            if (ui->lbRepate->text() != tr("不重复"))
            {
                QDate nextDdl = QDate::fromString(m_ddl, "yyyy-MM-dd"); //改

                // 根据重复类型计算下一个截止日期
                if (ui->lbRepate->text() == tr("每日重复"))
                {
                    nextDdl = nextDdl.addDays(1);
                }
                else if (ui->lbRepate->text() == tr("每周重复"))
                {
                    nextDdl = nextDdl.addDays(7);
                }
                else if (ui->lbRepate->text() == tr("每月重复"))
                {
                    nextDdl = nextDdl.addMonths(1);
                }
                else if (ui->lbRepate->text() == tr("每年重复"))
                {
                    nextDdl = nextDdl.addYears(1);
                }

                // 插入新的重复任务
                query.prepare("INSERT INTO todolist (Title, Deadline, Finished, priority, repeat, Crontab) "
                              "VALUES (:title, :deadline, 0, :priority, :repeat, :crontab);");
                query.bindValue(":title", ui->lbTitle->text());
                query.bindValue(":deadline", nextDdl.toString("yyyy-MM-dd"));  //改
                query.bindValue(":priority", m_priority);
                query.bindValue(":repeat", m_repeat);
                query.bindValue(":crontab", m_Crontab);

                if (!query.exec())
                {
                    QMessageBox::information(this, tr("新建重复事件提示"), tr("新建失败：") + query.lastError().text());
                }
            }
        }
        else
        {
            QMessageBox::information(this, tr("完成提示"), tr("完成失败：") + query.lastError().text());
            return;
        }
    }
}

//void GToDoitem::on_btnFinish_clicked()  //点击打勾 完成事项
//{
//    QDate date;
//    date=date.currentDate();
//    QSqlQuery query;
//    if(ui->lbDdl->text() == tr("无截止时间"))
//    {
//        if(query.exec(QString("update todolist set Finished = 1,FinishDate = '%1' where Title = '%2' and Deadline is null and Finished = 0;").arg(date.toString("yyyy-MM-dd")).arg(ui->lbTitle->text())))
//        {
//            this->close();
//            if(ui->lbRepate->text() != tr("不重复"))
//            {
//                QMessageBox::information(this,tr("新建重复事件提示"),tr("新建失败，没有设置截止日期"));
//            }
//        }
//        else
//        {
//            QMessageBox::information(this,tr("完成提示"),tr("完成失败"));
//            return;
//        }
//    }
//    else
//    {
//        QString ddl = m_ddl; // 保存任务的截止日期

//        // 标记任务为已完成状态
//        if(query.exec(QString("update todolist set Finished = 1,FinishDate = '%1' where Title = '%2' and Deadline = '%3' and Finished = 0;").arg(date.toString("yyyy-MM-dd")).arg(ui->lbTitle->text()).arg(ddl)))
//        {
//            this->close();
//            if(ui->lbRepate->text() != tr("不重复"))
//            {
//                QDate nextDdl = QDate::fromString(m_ddl,"yyyy-MM-dd");

//                // 根据任务重复类型计算下一个截止日期
//                if(ui->lbRepate->text() == tr("每日重复"))
//                {
//                    nextDdl=nextDdl.addDays(1);
//                }
//                else if(ui->lbRepate->text() == tr("每周重复"))
//                {
//                    nextDdl=nextDdl.addDays(7);
//                }
//                else if(ui->lbRepate->text() == tr("每月重复"))
//                {
//                    nextDdl=nextDdl.addMonths(1);
//                }
//                else if(ui->lbRepate->text() == tr("每年重复"))
//                {
//                    nextDdl=nextDdl.addYears(1);
//                }

//                // 生成新的任务记录
//                if(!query.exec(QString("insert into todolist (Title,Deadline,Finished,priority,repeat,Crontab) values ('%1','%2',0,%3,%4,%5);").arg(ui->lbTitle->text()).arg(nextDdl.toString("yyyy-MM-dd")).arg(m_priority).arg(m_repeat).arg(m_Crontab)))
//                {
//                    QMessageBox::information(this,tr("新建重复事件提示"),tr("新建失败"));
//                }
//            }

//        }
//        else
//        {
//            QMessageBox::information(this,tr("完成提示"),tr("完成失败"));
//            return;
//        }
//    }
//}
void GToDoitem::on_btnAlter_clicked()  //3个图标 问题是没显示?
{
    emit showSettingPanel(ui->lbTitle->text(),m_ddl);
}

void GToDoitem::on_lbIcon_clicked()
{

    emit showSettingPanel(ui->lbTitle->text(),m_ddl);
}
void GToDoitem::on_lbTitle_clicked()
{
    emit showSettingPanel(ui->lbTitle->text(),m_ddl);
}


void GToDoitem::on_pushButton_download_clicked()
{
    // 查询待办事项的详细信息，并构建富文本字符串
    QString currentTitle = ui->lbTitle->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM todolist WHERE Title = ?");
    query.bindValue(0, currentTitle);
    query.exec();

    QString content;
    if (query.next()) {
        QString Title = query.value("Title").toString();
        QString Deadline = query.value("Deadline").toString();
        QString Remind = query.value("Remind").toString();
        QString Finished = query.value("Finished").toString();
        QString FinishDate = query.value("FinishDate").toString();
        QString Todocontent = query.value("Todocontent").toString();
        QString Remarksdetail = query.value("Remarksdetail").toString();
        QString priority = query.value("priority").toString();
        QString repeat = query.value("repeat").toString();
        QString Crontab = query.value("Crontab").toString();
        QString GpName = query.value("GpName").toString();
        content = tr("[待办标题]：") + Title + "<br>"
                + tr("[所属组别]：") + GpName + "<br>"
                + tr("[截止日期]：") + Deadline + "<br>"
                + tr("[设置提醒]：") + Remind + "<br>"
                + tr("[完成标记]：") + Finished + "<br>"
                + tr("[完成时间]：") + FinishDate + "<br>"
                + tr("[完成属性]：") + priority + "<br>"
                + tr("[重复次数]：") + repeat + "<br>"
                + tr("[定时任务]：") + Crontab + "<br>"
                + tr("[待办内容]：") + "<br><br>" + Todocontent + "<br><br>"
                + tr("[待办备注]：") + "<br><br>" + Remarksdetail + "<br><br>";
    }

    // 将 HTML 标签转换为 RTF 格式
    QTextDocument textDocument;
    textDocument.setHtml(content);

    // 获取文件路径、扩展名和文件名
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), ui->lbTitle->text(), tr("文档类型 (*.doc);;富文本格式 (*.rtf);;文本类型 (*.txt)"));
    QFileInfo fileInfo(fileName);
    QString ext = fileInfo.suffix().toLower();
    QString baseName = fileInfo.baseName();

    if (!fileName.isEmpty()) {
        if (ext == "rtf") {
            // 将 HTML 转换后的 RTF 内容保存为 RTF 文件
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                stream.setCodec("GB2312");
                stream << textDocument.toPlainText();
                file.close();
            }
        } else if (ext == "doc") {
            // 将 HTML 转换后的纯文本内容保存为 DOCX 文件
            QAxObject word("Word.Application");
            word.setProperty("Visible", false);
            QAxObject *docs = word.querySubObject("Documents");
            QAxObject *doc = docs->querySubObject("Add()");
            QAxObject *selection = word.querySubObject("Selection");
            selection->dynamicCall("TypeText(QString)", textDocument.toPlainText());
            selection->dynamicCall("SelectAll()");
            selection->dynamicCall("ParagraphFormat.Alignment", 1); // 居中对齐
            doc->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
            doc->dynamicCall("Close()");
            word.dynamicCall("Quit()");
        } else if (ext == "txt") {
            // 将 HTML 转换后的纯文本内容保存为 TXT 文件
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                stream.setCodec("GB2312");
                stream << textDocument.toPlainText();
                file.close();
            }
        } else {
            // 文件扩展名不合法，输出错误提示信息
            QMessageBox::warning(this, tr("Warning"), tr("Invalid file extension."));
        }
    }
}

void GToDoitem::on_pushButton_del_clicked()
{
    QMessageBox mm(QMessageBox::Warning,QString(tr("警告")),QString(tr("你确定要删除吗？")),QMessageBox::Yes| QMessageBox::No);
    mm.setButtonText(QMessageBox::Yes,QString(tr("确认")));
    mm.button(QMessageBox::No)->setText(tr("取消"));
    int Ret = mm.exec();
    if(Ret == QMessageBox::Yes)
    {
        QDate date;
        date=date.currentDate();

        QSqlQuery query;
        if(query.exec(QString("delete from todolist where Title = '%1';").arg(ui->lbTitle->text()))){

            this->close();
        }
        else
        {
            QMessageBox::information(this,tr("删除提示"),tr("删除失败"));
        }
    }
}

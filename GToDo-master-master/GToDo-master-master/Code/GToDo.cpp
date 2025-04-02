#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QDesktopWidget>
#include <QScrollArea>
#include <QFuture>
#include <QHash>
#include <QLabel>
#include <QTextEdit>
#include <QColorDialog>
#include <QtCore/qmath.h>
#include "GToDo.h"
#include <QTextCharFormat>
#include "ui_GToDo.h"
#include <QFileDialog>
#include <QBuffer>
#include <QSettings>
#include <QByteArray>
#include <GBtnRroup.h>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QProcess>

#define SHADOW_WIDTH 10


GToDo::GToDo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GToDo)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);//放到window系统的任务栏
    setAttribute(Qt::WA_TranslucentBackground);
    ui->scrollArea->viewport()->setStyleSheet(".QWidget{background-color:transparent;}");

    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    this->setWindowTitle(tr(" GTOD待办专家"));
    db = QSqlDatabase::addDatabase("QSQLITE");//打开数据库
    db.setDatabaseName("D:\\code\\code_SE_Team_eight\\GToDo-master-master\\GToDo-master-master\\Exec for windows\\todo.db");

    bool isOpen = db.open();
    qDebug() << isOpen << endl;
        //Q_ASSERT(isOpen); // 如果数据库未成功打开，则触发断言

        if (!isOpen) {
            qCritical() << "Failed to open the database:" << db.lastError().text();
            exit(-1); // 返回错误码
        }

    loadGroup();
    ui->avatarLabel->hide();
    ui->panelList->setCurrentIndex(0);
    ui->lbGroup->setText(tr("全部待办"));
    update();
    ui->pushButton_login->setVisible(true);
    ui->pushButton_login_img->setVisible(false);
    ui->Selection_Audio_ok->setVisible(false);
    ui->Selection_Audio->setVisible(true);
    translator = new QTranslator(this);
    currentUsername = "";
    currentPassword = "";

    QSettings settings("Remember", "password");
    QString savedUsername = settings.value("username").toString();
    QString savedPassword = settings.value("password").toString();
    if(!savedUsername.isEmpty() && !savedPassword.isEmpty()) {
        ui->lineEdit_username->setText(savedUsername);
        ui->lineEdit_password->setText(savedPassword);
        ui->rememberCheckBox->setChecked(true);//默认记住密码

        QString selectSql = "SELECT * FROM user WHERE username=:username AND password=:password";
        QSqlQuery query;
        query.prepare(selectSql);
        query.bindValue(":username", savedUsername);
        query.bindValue(":password", savedPassword);
        if (!query.exec() || !query.next()) {
            qDebug() << "Login error";
            QMessageBox::information(this, "登录认证", "登录失败，账户或密码错误");
        } else {
            QString updateSql = "UPDATE user SET is_logged_in=1 WHERE id=:id";//登录成功
            query.prepare(updateSql);
            query.bindValue(":id", query.value("id"));
            if (!query.exec()) {
                qDebug() << "Update error: " << query.lastError().text();
                return;
            }

            ui->label_userName->setText(savedUsername);

            QPixmap userAvatar;//处理登录头像信息
            QString selectAvatarSql = "SELECT avatar FROM user WHERE username=:username";
            query.prepare(selectAvatarSql);
            query.bindValue(":username", savedUsername);
            if(!query.exec() || !query.next()) {
                qDebug() << "Get user avatar error: " << query.lastError().text();
            } else {
                QByteArray avatarData = query.value("avatar").toByteArray();
                userAvatar.loadFromData(avatarData);

                QSettings settings("MyApp", "MyApp");
                settings.setValue("loggedIn", true);

                ui->pushButton_login->setVisible(false);
                ui->pushButton_login_img->setVisible(true);

                QPixmap pixmap(userAvatar);
                QSize iconSize(ui->pushButton_login_img->size().width(),
                               ui->pushButton_login_img->size().height());
                QPixmap scaledPixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio);
                QPixmap roundedPixmap(iconSize);
                roundedPixmap.fill(Qt::transparent);
                QPainter painter(&roundedPixmap);
                QPainterPath path;
                path.addEllipse(0, 0, iconSize.width(), iconSize.height());
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, scaledPixmap);

                ui->pushButton_login_img->setIcon(QIcon(roundedPixmap));

                ui->panelList->setCurrentIndex(0);
                ui->lbGroup->setText(tr("全部待办"));
                update();
            }

            QSqlQuery query;
            QString selectUserDataSql = "SELECT avatar, gender FROM user WHERE username=:username";
            query.prepare(selectUserDataSql);
            query.bindValue(":username", savedUsername);
            if(!query.exec() || !query.next()) {
                qDebug() << "Get user data error: " << query.lastError().text();
            } else {
                QByteArray avatarData = query.value("avatar").toByteArray();
                QPixmap userAvatar;
                userAvatar.loadFromData(avatarData);

                QString gender = query.value("gender").toString();
                QString genderText = "性别：";
                if(gender == "男") {
                    ui->sexuality->setIcon(QIcon(":/image/male.png"));
                } else if(gender == "女") {
                    ui->sexuality->setIcon(QIcon(":/image/woman.png"));

                } else {
                    ui->sexuality->setIcon(QIcon(":/image/sex.png"));
                }

            }
        }
    }

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/image/logo.png"));
    trayIcon->setToolTip(tr("QTDO待办专家"));
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        trayIcon->show();
        QMenu *trayIconMenu = new QMenu(this);
        QAction *emailAction = new QAction(tr("退出"), this);
        trayIconMenu->addAction(emailAction);
        connect(emailAction, &QAction::triggered, this, [=](){
            on_pushButton_exit_clicked();
        });
        trayIcon->setContextMenu(trayIconMenu);
    }
    connect(trayIcon, &QSystemTrayIcon::activated, this, &GToDo::iconActivated);


    for(int i=5;i<50;i++)
    {
        ui->comboBox->addItem(tr("%1").arg(i));
    }

    connect(ui->pushButton_editcopy,SIGNAL(clicked()),ui->editMsg,SLOT(copy()));
    connect(ui->pushButton_editcut,SIGNAL(clicked()),ui->editMsg,SLOT(cut()));
    connect(ui->pushButton_editundo,SIGNAL(clicked()),ui->editMsg,SLOT(undo()));
    connect(ui->pushButton_editredo,SIGNAL(clicked()),ui->editMsg,SLOT(redo()));
    connect(ui->pushButton_paste,SIGNAL(clicked()),ui->editMsg,SLOT(paste()));
    connect(ui->fontComboBox, SIGNAL(currentIndexChanged(QString)),ui->editMsg,
            SLOT(setFontFamily(QString)));


}

void GToDo::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        show();
        trayIcon->hide();
    }
}

GToDo::~GToDo()
{
    delete ui;
    delete trayIcon;

}

void GToDo::update()//刷新键
{
    widget = new QWidget(this);
    todoLayout = new QVBoxLayout(widget);
    QSqlQuery query;
    if(ui->boxOrder->currentIndex() == 0 )
    {
        if(ui->lbGroup->text() == tr("全部待办"))
        {
            query.exec("select * from todolist where Finished = 0 order by Deadline,Priority desc;");
        }
        else
        {
            query.exec(QString("select * from todolist where Finished = 0 and gpName = '%1' order by Deadline,Priority desc;").arg(ui->lbGroup->text()));
        }
    }
    else
    {
        if(ui->lbGroup->text() == tr("全部待办"))
        {
            query.exec("select * from todolist where Finished = 0 order by Priority desc,Deadline;");
        }
        else
        {
            query.exec(QString("select * from todolist where Finished = 0 and gpName = '%1' order by Priority desc,Deadline;").arg(ui->lbGroup->text()));
        }
    }
    while(query.next())
    {
        GToDoitem * newItem = new GToDoitem();
        newItem->setTitle(query.value("Title").toString(),query.value("Priority").toInt());
        todoLayout->addWidget(newItem);
        newItem->setRepeat(query.value("Repeat").toInt());
        newItem->setCrontab(query.value("Crontab").toInt());
        QString Remind =query.value("Remind").toString();
        if(!Remind.isEmpty())
        {
            newItem->setRemind(Remind);
        }
        QString Deadline =query.value("Deadline").toString();
        if(!Deadline.isEmpty())
        {
            newItem->setDDL(Deadline);
        }
        connect(newItem,&GToDoitem::showSettingPanel,this,&GToDo::openSettingPanel);
    }
    GQStringToQDate::btnShowFinished = new QPushButton(widget);
    QPixmap empty(":/image/empty.png");
    QLabel* lbEmpty = new QLabel(widget);
    lbEmpty->setContentsMargins(80, 80, 80, 0);
    QHBoxLayout* layoutempty= new QHBoxLayout;
    QLabel* lblText = new QLabel(widget);
    lblText->setStyleSheet("font-size:24px;color:#cccccc;margin-bottom:50px;");
    if(todoLayout->count() == 0)
    {
        lbEmpty->setPixmap(empty);
        layoutempty->addStretch();
        layoutempty->addWidget(lbEmpty);
        layoutempty->addStretch();
        todoLayout->addLayout(layoutempty);
        lblText->setText(tr("没有待办事项"));
        lblText->setAlignment(Qt::AlignCenter);
        todoLayout->addWidget(lblText);

    }

    GQStringToQDate::btnShowFinished->setText(tr("显示已完成的任务"));
    GQStringToQDate::btnShowFinished->setCursor(Qt::PointingHandCursor);
    GQStringToQDate::btnShowFinished->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.3);}QPushButton:hover {background-color:rgba(0,0,0,0.1);}");
    QHBoxLayout* layoutShowFinished = new QHBoxLayout;
    layoutShowFinished->addStretch();
    layoutShowFinished->addWidget(GQStringToQDate::btnShowFinished);
    layoutShowFinished->addStretch();
    todoLayout->addLayout(layoutShowFinished);
    todoLayout->addStretch();
    ui->scrollArea->setWidget(widget);
    connect(GQStringToQDate::btnShowFinished, &QPushButton::clicked, this, &GToDo::on_btnShowFinished_clicked);
}

void GToDo::on_btnShowFinished_clicked()//点击显式已完成任务
{
    if(GQStringToQDate::btnShowFinished->text() == "显示已完成的任务")
    {
        QSqlQuery query;
        if(ui->lbGroup->text() == "全部待办")
        {
            query.exec("select * from todolist where Finished = 1 order by FinishDate desc;");
        }
        else
        {
            query.exec(QString("select * from todolist where Finished = 1 and gpName = '%1' order by FinishDate desc;").arg(ui->lbGroup->text()));
        }
        while(query.next())//构建KToDoitem加到layout中
        {
            GToDoitem * newItem = new GToDoitem();
            newItem->setTitle(query.value("Title").toString(),-1);
            todoLayout->addWidget(newItem);
            newItem->setRepeat(query.value("Repeat").toInt());
            QString remind =query.value("Remind").toString();
            if(!remind.isEmpty())
            {
                newItem->setRemind(remind);
            }
            QString Deadline =query.value("Deadline").toString();
            if(!Deadline.isEmpty())
            {
                newItem->setDDL(Deadline);
            }
            newItem->setFinishDate(query.value("FinishDate").toString());
            newItem->hideBtn();
            connect(newItem,&GToDoitem::showSettingPanel,this,&GToDo::openSettingPanel);
        }
        todoLayout->addStretch();
        GQStringToQDate::btnShowFinished->setText("隐藏已完成的任务");
    }
    else
    {
        update();//处于展示状态，调用update去再次隐藏起来
    }
}

void GToDo::loadGroup()//加载分类组
{
    QSqlQuery query(db);
    if(query.exec(QString("select * from groupName;")))
    {
        while (query.next()) {
            GBtnGroup * newGroup = new GBtnGroup(this);
            ui->layoutGroup->addWidget(newGroup);
            newGroup->setText(query.value("groupName").toString());
            connect(newGroup,&GBtnGroup::groupSwitch,this,&GToDo::groupSwitch);
        }

    }
    else
    {
        qCritical() << query.lastError().text();
        QMessageBox::information(this,tr("加载提示"),tr("加载分组失败"));
    }
}

void GToDo::on_btnRefresh_clicked()//点击刷新键
{
    update();
}

void GToDo::openSettingPanel(QString Title, QString Deadline)//从数据库里面导入数据或者编辑任务
{
    if(!(ui->panelList->currentIndex()==1))
    {
        ui->panelList->setCurrentIndex(1);
    }
    ui->editDdl->hide();
    ui->editRemind->hide();
    GQStringToQDate::s_currentTitle = Title;
    GQStringToQDate::s_currentDdl = Deadline;
    QSqlQuery query;
    if(Deadline.isEmpty()) // 未设置截止时间
    {
        if(!query.exec(QString("select * from todolist where Title = '%1' and Deadline is null;").arg(Title)))
        {
            QMessageBox::information(this,tr("查询提示"),tr("查询失败"));
        }
    }
    else // 已设置截止时间
    {
        if(query.exec(QString("select * from todolist where Title = '%1' and Deadline = '%2';").arg(Title).arg(Deadline)))
        {
        }
        else
        {
            QMessageBox::information(this,tr("查询提示"),tr("查询失败"));
        }
    }

    if(query.next())
    {
        ui->editTitle->setText(Title);

        ui->boxPriority->setCurrentIndex(query.value("Priority").toInt());

        ui->boxRepeat->setCurrentIndex(query.value("Repeat").toInt());

        QString Deadline = query.value("Deadline").toString();
        if(!Deadline.isEmpty()) // 已设置截止时间
        {
            ui->btnSetDdl->setText(GQStringToQDate::QStringFromat(Deadline));
        }
        else
        {
            ui->btnSetDdl->setText(tr("设置截止时间"));
        }

        QString Remind = query.value("Remind").toString();
        if(!Remind.isEmpty())
        {
            ui->btnSetRemind->setText(QDateTime::fromString(Remind,"yyyy-MM-dd hh:mm").toString("MM-dd hh:mm"));
        }
        else
        {
            ui->btnSetRemind->setText(tr("设置提醒时间"));
        }

        QString Todocontent = query.value("Todocontent").toString();
        if(!Todocontent.isEmpty())
        {
            ui->editMsg->setText(Todocontent);
        }
        else
        {
            ui->editMsg->setText(tr(""));
        }

        QString Remarksdetail = query.value("Remarksdetail").toString();
        if(!Remarksdetail.isEmpty())
        {
            ui->editDetail->setText(Remarksdetail);
        }
        else
        {
            ui->editDetail->setText(tr(""));
        }
    }
}

void GToDo::groupSwitch(QString group)
{
    ui->lbGroup->setText(group);
    update();
    ui->panelList->setCurrentIndex(0);
}

void GToDo::on_editTitle_editingFinished()
{
    if(!ui->editTitle->hasFocus()) return;
    QSqlQuery query;
    if(GQStringToQDate::s_currentDdl.isEmpty())
    {
        if(query.exec(QString("update todolist set Title = '%1' where Title = '%2' and Deadline is null;").arg(ui->editTitle->toPlainText()).arg(GQStringToQDate::s_currentTitle)))
        {
            update();
            GQStringToQDate::s_currentTitle = ui->editTitle->toPlainText();
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败,已有同名且截止时间相同的事件"));
        }
    }
    else
    {
        if(query.exec(QString("update todolist set Title = '%1' where Title = '%2' and Deadline = '%3';").arg(ui->editTitle->toPlainText()).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
        {
            update();
            GQStringToQDate::s_currentTitle = ui->editTitle->toPlainText();
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败,已有同名且截止时间相同的事件"));
        }
    }
}

void GToDo::on_btnDetail_clicked() //修改细节
{
    QSqlQuery query;
    QString oldTitle = GQStringToQDate::s_currentTitle;
    QString newTitle = ui->editTitle->toPlainText();
    QString deadline = GQStringToQDate::s_currentDdl;
    QByteArray contentData = ui->editMsg->toHtml().toUtf8();   // 将富文本数据转换为二进制格式
    QByteArray detailData = ui->editDetail->toHtml().toUtf8();   // 将富文本数据转换为二进制格式

    if (deadline.isEmpty()) {
        // 定义待执行的 SQL 语句
        QString sql = "update todolist set Todocontent = :content, Title = :title, Remarksdetail = :detail where Title = :oldTitle and Deadline is null;";

        query.prepare(sql);
        query.bindValue(":content", contentData);
        query.bindValue(":title", newTitle);
        query.bindValue(":detail", detailData);
        query.bindValue(":oldTitle", oldTitle);
    } else {

        QString sql = "update todolist set Todocontent = :content, Title = :title, Remarksdetail = :detail where Title = :oldTitle and Deadline = :deadline;";

        query.prepare(sql);
        query.bindValue(":content", contentData);
        query.bindValue(":title", newTitle);
        query.bindValue(":detail", detailData);
        query.bindValue(":oldTitle", oldTitle);
        query.bindValue(":deadline", deadline);
    }

    if (query.exec()) {
        GQStringToQDate::s_currentTitle = newTitle;
        ui->panelList->setCurrentIndex(0);
        update();
    } else {
        QMessageBox::information(this, tr("修改提示"), tr("修改失败"));
    }
}


void GToDo::on_boxPriority_currentIndexChanged(int index)//修改优先级
{
    QSqlQuery query;
    if(GQStringToQDate::s_currentDdl.isEmpty())
    {
        if(query.exec(QString("update todolist set Priority = %1 where Title = '%2' and Deadline is null;").arg(index).arg(GQStringToQDate::s_currentTitle)))
        {
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }
    else
    {
        if(query.exec(QString("update todolist set Priority = %1 where Title = '%2' and Deadline = '%3';").arg(index).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
        {
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }

    update();
}


void GToDo::on_boxRepeat_currentIndexChanged(int index)//修改重复次数
{
    QSqlQuery query;
    if(GQStringToQDate::s_currentDdl.isEmpty())
    {
        if(query.exec(QString("update todolist set Repeat = %1 where Title = '%2' and Deadline is null ;").arg(index).arg(GQStringToQDate::s_currentTitle)))
        {
            //QMessageBox::information(this,tr("修改提示"),tr("修改成功"));
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }
    else
    {
        if(query.exec(QString("update todolist set Repeat = %1 where Title = '%2' and Deadline = '%3';").arg(index).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
        {
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }

    update();
}

void GToDo::on_Crontab_currentIndexChanged(int index){//修改任务类型
    QSqlQuery query;
    if(GQStringToQDate::s_currentDdl.isEmpty())
    {
        if(query.exec(QString("update todolist set Crontab = %1 where Title = '%2' and Deadline is null ;").arg(index).arg(GQStringToQDate::s_currentTitle)))
        {
            //QMessageBox::information(this,tr("修改提示"),tr("修改成功"));
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }
    else
    {
        if(query.exec(QString("update todolist set Crontab = %1 where Title = '%2' and Deadline = '%3';").arg(index).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
        {
        }
        else
        {
            QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
        }
    }

    update();
}

void GToDo::on_btnSetDdl_clicked()//确定截止日期
{
    QSqlQuery query;
    if(ui->btnSetDdl->text() != tr("确定"))
    {
        if(GQStringToQDate::s_currentDdl.isEmpty())
        {
            query.exec(QString("select * from todolist where Title = '%1' and Deadline is null;").arg(GQStringToQDate::s_currentTitle));
        }
        else
        {
            query.exec(QString("select * from todolist where Title = '%1' and Deadline = '%2';").arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl));
        }

        if(query.next())
        {
            QString originalDdl = query.value("Deadline").toString();
            if(!originalDdl.isEmpty())
            {
                ui->editDdl->setDate(QDate::fromString(originalDdl,"yyyy-MM-dd"));
            }
            else
            {
                ui->editDdl->setDate(QDate::currentDate());
            }
        }
        ui->editDdl->show();
        ui->btnSetDdl->setText(tr("确定"));
    }
    else
    {
        if(GQStringToQDate::s_currentDdl.isEmpty())
        {
            if(query.exec(QString("update todolist set Deadline = '%1' where Title = '%2'  and Deadline is null;").arg(ui->editDdl->date().toString("yyyy-MM-dd")).arg(GQStringToQDate::s_currentTitle)))
            {
                GQStringToQDate::s_currentDdl = ui->editDdl->date().toString("yyyy-MM-dd");
                update();
                ui->btnSetDdl->setText(GQStringToQDate::QStringFromat(ui->editDdl->date().toString("yyyy-MM-dd")));
                ui->editDdl->hide();
            }
            else
            {
                QMessageBox::information(this,tr("修改提示"),tr("修改失败,已有同名且截止时间相同的事件"));
            }
        }
        else
        {
            if(query.exec(QString("update todolist set Deadline = '%1' where Title = '%2'  and Deadline = '%3';").arg(ui->editDdl->date().toString("yyyy-MM-dd")).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
            {
                GQStringToQDate::s_currentDdl = ui->editDdl->date().toString("yyyy-MM-dd");
                update();
                ui->btnSetDdl->setText(GQStringToQDate::QStringFromat(ui->editDdl->date().toString("yyyy-MM-dd")));
                ui->editDdl->hide();
            }
            else
            {
                QMessageBox::information(this,tr("修改提示"),tr("修改失败,已有同名且截止时间相同的事件"));
            }
        }

    }
}

void GToDo::on_btnSetRemind_clicked()//确定截止时间
{
    QSqlQuery query;
    if(ui->btnSetRemind->text() != tr("确定"))
    {
        if(GQStringToQDate::s_currentDdl.isEmpty())
        {
            query.exec(QString("select * from todolist where Title = '%1' and Deadline is null ;").arg(GQStringToQDate::s_currentTitle));
        }
        else
        {
            query.exec(QString("select * from todolist where Title = '%1' and Deadline = '%2' ;").arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl));
        }

        if(query.next())
        {
            QString originalRemind = query.value("Remind").toString();
            if(!originalRemind.isEmpty())
            {
                ui->editRemind->setDateTime(QDateTime::fromString(originalRemind,"yyyy-MM-dd hh:mm"));
            }
            else
            {
                ui->editRemind->setDate(QDate::currentDate());
            }
        }
        ui->editRemind->show();
        ui->btnSetRemind->setText(tr("确定"));
    }
    else
    {
        if(GQStringToQDate::s_currentDdl.isEmpty())
        {
            if(query.exec(QString("update todolist set Remind = '%1' where Title = '%2' and Deadline is null;").arg(ui->editRemind->dateTime().toString("yyyy-MM-dd hh:mm")).arg(GQStringToQDate::s_currentTitle)))
            {
                update();
                ui->btnSetRemind->setText(ui->editRemind->dateTime().toString("MM-dd hh:mm"));
                ui->editRemind->hide();
            }
            else
            {
                QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
            }
        }
        else
        {
            if(query.exec(QString("update todolist set Remind = '%1' where Title = '%2' and Deadline = '%3';").arg(ui->editRemind->dateTime().toString("yyyy-MM-dd hh:mm")).arg(GQStringToQDate::s_currentTitle).arg(GQStringToQDate::s_currentDdl)))
            {
                update();
                ui->btnSetRemind->setText(ui->editRemind->dateTime().toString("MM-dd- hh:mm"));
                ui->editRemind->hide();
            }
            else
            {
                QMessageBox::information(this,tr("修改提示"),tr("修改失败"));
            }
        }

    }
}


void GToDo::on_btnMyTask_clicked()//点击全部按钮
{
    ui->lbGroup->setText(tr("全部待办"));
    update();
    ui->panelList->setCurrentIndex(0);
}

void GToDo::on_editAddGroup_editingFinished()//添加分类组
{
    if(!ui->editAddGroup->hasFocus()) return;
    if(ui->editAddGroup->text() == "全部待办")
    {
        QMessageBox::information(this,tr("添加提示"),tr("添加失败,非法名字"));
        return;
    }
    QSqlQuery query;
    if(query.exec(QString("insert into groupName values ('%1');").arg(ui->editAddGroup->text())))
    {

        GBtnGroup * newGroup = new GBtnGroup(this);
        ui->layoutGroup->addWidget(newGroup);
        newGroup->setText(ui->editAddGroup->text());
        connect(newGroup,&GBtnGroup::groupSwitch,this,&GToDo::groupSwitch);
    }
    else
    {
        QMessageBox::information(this,tr("添加提示"),tr("添加失败"));
    }
    ui->editAddGroup->setText("");
}

void GToDo::on_editAddItem_editingFinished()//添加新事项
{
    if(!ui->editAddItem->hasFocus()) return;
    QString tilte = ui->editAddItem->text();
    if(tilte.length() < 1) return;
    QSqlQuery query(db);
    query.exec(QString("select * from todolist where Title = '%1' and Deadline is null;").arg(tilte));
    if(!query.next())
    {
        QString sql = QString("insert into todolist (Title,Finished,Priority,gpName) values ('%1',0,0,'%2');").arg(tilte).arg(ui->lbGroup->text());

        if(query.exec(sql))
        {

        }
        else
        {
            QMessageBox::information(this,tr("新建提示"),tr("新建失败，已有同名且截至日期相同的事件"));
        }
    }
    else
    {
        QMessageBox::information(this,tr("新建提示"),tr("新建失败，已有同名且截至日期相同的事件"));
    }
    ui->editAddItem->clear();
    update();
}


void GToDo::on_boxOrder_currentIndexChanged(int)//按时间排序还是按优先级排序？？？？
{
    update();
}


void GToDo::on_pushButton_background_color_clicked()//事项编辑页面的颜色细微调整区
{
    QColor Backg=QColorDialog::getColor(Qt::white);
    if(Backg.isValid())
    {

        ui->editMsg->setTextBackgroundColor(Backg);

        QString buttoncolor=tr("color:%1").arg(Backg.name());
        ui->pushButton_background_color->setStyleSheet(buttoncolor);
    }
}


void GToDo::on_pushButton_color_clicked()
{
    QColor clr = QColorDialog::getColor(Qt::black);
    if(clr.isValid())
    {
        ui->editMsg->setTextColor(clr);
        QString buttons_color = tr("color: %1").arg(clr.name());
        ui->pushButton_color->setStyleSheet(buttons_color);
    }
}

void GToDo::on_pushButton_textbold_clicked()
{
    if(ui->editMsg->fontWeight()==QFont::Bold)
    {
        ui->editMsg->setFontWeight(QFont::Normal); //设置字体为不加粗
    }
    else
    {
        ui->editMsg->setFontWeight(QFont::Bold); //设置字体加粗
    }
}

void GToDo::on_pushButton_textitalic_clicked()
{
    if(ui->editMsg->fontItalic())
    {
        ui->editMsg->setFontItalic(false);
    }
    else
    {
        ui->editMsg->setFontItalic(true); //设置斜体
    }
}

void GToDo::on_pushButton_textunder_clicked()
{
    if(ui->editMsg->fontUnderline())
    {
        ui->editMsg->setFontUnderline(false);
    }
    else
    {
        ui->editMsg->setFontUnderline(true); //设置字体加下划线
    }
}

void GToDo::on_pushButton_textright_clicked()
{
    ui->editMsg->setAlignment(Qt::AlignRight);
}

void GToDo::on_pushButton_textleft_clicked()
{
    ui->editMsg->setAlignment(Qt::AlignLeft);
}


void GToDo::on_pushButton_textjustify_clicked()
{
    ui->editMsg->setAlignment(Qt::AlignJustify);
}

void GToDo::on_pushButton_textcenter_clicked()
{
    ui->editMsg->setAlignment(Qt::AlignHCenter);
}

void GToDo::on_comboBox_activated(int)
{

}

void GToDo::on_comboBox_activated(const QString &arg1)
{
    ui->editMsg->setFontPointSize(arg1.toInt());
}

void GToDo::on_update_img_clicked()//更新头像图片
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("选择要上传的图片"), QDir::homePath(), tr("Images (*.png *.jpg *.bmp)"));
    if (!imagePath.isEmpty()) {
        QString html = "<img src=\"" + imagePath + "\">";
        ui->editMsg->textCursor().insertHtml(html);

    }
}

void GToDo::on_Clear_btn_clicked()//去除粗体、斜体等
{
    QTextCursor cursor = ui->editMsg->textCursor();

    if (cursor.hasSelection()) {
        QTextCharFormat format;
        QString selectedText = cursor.selectedText();

        int position = cursor.position();
        cursor.removeSelectedText();
        cursor.setPosition(position);
        cursor.insertText(selectedText, format);
    }
}

void GToDo::mousePressEvent(QMouseEvent *event)//左键拖动
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        mouseStartPoint = event->globalPos();
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void GToDo::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        QPoint distance = event->globalPos() - mouseStartPoint;
        this->move(windowTopLeftPoint + distance);
    }
}

void GToDo::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}


void GToDo::paintEvent(QPaintEvent *event) //绘制界面
{

    Q_UNUSED(event);
    QPainter painter(this);
    QPoint topLeft(10, 10);
    QSize size(width() - 20, height() - 20);
    QRectF rect(topLeft, size);

    QPainterPath path;
    path.addRoundedRect(rect, 10, 10); // 添加带圆角的矩形

    painter.setClipPath(path);

    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor color(0, 0, 0, 220);
    for (int i = 10; i > 0; i--)
    {
        QColor color(0, 0, 0, 30 - i * 3);
        painter.setPen(color);
        painter.setClipping(false);
        painter.drawRoundedRect(rect.adjusted(-i, -i, i, i), 10, 10);
        painter.setClipPath(path);
    }

    painter.fillRect(rect, Qt::white);

}

void GToDo::on_pushButton_exit_clicked()//退出键
{
    if (!(QMessageBox::information(this,tr("程序提醒"),tr("你是否确定要退出程序？"),tr("是的"),tr("不是"))))
    {
        QApplication* app = nullptr;
        app->exit(0);
    }
}

void GToDo::on_pushButton_login_clicked()
{
    ui->panelList->setCurrentIndex(2);
}

void GToDo::on_pushButton_min_clicked()//最小化
{
    hide();
    trayIcon->show();//放在了windows系统托盘区域
}

void GToDo::on_pushButton_menu_clicked()//附加功能区
{
    QMenu *menu = new QMenu(this);

    QAction *action1 = new QAction(QIcon(":/image/set.png"), tr("系统配置"), this);
    menu->addAction(action1);
    connect(action1, &QAction::triggered, this, [=](){
        ui->panelList->setCurrentIndex(4);
        ui->lbGroup->setText(tr("系统配置"));
    });


    QPoint pos = ui->pushButton_menu->mapToGlobal(QPoint(0, ui->pushButton_menu->height()));
    QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    if (pos.x() + menu->width() > screenGeometry.width()) {
        pos.setX(screenGeometry.width() - menu->width());
    }
    if (pos.y() + menu->height() > screenGeometry.height()) {
        pos.setY(pos.y() - menu->height() - ui->pushButton_menu->height());
    }

    menu->exec(pos);

}

void GToDo::on_pushButton_login_img_clicked()//点击头像，跳转个人中心
{
    ui->panelList->setCurrentIndex(3);
    ui->lbGroup->setText(tr("个人中心"));
    //  ui->tabWidget_usercenter->setCurrentIndex(0);
}

void GToDo::on_btn_signin_clicked()//点击登录按钮、校验登录、加载头像
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QString sql = QString("SELECT * FROM user WHERE username='%1' AND password='%2'")
            .arg(username).arg(password);

    QSqlQuery query(sql);

    if (!query.next()) {
        qDebug() << "Login error";
        QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");
    }
    else//登录成功
    {
        query.prepare("UPDATE user SET is_logged_in=:is_logged_in WHERE username=:username");
        query.bindValue(":is_logged_in", true);
        query.bindValue(":username", currentUsername);

        if (!query.exec()) {
            qWarning() << "Failed to update user logged in status:" << query.lastError().text();
            return;
        } else {
            qDebug() << "User logged in successfully:" << query.boundValues();
        }
        currentUsername = username;
        currentPassword = password;

        QSqlQuery query;
        query.prepare("SELECT avatar FROM user WHERE username=:username AND password=:password");
        query.bindValue(":username", currentUsername);
        query.bindValue(":password", currentPassword);
        query.exec();

        if (query.next()) {
            QByteArray avatarData = query.value("avatar").toByteArray();
            QImage avatarImage;
            if (!avatarData.isEmpty()) {
                avatarImage.loadFromData(avatarData);
            } else {
                avatarImage.load(":/image/course.png");
            }
            QPixmap avatar = QPixmap::fromImage(avatarImage);
            ui->label_userName->setText(username);
            ui->pushButton_login->setVisible(false);
            ui->pushButton_login_img->setVisible(true);

            QPixmap pixmap(avatar);
            QSize iconSize(ui->pushButton_login_img->size().width(),
                           ui->pushButton_login_img->size().height());
            QPixmap scaledPixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio);
            QPixmap roundedPixmap(iconSize);
            roundedPixmap.fill(Qt::transparent);
            QPainter painter(&roundedPixmap);
            QPainterPath path;
            path.addEllipse(0, 0, iconSize.width(), iconSize.height());
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, scaledPixmap);

            ui->pushButton_login_img->setIcon(QIcon(roundedPixmap));

            QSqlQuery query;
            QString selectUserDataSql = "SELECT avatar, gender FROM user WHERE username=:username";
            query.prepare(selectUserDataSql);
            query.bindValue(":username", username);
            if(!query.exec() || !query.next()) {
                qDebug() << "Get user data error: " << query.lastError().text();
            } else {
                QByteArray avatarData = query.value("avatar").toByteArray();
                QPixmap userAvatar;
                userAvatar.loadFromData(avatarData);

                QString gender = query.value("gender").toString();
                QString genderText = "性别：";
                if(gender == "男") {
                    ui->sexuality->setIcon(QIcon(":/image/male.png"));
                } else if(gender == "女") {
                    ui->sexuality->setIcon(QIcon(":/image/woman.png"));

                } else {
                    ui->sexuality->setIcon(QIcon(":/image/sex.png"));
                }

            }
        }

        QSettings settings("Remember", "password");
        if(ui->rememberCheckBox->isChecked()) {
            settings.setValue("username", username);
            settings.setValue("password", password);

        } else {
            settings.remove("username");
            settings.remove("password");

        }

        ui->panelList->setCurrentIndex(0);
        ui->lbGroup->setText(tr("全部待办"));
        update();


    }
}


void GToDo::on_pushButton_reg_clicked()//点击注册
{
    QString username = ui->lineEdit_username_reg->text();
    QString password = ui->lineEdit_passwd_reg->text();
    QString surepass = ui->lineEdit_surepasswd_reg->text();
    if(password == surepass)
    {
        QString sql=QString("insert into user(username,password) values('%1','%2');")
                .arg(username).arg(password);

        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug()<<"insert into error";
            QMessageBox::information(this,"注册认证","插入失败！");
        }
        else
        {
            qDebug()<<"insert into success";
            QMessageBox::information(this,"注册认证","插入成功！");

        }

    }else{
        QMessageBox::information(this,"注册认证","两次密码输入不一致");
    }
}


void GToDo::on_pushButton_longinbtn_clicked()//跳转登录
{
    ui->stackedWidget_login->setCurrentIndex(1);
}

void GToDo::on_pushButton_regbtn_clicked()//跳转注册
{
    ui->stackedWidget_login->setCurrentIndex(0);
}

void GToDo::on_selectButton_clicked()//选择头像
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), ".", tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty())
        ui->selectButton->setIcon(QPixmap(fileName));
    ui->avatarLabel->setPixmap(fileName);
    ui->selectButton->setText("");
}


void GToDo::on_saveButton_clicked()//保存资料
{
    QPixmap avatarPixmap = ui->avatarLabel->pixmap()->scaled(256, 256, Qt::KeepAspectRatio);
    QByteArray avatarData;
    QBuffer* buffer = new QBuffer(&avatarData);
    buffer->open(QIODevice::WriteOnly);
    avatarPixmap.save(buffer, "PNG");
    QString gender = tr(ui->radioButton_male->isChecked() ? "男" : (ui->radioButton_female->isChecked() ? "女" : "未知"));

    QString ModUserName = ui->lineEdit_UserName->text();
    QString wechatId = ui->lineEdit_wechatId->text();
    QDate birthday = ui->dateEdit_birthday->date();
    QString email = ui->lineEdit_email->text();
    QString profile = ui->TextEdit_profile->toPlainText();

    QSqlQuery query;
    query.prepare("UPDATE user SET username=:username, avatar=:avatar, gender=:gender, birthday=:birthday, wechat_id=:wechat_id, email=:email, profile=:profile WHERE username=:old_username AND password=:password");
    query.bindValue(":username", ModUserName);
    query.bindValue(":avatar", avatarData);
    query.bindValue(":gender", gender);
    query.bindValue(":birthday", birthday.toString(Qt::ISODate));
    query.bindValue(":wechat_id", wechatId);
    query.bindValue(":email", email);
    query.bindValue(":profile", profile);
    query.bindValue(":old_username", currentUsername);
    query.bindValue(":password", currentPassword);
    if (!query.exec()) {
        qWarning() << "Failed to update user profile:" << query.lastError().text();
        delete buffer;
        return;
    }

    QMessageBox::information(this,tr("设置成功"),tr("设置头像成功"));

    query.prepare("SELECT avatar FROM user WHERE username=:username AND password=:password");
    query.bindValue(":username", currentUsername);
    query.bindValue(":password", currentPassword);
    if (!query.exec() || !query.next()) {
        qWarning() << "Failed to retrieve updated user profile:" << query.lastError().text();
        delete buffer;
        return;
    }
    QByteArray avatarData2 = query.value(0).toByteArray();
    QPixmap avatarPixmap2;
    if (avatarData2.isEmpty()) {
        avatarPixmap2 = QPixmap(":/image/course.png");
    } else {
        avatarPixmap2.loadFromData(avatarData2);
    }
    ui->pushButton_login_img->setIcon(avatarPixmap2);
    ui->label_userName->setText(ModUserName);

    delete buffer;
}

void GToDo::on_QPushButton_out_clicked()//退出登录
{
    QString username = ui->label_userName->text();
    QString sql = QString("SELECT is_logged_in FROM user WHERE username='%1'").arg(username);
    QSqlQuery query(sql);
    if (query.next()) {
        QSqlQuery update_query(db);
        update_query.prepare("UPDATE user SET is_logged_in=:is_logged_in WHERE username=:username");
        update_query.bindValue(":is_logged_in", false);
        update_query.bindValue(":username", username);
        if (!update_query.exec()) {
            qWarning() << "Failed to update user logged in status:" << update_query.lastError().text();
            return;
        }

        ui->label_userName->setText(tr("嗨，请登录！"));
        ui->pushButton_login->setVisible(true);
        ui->pushButton_login_img->setVisible(false);

        QSettings settings("Remember", "password");

        settings.remove("username");
        settings.remove("password");
        ui->panelList->setCurrentIndex(0);
        ui->lbGroup->setText(tr("全部待办"));
        ui->sexuality->setIcon(QIcon(":/image/sex.png"));
        update();
    }
}


void GToDo::on_Selection_Audio_clicked()//选择提醒音效
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择音频文件"), QDir::homePath(), tr("音频文件 (*.mp3 *.wav *.ogg)"));

        if (!filePath.isEmpty()) {
            ui->Selection_lineEdit->setText(filePath);
            ui->Selection_Audio_ok->setVisible(true);
            ui->Selection_Audio->setVisible(false);
            ui->Selection_Audio->setText("重新选择");
        }
}

void GToDo::on_Selection_Audio_ok_clicked()
{
     QMessageBox::warning(this,tr("保存失败"),tr("好像出问题了，似乎没有保存成功！"));
     ui->Selection_Audio_ok->setVisible(false);
     ui->Selection_Audio->setVisible(true);
}

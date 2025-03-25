#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test();
    // 设置密码输入框不显示明文
    ui->loginPassword->setEchoMode(QLineEdit::Password);
    ui->registerPassword->setEchoMode(QLineEdit::Password);
    ui->confirmPassword->setEchoMode(QLineEdit::Password);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 登录按钮
void MainWindow::on_loginButton_clicked()
{
    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();

    if (username == "admin" && password == "123456") {
        QMessageBox::information(this, "登录成功", "欢迎使用本系统！");
        // 这里可以切换到主页面
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}

// 注册按钮
void MainWindow::on_registerButton_clicked()
{
    QString username = ui->registerUsername->text();
    QString password = ui->registerPassword->text();
    QString confirm = ui->confirmPassword->text();

    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "请填写完整信息");
        return;
    }

    if (password != confirm) {
        QMessageBox::warning(this, "注册失败", "两次输入的密码不一致");
        return;
    }

    QMessageBox::information(this, "注册成功", "注册成功，请返回登录");
    ui->stackedWidget->setCurrentIndex(0); // 返回登录界面
}

// 切换到注册界面
void MainWindow::on_switchToRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// 切换回登录界面
void MainWindow::on_switchToLogin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::test()
{
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); // 推荐使用 MySQL 驱动
    db.setHostName("49.235.140.182");
    db.setPort(3306);
    db.setDatabaseName("myproject");
    db.setUserName("root");
    db.setPassword("Chenliang2005");

    if (!db.open()) {
        QMessageBox::information(this, "infor", "link failed");
        qDebug() << "error open database because" << db.lastError().text();
        return;
    }

    QMessageBox::information(this, "infor", "link success");
    // qDebug() << "数据库连接成功！";

    QSqlQuery query(db);

    // 插入数据
    QString insertSql = "INSERT INTO user (id, name,telephone,password ) VALUES (1002, 'Alice','0593021931','123456')";
    if (!query.exec(insertSql)) {
        qDebug() << "插入失败：" << query.lastError().text();
    } else {
        qDebug() << "插入成功";
    }

    // 查询数据
    QString selectSql = "SELECT id, name FROM user";
    if (!query.exec(selectSql)) {
        qDebug() << "查询失败：" << query.lastError().text();
    } else {
        qDebug() << "查询结果：";
        while (query.next()) {
            int id = query.value("id").toInt();
            QString name = query.value("name").toString();
            qDebug() << "ID:" << id << ", Name:" << name;
        }
    }

    // 更新数据
    QString updateSql = "UPDATE user SET name = 'Bob' WHERE id = 1002";
    if (!query.exec(updateSql)) {
        qDebug() << "更新失败：" << query.lastError().text();
    } else {
        qDebug() << "更新成功";
    }

    // 删除数据
    //  QString deleteSql = "DELETE FROM user WHERE id = 1002";
    //   if (!query.exec(deleteSql)) {
    //      qDebug() << "删除失败：" << query.lastError().text();
    //   } else {
    //      qDebug() << "删除成功";
    //  }

    db.close();
}

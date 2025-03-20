#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    QSqlDatabase db;
    if (QSqlDatabase::contains("str1")) {
        db = QSqlDatabase::database("str1");
    } else {
        db = QSqlDatabase::addDatabase("QODBC", "str1");
    }

    db.setHostName("127.0.0.1");  // 确保替换为正确的数据库 IP 地址
    db.setPort(3306);  // MySQL 默认端口
    db.setDatabaseName("Mysql");  // 替换为实际的数据库名
    db.setUserName("wj");  // 替换为实际的用户名
    db.setPassword("O2l93IwJ");  // 替换为实际的密码

    if (!db.open()) {
        qDebug() << "数据库连接失败：" << db.lastError().text();  // 打印错误信息
        return;
    }

    QSqlQuery query(db);

    QString sql_1 = "select * from 用户表";  // 替换为实际的表名
    if (!query.exec(sql_1)) {
        qDebug() << "查询执行失败：" << query.lastError().text();  // 打印查询执行错误
        db.close();
        return;
    }

    while (query.next()) {
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
        qDebug() << query.value(2).toString();
    }

    db.close();
    QSqlDatabase::removeDatabase("str1");
}

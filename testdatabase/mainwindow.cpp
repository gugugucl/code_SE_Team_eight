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



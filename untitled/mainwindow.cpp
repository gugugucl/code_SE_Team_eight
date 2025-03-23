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

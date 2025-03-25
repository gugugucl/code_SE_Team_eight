#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void test();
private:
    Ui::MainWindow *ui;

    // 连接 MySQL 数据库
    bool connectDatabase();

    // 注册用户
    bool registerUser(const QString &username, const QString &password);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_switchToRegister_clicked();
    void on_switchToLogin_clicked();
};

#endif // MAINWINDOW_H

#ifndef USER_H
#define USER_H

#include <QString>


class User {
    private:
        int id;           // 用户ID
        QString name;     // 用户名
        QString password; // 密码

    public:
        // 构造函数
        User(int userId, const QString &userName, const QString &userPassword)
            : id(userId), name(userName), password(userPassword) {}

        // 获取用户ID
        unsigned int getId() const {

            return id;
        }

        // 获取用户名
        QString getName() const {
            return name;
        }

        // 设置用户名
        void setName(const QString &newName) {
            name = newName;
        }

        // 获取密码
        QString getPassword() const {
            return password;
        }

        // 设置密码
        void setPassword(const QString &newPassword) {
            password = newPassword;
        }

        // 用户登录验证（简单示例）
        bool authenticate(const QString &enteredPassword) const {
            return enteredPassword == password;
        }
    };


#endif // USER_H

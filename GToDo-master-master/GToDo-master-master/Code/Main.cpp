#include <QApplication>
#include <QFile>
#include <QLocale>
#include <QTranslator>
#include "GToDoItem.h"
#include <QSystemTrayIcon>
#include <QTextCodec>
#include "GSplashScreen.h"
#include  <QPropertyAnimation>
#include "GToDo.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
    QFile qss(":/qss/default.css");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    QFont font;
    font.setPointSize(9);
    font.setFamily("微软雅黑");
    app.setFont(font);
//    GSplashScreen s;//播放开始的ppt
//    QPropertyAnimation *animation = new QPropertyAnimation(&s,"windowOpacity");//动画类
//    animation->setDuration(300);
//    animation->setStartValue(0);
//    animation->setEndValue(1);
//    animation->setEasingCurve(QEasingCurve::InOutQuad);
//    animation->start();

//    s.show();
    GToDo *w = new GToDo();
    w->show();
    return app.exec();
}

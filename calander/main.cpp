#include "widget.h"
#include "STDateWidget.h"
#include "STCalandarWidget.h"
#include <QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    Widget w;

    //w.show();
    return a.exec();
}

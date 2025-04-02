#include "GQstringDate.h"

QString GQStringToQDate::QStringFromat(QString date)//在已完成的时间的截止日期特殊处理的格式
{
    QString ans;

    QDate qdate = QDate::fromString(date, "yyyy-MM-dd");
    if (!qdate.isValid()) {
        return "Invalid Date Format";
    }

    ans = QString("%1-%2").arg(qdate.month(), 2, 10, QLatin1Char('0')).arg(qdate.day(), 2, 10, QLatin1Char('0'));

    switch (qdate.dayOfWeek())
    {
    case Qt::Monday:
        ans += tr("周一");
        break;
    case Qt::Tuesday:
        ans += tr("周二");
        break;
    case Qt::Wednesday:
        ans += tr("周三");
        break;
    case Qt::Thursday:
        ans += tr("周四");
        break;
    case Qt::Friday:
        ans += tr("周五");
        break;
    case Qt::Saturday:
        ans += tr("周六");
        break;
    case Qt::Sunday:
        ans += tr("周日");
        break;
    }

    return ans;
}

QString GQStringToQDate::s_currentTitle = "null";
QString GQStringToQDate::s_currentDdl = "";
QPushButton* GQStringToQDate::btnShowFinished = nullptr;

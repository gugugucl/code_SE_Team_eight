#ifndef _GQSTRINGTOQDATE_H_
#define _GQSTRINGTOQDATE_H_
#include <QString>
#include <QStringList>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QPushButton>
class GQStringToQDate : public QWidget
{
       Q_OBJECT
public:
    static QString QStringFromat(QString date);
    static QString s_currentTitle,s_currentDdl;
    static QPushButton * btnShowFinished;
};

#endif

#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QWidget>
#include <QRectF>

class ClockWidget
    : public QWidget
{
    Q_OBJECT
public:
    ClockWidget(QWidget *parent);
    ~ClockWidget();
    QRectF textRectF(double radius, int pointSize, double angle);
    void paintEvent(QPaintEvent *event);

private:
};


#endif // CLOCKWIDGET_H

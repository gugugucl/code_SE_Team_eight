#ifndef _GBTNGROUP_H_
#define _GBTNGROUP_H_
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QMenu>
#include <QMessageBox>
#include "GQstringDate.h"

namespace Ui {
class GBtnGroup;
}

class GBtnGroup : public QWidget
{
    Q_OBJECT

public:
    explicit GBtnGroup(QWidget *parent = 0);
    ~GBtnGroup();
    void setText(QString name);

signals:
    void groupSwitch(QString group);
private slots:
    void on_pushButton_clicked();
    void on_btnDelete_clicked();
    void sltShowPopMenu(const QPoint& );
    void on_btnModify_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_button_doubleClicked(QPushButton *button);

private:
    QPushButton *m_editingButton = nullptr;
    Ui::GBtnGroup *ui;
    QMenu *popMenu;
};
#endif

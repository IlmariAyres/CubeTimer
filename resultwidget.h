#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>

#include "db.h"

namespace Ui {
class ResultWidget;
}

class ResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(QWidget *parent = 0, Entry entry = {0}, bool deletable = 0, int dispID = 0);
    ~ResultWidget();

    void deleteWidgetAndEntry();

signals:
    void deleteEntry(int e);

    void replay(QString s);

private slots:
    void on_DeleteButton_clicked();

    void on_ReplayButton_clicked();

private:
    Ui::ResultWidget *ui;

    Entry entry;
    int displayID;
};

#endif // RESULTWIDGET_H

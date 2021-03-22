#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "timer.h"
#include "scrambler.h"
#include "db.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_Inspection_valueChanged(int arg1);

    void on_NewScramble_clicked();

    void on_Puzzle_currentIndexChanged(int index);

    void on_ClearReults_clicked();

    void on_DeleteRequested(int e);

    void on_ResultAreaScrollDownRequest();

    void on_AverageXPicker_valueChanged(int arg1);

    void on_SuggestSrcamble(QString s);

private:
    Ui::MainWindow *ui;

    Timer timer;
    Scrambler scrambler;
    DB* db;

    bool saved = false;

    void clearResultArea();
    void addToResultArea(Entry e);
    void updateRecords();
};

#endif // MAINWINDOW_H

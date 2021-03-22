#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QStandardPaths>
#include <QDir>

#include <QLabel>
#include <QSpinBox>
#include <QKeyEvent>
#include <QComboBox>
#include <QLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QFormLayout>
#include <QMessageBox>

#include "resultwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList l =  QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QString s = l.at(0);

    if(!QDir().exists(s))
        QDir().mkdir(s);

    db = new DB(s.append("/cubetimes.db"));

    scrambler.LoadDirectory(QDir(":/puzzles"));
    for(int i = 0; i < scrambler.puzzles.length(); i++)
    {
        ui->Puzzle->addItem(scrambler.puzzles[i]->name, i);
    }

    timer.setInspection(ui->Inspection->value());

    on_NewScramble_clicked();
    startTimer(1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

void MainWindow::addToResultArea(Entry e)
{
    ResultWidget* rw = new ResultWidget(ui->ResultArea, e, true);
    ui->ResultAreaLayout->addWidget((rw));
    QObject::connect(rw, &ResultWidget::replay, this, &MainWindow::on_SuggestSrcamble);
    QObject::connect(rw, &ResultWidget::deleteEntry, this, &MainWindow::on_DeleteRequested);
    QTimer::singleShot(5, this, SLOT(on_ResultAreaScrollDownRequest()));
}

void MainWindow::updateRecords()
{
    ResultWidget* best = new ResultWidget(this, db->getBest());
    QLayoutItem* pre = ui->PuzzleForm->replaceWidget(ui->BestResult, best);
    delete pre->widget();
    delete pre;
    ui->BestResult = best;

    QObject::connect(best, &ResultWidget::replay, this, &MainWindow::on_SuggestSrcamble);

    ui->A5Result->setText(TimeC::getQStr(db->getAverage(5)));
    ui->A10Result->setText(TimeC::getQStr(db->getAverage(10)));
    ui->AXResult->setText(TimeC::getQStr(db->getAverage(ui->AverageXPicker->value())));
    ui->AverageResult->setText(TimeC::getQStr(db->getAverage(-1)));
}

void MainWindow::clearResultArea()
{
    QLayoutItem* item;
    while((item = ui->ResultAreaLayout->layout()->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }

    ui->ResultArea->repaint();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    TimeC t = timer.getTime();

    ui->time->setText(t.getQStr());

    if(t.state == STATE_FINAL && !saved)
    {
        saved = true;
        addToResultArea(db->newEntry(t.time, ui->Scramble->text()));
        updateRecords();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == 32)
        {
            switch(timer.getState())
            {
            case STATE_INSPECTING:
                timer.stopInspection();
                break;
            case STATE_RUNNING:
                timer.stopTimer();
                break;
            }
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(event->key() == 32)
        {
            switch(timer.getState())
            {
            case STATE_INITIAL:
                timer.startInspection();
                break;
            case STATE_STOPPED:
                timer.startTimer();
                break;
            }
        }
    }
}

void MainWindow::on_Inspection_valueChanged(int arg1)
{
    timer.setInspection(arg1);
}

void MainWindow::on_NewScramble_clicked()
{
    ui->Scramble->setText(scrambler.Scramble(ui->Puzzle->currentData().toInt()));
    timer.reset();
    this->setFocus();
    saved = false;
}

void MainWindow::on_Puzzle_currentIndexChanged(int index)
{
    clearResultArea();

    db->setTable(scrambler.puzzles[index]->name);

    QVector<Entry>* e = db->getEntries();
    for(int i = 0; i < e->length(); i++)
        addToResultArea((*e)[i]);
    delete e;

    updateRecords();

    on_NewScramble_clicked();
}

void MainWindow::on_ClearReults_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to permanently delete all entries?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes)
    {
        QLayoutItem* item;
        while((item = ui->ResultAreaLayout->layout()->takeAt(0)) != NULL)
            ((ResultWidget*)(item->widget()))->deleteWidgetAndEntry();

        ui->ResultArea->repaint();
    }
}

void MainWindow::on_DeleteRequested(int id)
{
    db->deleteEntry(id);
    updateRecords();
}

void MainWindow::on_ResultAreaScrollDownRequest()
{
    ui->ResultArea->verticalScrollBar()->setValue(ui->ResultArea->verticalScrollBar()->maximum());
}

void MainWindow::on_AverageXPicker_valueChanged(int arg1)
{
    updateRecords();
}

void MainWindow::on_SuggestSrcamble(QString s)
{
    if(timer.getState() == STATE_INITIAL || timer.getState() == STATE_FINAL)
    {
        ui->Scramble->setText(s);
        timer.reset();
        setFocus();
        saved = false;
    }
}

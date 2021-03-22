#include "resultwidget.h"
#include "ui_resultwidget.h"

#include "timec.h"

#include <QLabel>

ResultWidget::ResultWidget(QWidget *parent, Entry entry, bool deletable, int dispID) :
    QWidget(parent),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
    this->entry = entry;
    this->displayID = dispID ?: entry.id;

    if(!deletable)
        delete ui->DeleteButton;

    if(this->displayID)
        ui->ID->setText(QString::number(this->displayID).append(": "));
    else
        delete ui->ID;

    ui->Time->setText(TimeC::getQStr(entry.resulttime));

    setToolTip("Scramble: " + entry.scramble);
}

ResultWidget::~ResultWidget()
{
    delete ui;
}

void ResultWidget::deleteWidgetAndEntry()
{
    emit deleteEntry(entry.id);
    delete this;
}

void ResultWidget::on_DeleteButton_clicked()
{
    deleteWidgetAndEntry();
}

void ResultWidget::on_ReplayButton_clicked()
{
    emit replay(entry.scramble);
}

#include <timec.h>

#include "mainwindow.h"
#include <QApplication>

#include "scrambler.h"
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

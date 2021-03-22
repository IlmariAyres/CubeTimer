#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include <QDir>
#include <QVector>

#include "puzzle.h"

class Scrambler
{
public:
    Scrambler();
    ~Scrambler();

    void LoadDirectory(QDir dir);
    QString Scramble(int i);

    QVector<Puzzle*> puzzles;
};

#endif // SCRAMBLER_H

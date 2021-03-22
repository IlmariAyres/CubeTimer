#ifndef PUZZLE_H
#define PUZZLE_H

#include <QString>
#include <QStringList>
#include <QVector>

struct Moveset
{
    QStringList sides;
    QStringList suffix;
};

class Puzzle
{
public:
    Puzzle(QString name, int id, int levels, QVector<Moveset> movesets, int moves);

    static Puzzle* puzzleFactory(QString puz);

    QString name;
    int id;
    int levels;
    QVector<Moveset> movesets;
    int moves;

    static bool lessthan(Puzzle* a, Puzzle* b);

};

#endif // PUZZLE_H

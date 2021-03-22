#include "puzzle.h"

Puzzle::Puzzle(QString name, int id, int levels, QVector<Moveset> movesets, int moves)
{
    this->name = name;
    this->id = id;
    this->levels = levels;
    this->movesets = movesets;
    this->moves = moves;
}

Puzzle* Puzzle::puzzleFactory(QString puz)
{
    QStringList strl = puz.split("\n");

    if(strl.length() < 6)
        return nullptr;

    QString name = strl[0];
    int id = strl[1].toInt();
    int levels = strl[2].toInt();
    int moves = strl[3].toInt();

    QVector<Moveset> movesets;

    for(int i = 4; i < strl.length() - 1; i += 2)
    {
        Moveset ms;
        ms.sides = strl[i].split(" ");
        ms.suffix = strl[i + 1].split(" ");

        for(int j = 0; j < ms.suffix.length(); j++)
        {
            if(ms.suffix[j] == "_")
                ms.suffix[j] = "";
        }

        movesets.push_back(ms);
    }

    return new Puzzle(name, id, levels, movesets, moves);
}

bool Puzzle::lessthan(Puzzle* a, Puzzle* b)
{
    return a->id < b->id;
}


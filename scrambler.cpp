#include "scrambler.h"

#include <QTextStream>
#include <algorithm>

Scrambler::Scrambler()
{
}

Scrambler::~Scrambler()
{
    for(int i = 0; i < puzzles.size(); i++)
    {
        delete puzzles[i];
    }
}

void Scrambler::LoadDirectory(QDir dir)
{
    QFileInfoList ls = dir.entryInfoList();

    for(int i = 0; i < ls.length(); i++)
    {
        if(ls[i].isFile() && ls[i].fileName().endsWith(".puz"))
        {
            QFile f(ls[i].filePath());
            if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) continue;
            QTextStream in(&f);
            QString str = in.readAll();
            f.close();

            Puzzle *p = Puzzle::puzzleFactory(str);
            if(p != nullptr)
            {
                puzzles.push_back(p);
            }
        }
    }

    std::sort(puzzles.begin(), puzzles.end(), Puzzle::lessthan);
}

QString Scrambler::Scramble(int id)
{
    QString ret = " ";

    int sides = 0;
    for(int i = 0; i < puzzles[id]->movesets.size(); i++)
        sides += puzzles[id]->movesets[i].sides.length();

    int sn = -1;
    int psn = -1;

    for(int i = 0; i < puzzles[id]->moves; i++)
    {
        QString num = QString::number(qrand() % puzzles[id]->levels + 1);
        if(num == "1")
            num = "";

        while(sn == psn)
        {
            sn = qrand() % sides;
        }
        psn = sn;

        int set = 0;
        while(sn >= puzzles[id]->movesets[set].sides.length())
        {
            sn -= puzzles[id]->movesets[set].sides.length();
            set++;
        }

        ret.append(num).append(puzzles[id]->movesets[set].sides[sn]).append(puzzles[id]->movesets[set].suffix[qrand() % puzzles[id]->movesets[set].suffix.length()]).append(" ");
    }

    return ret;
}

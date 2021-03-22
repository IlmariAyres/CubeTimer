#ifndef DB_H
#define DB_H

#include <QString>
#include <QVector>
#include <QtSql>

struct Entry
{
    int id;
    int timestamp;
    int resulttime;
    QString scramble;
};

class DB
{
public:
    DB(QString path);
    ~DB();

    void setTable(QString table);
    Entry newEntry(int resulttime, QString scramble, int timestamp = -1, int id = -1);
    QVector<Entry>* getEntries();
    void clearTable();
    void deleteEntry(int id);

    Entry getBest();
    int getAverage(int n);

private:
    QSqlDatabase m_db;
    QString table;
};

#endif // DB_H

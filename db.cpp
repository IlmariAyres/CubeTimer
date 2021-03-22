#include "db.h"

#include <iostream>

DB::DB(QString path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
        std::cout << "Error: connection with database fail" << std::endl;
    else
        std::cout << "Database: connection ok" << std::endl;
}

DB::~DB()
{
    m_db.close();
}

void DB::setTable(QString table)
{
    QString name = table;
    name.replace(" ", "_").prepend("Cube_");

    QSqlQuery q;
    q.prepare("CREATE TABLE IF NOT EXISTS " + name + " (timeresult INT, timestamp INT, scramble TEXT)");
    std::cout << q.exec() << std::endl << q.lastError().text().toStdString() << std::endl;

    this->table = name;
}

Entry DB::newEntry(int resulttime, QString scramble, int timestamp, int id)
{
    if(timestamp < 0)
        timestamp = QDateTime::currentDateTime().toSecsSinceEpoch();

    QSqlQuery q;
    q.prepare("INSERT INTO " + table + " (timeresult, timestamp, scramble) VALUES (:timeresult, :timestamp, :scramble)");
    q.bindValue(":timeresult", resulttime);
    q.bindValue(":timestamp", timestamp);
    q.bindValue(":scramble", scramble);
    q.exec();

    id = q.lastInsertId().toInt();

    Entry ret;
    ret.id = id;
    ret.resulttime = resulttime;
    ret.scramble = scramble;
    ret.timestamp = timestamp;
    return ret;
}

QVector<Entry>* DB::getEntries()
{
    QVector<Entry>* ret = new QVector<Entry>;

    QSqlQuery q;
    q.prepare("SELECT rowid, * FROM " + table + " ORDER BY timestamp");
    q.setForwardOnly(true);
    q.exec();

    int NoRowid = q.record().indexOf("rowid");
    int NoTimeResult = q.record().indexOf("timeresult");
    int NoTimestamp = q.record().indexOf("timestamp");
    int NoScramble = q.record().indexOf("scramble");

    while (q.next())
    {
        Entry e;
        e.id = q.value(NoRowid).toInt();
        e.resulttime = q.value(NoTimeResult).toInt();
        e.timestamp = q.value(NoTimestamp).toInt();
        e.scramble = q.value(NoScramble).toString();
        ret->push_back(e);
    }

    return ret;
}

void DB::clearTable()
{
    QSqlQuery q;
    q.prepare("DELETE FROM " + table);
    q.exec();
}

void DB::deleteEntry(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM " + table + " WHERE rowid = ?");
    q.bindValue(0, id);
    q.exec();
}

Entry DB::getBest()
{
    QSqlQuery q;
    q.prepare("SELECT rowid, * FROM " + table + " ORDER BY timeresult LIMIT 1");
    q.setForwardOnly(true);
    q.exec();

    int NoRowid = q.record().indexOf("rowid");
    int NoTimeResult = q.record().indexOf("timeresult");
    int NoTimestamp = q.record().indexOf("timestamp");
    int NoScramble = q.record().indexOf("scramble");

    if(q.next())
    {
        Entry e;
        e.id = q.value(NoRowid).toInt();
        e.resulttime = q.value(NoTimeResult).toInt();
        e.timestamp = q.value(NoTimestamp).toInt();
        e.scramble = q.value(NoScramble).toString();
        return e;
    }
    else
        return {0, 0, 0, 0};
}

int DB::getAverage(int n)
{
    int ret = 0;
    QSqlQuery q;

    if(n > 0)
    {
        q.prepare("SELECT rowid, * FROM " + table + " ORDER BY rowid DESC LIMIT ?");
        q.bindValue(0, n);
        q.setForwardOnly(true);
        q.exec();

        int NoTimeResult = q.record().indexOf("timeresult");

        for(int i = 0; i < n; i++)
        {
            if(q.next())
                ret += q.value(NoTimeResult).toInt();
            else
                return -1;
        }

        return ret / n;
    }
    else
    {
        q.prepare("SELECT rowid, * FROM " + table + " ORDER BY rowid DESC");
        q.setForwardOnly(true);
        q.exec();

         int NoTimeResult = q.record().indexOf("timeresult");

        int count = 0;
        while(q.next())
        {
            ret += q.value(NoTimeResult).toInt();
            count++;
        }

        if(count > 0)
            return ret / count;
        else
            return -1;
    }
}

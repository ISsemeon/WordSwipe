#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database {
public:
    Database(const QString &path);
    ~Database();

    bool open();
    void close();
    QSqlQuery execQuery(const QString &queryStr);

private:
    QSqlDatabase db;
};

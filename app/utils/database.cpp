#include "database.h"

Database::Database(const QString &path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

Database::~Database() {
    close();
}

bool Database::open() {
    if (!db.open()) {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return false;
    }
    return true;
}

void Database::close() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlQuery Database::execQuery(const QString &queryStr) {
    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        qWarning() << "Query failed:" << query.lastError().text();
    }
    return query;
}

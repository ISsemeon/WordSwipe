#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Constructs a Database object and sets up the database.
 */
Database::Database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wordswipe.db");
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    }
    setupTables();
}

/**
 * @brief Sets up the necessary tables in the database.
 */
void Database::setupTables() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Folders (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, color TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS Modules (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, folder_id INTEGER, FOREIGN KEY(folder_id) REFERENCES Folders(id))");
    query.exec("CREATE TABLE IF NOT EXISTS Cards (id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT, answer TEXT, image TEXT, module_id INTEGER, FOREIGN KEY(module_id) REFERENCES Modules(id))");
}

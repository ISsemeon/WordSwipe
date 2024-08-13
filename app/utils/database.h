#pragma once

#include <QSqlDatabase>

/**
 * @brief Handles database operations.
 */
class Database {
public:
    Database();

private:
    QSqlDatabase db;

    void setupTables();
};

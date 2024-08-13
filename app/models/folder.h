#pragma once

#include <QString>
#include <QList>

/**
 * @brief Represents a folder containing modules.
 */
class Folder {
public:
    int id;                 // Unique identifier for the folder
    QString name;           // Name of the folder
    QString color;          // Color associated with the folder
    QList<int> moduleIds;   // List of module IDs associated with this folder
};

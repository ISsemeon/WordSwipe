#pragma once

#include <QString>
#include <QList>

/**
 * @brief Represents a module containing cards.
 */
class Module {
public:
    int id;                 // Unique identifier for the module
    QString name;           // Name of the module
    QList<int> cardIds;     // List of card IDs associated with this module
};

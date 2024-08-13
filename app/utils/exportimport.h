#pragma once

#include <QString>

/**
 * @brief Exports data to a JSON file.
 * @param filePath Path to the file where data will be exported.
 */
void exportData(const QString &filePath);

/**
 * @brief Imports data from a JSON file.
 * @param filePath Path to the file from which data will be imported.
 */
void importData(const QString &filePath);

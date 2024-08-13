#include "exportimport.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

/**
 * @brief Exports data to a JSON file.
 * @param filePath Path to the file where data will be exported.
 */
void exportData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    QJsonObject jsonObject;
    // Populate jsonObject with data from the database
    QJsonDocument doc(jsonObject);
    file.write(doc.toJson());
    file.close();
}

/**
 * @brief Imports data from a JSON file.
 * @param filePath Path to the file from which data will be imported.
 */
void importData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject jsonObject = doc.object();
    // Process jsonObject and save data to the database
}

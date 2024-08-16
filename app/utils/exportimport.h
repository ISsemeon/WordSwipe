#pragma once

#include <QString>

class ExportImport {
public:
    static bool exportToJson(const QString &filePath);
    static bool importFromJson(const QString &filePath);
};

#include "DataController.h"
#include <QDebug>

DataController::DataController(QObject *parent)
    : QObject(parent) {
    // Initialize with some data
    addFolder("Folder 1");
    addFolder("Folder 2");
}

void DataController::addFolder(const QString &name) {
    QSharedPointer<Folder> folder(new Folder);
    folder->setName(name);
    m_folders.append(folder);

    updateFoldersModel();
    emit foldersModelChanged();
}

void DataController::selectFolder(int index) {
    if (index >= 0 && index < m_folders.size()) {
        qDebug() << "Selected Folder:" << m_folders[index]->name();
        // Handle folder selection
    }
}

QVariantList DataController::foldersModel() const {
    return m_foldersModel;
}

void DataController::updateFoldersModel() {
    m_foldersModel.clear();
    for (const auto &folder : m_folders) {
        QVariantMap map;
        map["name"] = folder->name();
        m_foldersModel.append(map);
    }
}

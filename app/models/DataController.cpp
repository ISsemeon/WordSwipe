#include "DataController.h"
#include <QDebug>

DataController::DataController(QObject *parent) : QObject(parent), m_foldersModel(new FolderModel(this)) {
    // Initialize with some data
    addFolder("Folder 1");
    addFolder("Folder 2");
}

void DataController::addFolder(const QString &name) {
    QSharedPointer<Folder> folder(new Folder);
    folder->setName(name);
    m_foldersModel->addFolder(folder);

    emit foldersModelChanged();
}

void DataController::addModuleToSelectedFolder(const QString &moduleName, const QString &moduleColor) {
    if (m_selectedFolder) {
        m_selectedFolder->addModule(moduleName, moduleColor);
        // Notify if needed
    }
}

void DataController::selectFolder(int index) {
    if (index >= 0 && index < m_foldersModel->rowCount()) {
        auto folder = m_foldersModel->data(m_foldersModel->index(index), FolderModel::NameRole).value<QSharedPointer<Folder>>();
        if (folder) {
            m_selectedFolder = folder;
            qDebug() << "Selected Folder:" << folder->name();
        } else {
            qDebug() << "Failed to get folder at index:" << index;
        }
    } else {
        qDebug() << "Index out of range:" << index;
    }
}
FolderModel* DataController::foldersModel() const {
    return m_foldersModel;
}

QString DataController::newFolderName() const {
    return m_newFolderName;
}

void DataController::setNewFolderName(const QString &name) {
    if (m_newFolderName != name) {
        m_newFolderName = name;
        emit newFolderNameChanged();
    }
}

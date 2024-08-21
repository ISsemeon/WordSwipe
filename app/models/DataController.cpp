#include "DataController.h"
#include <QDebug>

DataController::DataController(QObject *parent) : QObject(parent), m_foldersModel(new FolderModel(this)) {
    // Initialize with some data
    addFolder("Folder 1");
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

void DataController::selectFolder(int index)
{
    if (index >= 0 && index < m_foldersModel->rowCount()) {
        QVariant variant = m_foldersModel->data(m_foldersModel->index(index), FolderModel::FolderRole);
        auto folder = variant.value<QSharedPointer<Folder>>();
        if (folder) {
            m_selectedFolder = folder;
            emit selectedFolderChanged();
            qDebug() << "Selected Folder:" << folder->name();
        } else {
            qDebug() << "Failed to get folder at index:" << index;
        }
    } else {
        qDebug() << "Index out of range:" << index;
    }
}

QString DataController::selectedFolderName() const
{

    if (m_selectedFolder) {
        return m_selectedFolder->name();
    }
    return QString("No Folder Selected");
}

Folder* DataController::selectedFolder()
{
    if(m_selectedFolder)
        return m_selectedFolder.data();
    return nullptr;
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

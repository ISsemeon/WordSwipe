#include "DataController.h"
#include <QDebug>

DataController::DataController(QObject *parent) :
    QObject(parent),
    m_foldersModel(new FolderModel(this))
    ,m_selectedFolder(),
    m_selectedModule()
{
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
void DataController::selectModule(int index) {
    if (m_selectedFolder && index >= 0 && index < m_selectedFolder->modulesModel()->rowCount()) {
        QVariant variant = m_selectedFolder->modulesModel()->data(m_selectedFolder->modulesModel()->index(index), ModuleModel::ModuleRole);
        auto module = variant.value<QSharedPointer<Module>>();
        if (module) {
            m_selectedModule = module;
            emit selectedModuleChanged();
            qDebug() << "Selected Module:" << module->name();
        } else {
            qDebug() << "Failed to get module at index:" << index;
        }
    } else {
        qDebug() << "Index out of range or no folder selected.";
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

Module* DataController::selectedModule()
{
    if (m_selectedModule) {
        return m_selectedModule.data();
    }
    return nullptr;
}

#include "DataController.h"
#include <QDebug>
#include "SessionManager.h"


DataController::DataController(QObject *parent) :
    QObject(parent),
    m_foldersModel(new FolderModel(this))
    ,m_selectedFolder(),
    m_selectedModule()
{
    // Initialize with some data
//    addFolder("Folder 1");
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

void DataController::addCardToSelectedModule(const QString &word, const QString &translation) {
    if (m_selectedModule) {
        m_selectedModule->addCard(word, translation);
        emit selectedModuleChanged(); // Обновляем UI
    }
}

void DataController::deleteSelectedModule() {
    if (m_selectedFolder && m_selectedModule) {
        // Получите модель модулей выбранной папки
        auto modulesModel = m_selectedFolder->modulesModel();

        // Найдите индекс выбранного модуля
        int index = -1;
        for (int i = 0; i < modulesModel->rowCount(); ++i) {
            QModelIndex modelIndex = modulesModel->index(i);
            auto module = modulesModel->data(modelIndex, ModuleModel::ModuleRole).value<QSharedPointer<Module>>();
            if (module == m_selectedModule) {
                index = i;
                break;
            }
        }

        if (index >= 0) {
            // Удалите модуль из модели
            m_selectedFolder->removeModule(index);
            m_selectedModule.reset(); // Сбросить выбранный модуль
            emit selectedModuleChanged(); // Обновите UI
        } else {
            qDebug() << "Module not found in the model.";
        }
    } else {
        qDebug() << "No folder or module selected.";
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

QList<QSharedPointer<Folder>> DataController::getFolders() const {
    QList<QSharedPointer<Folder>> folders;
    for (int i = 0; i < m_foldersModel->rowCount(); ++i) {
        QModelIndex index = m_foldersModel->index(i);
        QSharedPointer<Folder> folder = m_foldersModel->data(index, FolderModel::FolderRole).value<QSharedPointer<Folder>>();
        folders.append(folder);
    }
    return folders;
}

void DataController::setFolders(const QList<QSharedPointer<Folder>> &folders) {
    m_foldersModel->clear();
    for (const auto &folder : folders) {
        m_foldersModel->addFolder(folder);
    }
}


void DataController::saveSession() {
    // Extract the list of folders from the model
    QList<QSharedPointer<Folder>> folders;
    for (int i = 0; i < m_foldersModel->rowCount(); ++i) {
        QModelIndex index = m_foldersModel->index(i);
        QSharedPointer<Folder> folder = m_foldersModel->data(index, FolderModel::FolderRole).value<QSharedPointer<Folder>>();
        folders.append(folder);
    }

    // Call the SessionManager to save the session
    SessionManager::saveSession(sessionFilePath, folders);
}

void DataController::loadSession() {
    QList<QSharedPointer<Folder>> folders;
    if (SessionManager::loadSession(sessionFilePath, folders)) {
        // Update the model with the loaded folders
        m_foldersModel->clear();
        for (const auto &folder : folders) {
            m_foldersModel->addFolder(folder);
        }
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

Module* DataController::selectedModule()
{
    if (m_selectedModule) {
        return m_selectedModule.data();
    }
    return nullptr;
}

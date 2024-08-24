#pragma once

#include "FolderModel.h"
#include <QObject>
#include <QSharedPointer>

class DataController : public QObject {
    Q_OBJECT
    Q_PROPERTY(FolderModel* foldersModel READ foldersModel NOTIFY foldersModelChanged)
    Q_PROPERTY(QString newFolderName READ newFolderName WRITE setNewFolderName NOTIFY newFolderNameChanged)
    Q_PROPERTY(Folder* selectedFolder READ selectedFolder NOTIFY selectedFolderChanged)
    Q_PROPERTY(Module* selectedModule READ selectedModule NOTIFY selectedModuleChanged)



public:
    explicit DataController(QObject *parent = nullptr);

    Q_INVOKABLE void addFolder(const QString &name);
    Q_INVOKABLE void addModuleToSelectedFolder(const QString &moduleName, const QString &moduleColor);
    Q_INVOKABLE void selectFolder(int index);
    Q_INVOKABLE void selectModule(int index);
    Q_INVOKABLE void addCardToSelectedModule(const QString &word, const QString &translation);

    //ei
    Q_INVOKABLE bool exportSelectedFolder(const QString &filePath);

    Q_INVOKABLE bool importFolder(const QString &filePath);
    Q_INVOKABLE bool exportSelectedModule(const QString &filePath);
    Q_INVOKABLE bool importModule(const QString &filePath);

    Q_INVOKABLE bool hasUnfilledCards() const;





public slots:
    void deleteSelectedModule();
    void deleteSelectedFolder();

public:


    QString selectedFolderName() const;
    Folder* selectedFolder();

    QList<QSharedPointer<Folder>> getFolders() const;
    void setFolders(const QList<QSharedPointer<Folder>> &folders);

    FolderModel* foldersModel() const;
    QString newFolderName() const;
    void setNewFolderName(const QString &name);
    Module* selectedModule();

    Q_INVOKABLE void saveSession();
    Q_INVOKABLE void loadSession();


    //for study mode
    Q_INVOKABLE CardsModel* getCardsModelInSelectedFolder() const;
    Q_INVOKABLE CardsModel* getCardsModelInSelectedModule() const;

signals:
    void foldersModelChanged();
    void newFolderNameChanged();
    void selectedFolderChanged();
    void selectedModuleChanged();


private:

    const QString sessionFilePath = "session.json";

    QSharedPointer<Module> m_selectedModule;
    FolderModel* m_foldersModel;
    QSharedPointer<Folder> m_selectedFolder;
    QString m_newFolderName;


private:
    bool checkIfModuleHasUnfilledCards(const Module* module) const;
};

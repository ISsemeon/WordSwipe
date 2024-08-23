#pragma once

#include <QObject>
#include <QSharedPointer>
#include "ModuleModel.h"

class Folder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(ModuleModel* modulesModel READ modulesModel NOTIFY modulesModelChanged)  // Заменен тип

public:
    explicit Folder(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    ModuleModel* modulesModel() ;  // Метод для доступа к модели модулей
    void addModule(const QString &name, const QString &color);

public slots:
    void removeModule(int index);

signals:
    void nameChanged();
    void modulesModelChanged();  // Сигнал для изменения модели

private:
    QString m_name;
    ModuleModel m_modulesModel;  // Использование ModuleModel вместо QList
};

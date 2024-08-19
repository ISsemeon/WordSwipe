// folder.h
#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "module.h"

class Folder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<Module*> modules READ modules NOTIFY modulesChanged)

public:
    explicit Folder(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QList<Module*> modules() const;

    Q_INVOKABLE void addModule(const QString &name, const QString &color);

signals:
    void nameChanged();
    void modulesChanged();

private:
    QString m_name;
    QList<Module*> m_modules;
};

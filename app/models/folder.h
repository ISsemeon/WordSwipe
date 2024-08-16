#pragma once

#include <QObject>
#include <QString>
#include <QList>

class Module;  // Forward declaration

class Folder : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<QObject*> modules READ modules NOTIFY modulesChanged)

public:
    explicit Folder(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QList<QObject*> modules() const;

signals:
    void nameChanged();
    void modulesChanged();

private:
    QString m_name;
    QList<QObject*> m_modules;
};

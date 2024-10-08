#pragma once
// ModuleModel.h
#include <QAbstractListModel>
#include "module.h"

class ModuleModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Role {
        NameRole = Qt::UserRole + 1,
        ColorRole,
        ModuleRole
    };

    explicit ModuleModel(QObject *parent = nullptr);

    void removeModule(int index);

    public:
    Q_INVOKABLE void removeRow(int index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addModule(const QSharedPointer<Module> &module);

    void updateModule(int index);

    QList<QSharedPointer<Module>> modules() const;
private:
    QList<QSharedPointer<Module>> m_modules;
};

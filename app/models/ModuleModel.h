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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addModule(const QSharedPointer<Module> &module);

    void updateModule(int index);
private:
    QList<QSharedPointer<Module>> m_modules;
};

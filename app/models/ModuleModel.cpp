// ModuleModel.cpp
#include "ModuleModel.h"

ModuleModel::ModuleModel(QObject *parent)
    : QAbstractListModel(parent)
    {
    auto module = QSharedPointer<Module>::create(this);
    module->setName("test");
    module->setColor("test");
    m_modules.append(module);

    addModule(module);
}

int ModuleModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_modules.size();
}

QVariant ModuleModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_modules.size()) {
        return QVariant();
    }

    const auto module = m_modules[index.row()];
    if (role == NameRole) {
        return module->name();
    } else if (role == ColorRole) {
        return module->color();
    }

    return QVariant();
}

QHash<int, QByteArray> ModuleModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ColorRole] = "color";
    return roles;
}

void ModuleModel::addModule(const QSharedPointer<Module> &module) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_modules.append(module);
    endInsertRows();
}

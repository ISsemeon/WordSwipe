// ModuleModel.cpp
#include "ModuleModel.h"

ModuleModel::ModuleModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ModuleModel::removeModule(int index) {
    if (index >= 0 && index < m_modules.size()) {
        beginRemoveRows(QModelIndex(), index, index);
        m_modules.removeAt(index);
        endRemoveRows();
    }
}

void ModuleModel::removeRow(int index) {
    if (index >= 0 && index < rowCount()) {
        beginRemoveRows(QModelIndex(), index, index);
        // Удалите элемент из данных модели
        m_modules.removeAt(index);
        endRemoveRows();
    }
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
    }
    else if (role == ColorRole) {
        return module->color();
    }
    else if (role == ModuleRole)
    {
        return QVariant::fromValue(module);
    }


    return QVariant();
}

void ModuleModel::updateModule(int index) {
    emit dataChanged(this->index(index), this->index(index));
}

QList<QSharedPointer<Module> > ModuleModel::modules() const
{
    return m_modules;
}

QHash<int, QByteArray> ModuleModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ColorRole] = "color";
    roles[ModuleRole] = "module";
    return roles;
}

void ModuleModel::addModule(const QSharedPointer<Module> &module) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_modules.prepend(module);
    endInsertRows();
}

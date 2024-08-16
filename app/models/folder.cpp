#include "folder.h"

Folder::Folder(QObject *parent)
    : QObject(parent) {}

QString Folder::name() const {
    return m_name;
}

void Folder::setName(const QString &name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QList<QObject*> Folder::modules() const {
    return m_modules;
}

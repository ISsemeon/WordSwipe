// folder.cpp
#include "folder.h"

Folder::Folder(QObject *parent) : QObject(parent) {}

QString Folder::name() const {
    return m_name;
}

void Folder::setName(const QString &name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QList<Module*> Folder::modules() const {
    return m_modules;
}

void Folder::addModule(const QString &name, const QString &color) {
    Module *module = new Module(this);
    module->setName(name);
    module->setColor(color);
    m_modules.append(module);
    emit modulesChanged();
}

#include "folder.h"

Folder::Folder(QObject *parent)
    : QObject(parent),
      m_modulesModel(new ModuleModel(this))
{
//    addModule("test", "white");
//    addModule("test", "green");
//    addModule("test", "blue");
//    addModule("test", "white");
//    addModule("test", "green");
//    addModule("test", "blue");
//    addModule("test", "white");
//    addModule("test", "green");
//    addModule("test", "blue");
}

QString Folder::name() const
{
    return m_name;
}

void Folder::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

ModuleModel* Folder::modulesModel()
{
    return &m_modulesModel;  // Возвращаем указатель на модель модулей
}

void Folder::addModule(const QString &name, const QString &color)
{
    auto module = QSharedPointer<Module>::create(this);
    module->setName(name);
    module->setColor(color);
    m_modulesModel.addModule(module);  // Добавляем модуль через модель
    emit modulesModelChanged();  // Оповещаем об изменении модели
}

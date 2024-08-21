#include "Module.h"

Module::Module(QObject *parent)
    : QObject(parent)
    , m_cardsModel(new CardsModel(this))
{
}

QString Module::name() const {
    return m_name;
}

void Module::setName(const QString &name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QString Module::color() const {
    return m_color;
}

void Module::setColor(const QString &color) {
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
    }
}

CardsModel* Module::cardsModel() const {
    return m_cardsModel;
}

void Module::addCard(const QString &question, const QString &answer) {
    QSharedPointer<Card> card(new Card(question, answer));
    m_cardsModel->addCard(card);
    emit cardsModelChanged();
}

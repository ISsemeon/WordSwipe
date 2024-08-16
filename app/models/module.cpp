// module.cpp
#include "module.h"

Module::Module(QObject *parent)
    : QObject(parent)
{
}

QString Module::name() const
{
    return m_name;
}

void Module::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QString Module::color() const
{
    return m_color;
}

void Module::setColor(const QString &color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
    }
}

QList<Card*> Module::cards() const
{
    return m_cards;
}

void Module::addCard(const QString &question, const QString &answer, const QString &imagePath)
{
    Card *card = new Card(this);
    card->setQuestion(question);
    card->setAnswer(answer);
    card->setImagePath(imagePath);
    m_cards.append(card);
    emit cardsChanged();
}

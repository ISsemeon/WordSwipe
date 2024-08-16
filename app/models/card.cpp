// card.cpp
#include "card.h"

Card::Card(QObject *parent)
    : QObject(parent)
{
}

QString Card::question() const
{
    return m_question;
}

void Card::setQuestion(const QString &question)
{
    if (m_question != question) {
        m_question = question;
        emit questionChanged();
    }
}

QString Card::answer() const
{
    return m_answer;
}

void Card::setAnswer(const QString &answer)
{
    if (m_answer != answer) {
        m_answer = answer;
        emit answerChanged();
    }
}

QString Card::imagePath() const
{
    return m_imagePath;
}

void Card::setImagePath(const QString &imagePath)
{
    if (m_imagePath != imagePath) {
        m_imagePath = imagePath;
        emit imagePathChanged();
    }
}

// card.cpp
#include "card.h"

Card::Card(QObject *parent)
    : QObject(parent)
{
}

Card::Card(const QString &question, const QString &answer, QObject *parent)
    : QObject(parent)
    , m_question(question)
    , m_answer(answer)
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

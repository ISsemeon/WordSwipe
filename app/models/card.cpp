#include "card.h"

Card::Card(QObject *parent)
    : QObject(parent)
    , m_recorded(false) // Initialize recorded to false
{
}

Card::Card(const QString &question, const QString &answer, bool recorded, QObject *parent)
    : QObject(parent)
    , m_question(question)
    , m_answer(answer)
    , m_recorded(recorded)
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

bool Card::recorded() const
{
    return m_recorded;
}

void Card::setRecorded(bool recorded)
{
    if (m_recorded != recorded) {
        m_recorded = recorded;
        emit recordedChanged();
    }
}

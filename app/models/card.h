// card.h
#pragma once

#include <QObject>
#include <QString>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString answer READ answer WRITE setAnswer NOTIFY answerChanged)

public:
    explicit Card(QObject *parent = nullptr);
    Card(const QString &question, const QString &answer, QObject *parent = nullptr);

    QString question() const;
    void setQuestion(const QString &question);

    QString answer() const;
    void setAnswer(const QString &answer);

signals:
    void questionChanged();
    void answerChanged();

private:
    QString m_question;
    QString m_answer;
};


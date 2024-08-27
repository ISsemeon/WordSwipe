#pragma once

#include <QObject>
#include <QString>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString answer READ answer WRITE setAnswer NOTIFY answerChanged)
    Q_PROPERTY(bool recorded READ recorded WRITE setRecorded NOTIFY recordedChanged)

public:
    explicit Card(QObject *parent = nullptr);
    Card(const QString &question, const QString &answer, bool recorded = false, QObject *parent = nullptr);

    QString question() const;
    void setQuestion(const QString &question);

    QString answer() const;
    void setAnswer(const QString &answer);

    bool recorded() const;
    void setRecorded(bool recorded);

signals:
    void questionChanged();
    void answerChanged();
    void recordedChanged();

private:
    QString m_question;
    QString m_answer;
    bool m_recorded;
};

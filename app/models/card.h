// card.h
#pragma once

#include <QObject>
#include <QString>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString answer READ answer WRITE setAnswer NOTIFY answerChanged)
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)

public:
    explicit Card(QObject *parent = nullptr);

    QString question() const;
    void setQuestion(const QString &question);

    QString answer() const;
    void setAnswer(const QString &answer);

    QString imagePath() const;
    void setImagePath(const QString &imagePath);

signals:
    void questionChanged();
    void answerChanged();
    void imagePathChanged();

private:
    QString m_question;
    QString m_answer;
    QString m_imagePath;
};

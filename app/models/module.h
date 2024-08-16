// module.h
#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include "card.h"

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QList<Card*> cards READ cards NOTIFY cardsChanged)

public:
    explicit Module(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

    QList<Card*> cards() const;

    Q_INVOKABLE void addCard(const QString &question, const QString &answer, const QString &imagePath);

signals:
    void nameChanged();
    void colorChanged();
    void cardsChanged();

private:
    QString m_name;
    QString m_color;
    QList<Card*> m_cards;
};

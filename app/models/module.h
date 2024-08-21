#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QSharedPointer>
#include "card.h"

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QList<QSharedPointer<Card>> cards READ cards NOTIFY cardsChanged)

public:
    explicit Module(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

    QList<QSharedPointer<Card>> cards() const;
    void addCard(const QString &question, const QString &answer, const QString &imagePath);

signals:
    void nameChanged();
    void colorChanged();
    void cardsChanged();

private:
    QString m_name;
    QString m_color;
    QList<QSharedPointer<Card>> m_cards;
};

#pragma once

#include <QObject>
#include <QSharedPointer>
#include "CardsModel.h"

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(CardsModel* cardsModel READ cardsModel NOTIFY cardsModelChanged)

public:
    explicit Module(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

    CardsModel* cardsModel() const;

    Q_INVOKABLE void addCard(const QString &question, const QString &answer);

signals:
    void nameChanged();
    void colorChanged();
    void cardsModelChanged();

private:
    QString m_name;
    QString m_color;
    CardsModel* m_cardsModel;
};

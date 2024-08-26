#ifndef CARDSMODEL_H
#define CARDSMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <algorithm>
#include <random>
#include "models/card.h"

class CardsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CardsModel(QObject *parent = nullptr);

    enum CardRoles {
        CardRole = Qt::UserRole + 1,
        QuestionRole,
        AnswerRole
    };

    void addCard(const QSharedPointer<Card> &card);
    void addCards(const QList<QSharedPointer<Card>> &cards);

    Q_INVOKABLE void shuffle();
    Q_INVOKABLE void unshuffle();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QList<QSharedPointer<Card>> cards() const;

protected:
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QList<QSharedPointer<Card>> m_cards;
    QList<int> m_indexMapping;  // Маппинг индексов для перемешивания
};

#endif // CARDSMODEL_H

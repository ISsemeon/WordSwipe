#include "CardsModel.h"

CardsModel::CardsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CardsModel::addCard(const QSharedPointer<Card> &card)
{
    beginInsertRows(QModelIndex(), 0, 0);  // Указываем, что новая строка будет вставлена в начало
    m_cards.prepend(card);  // Добавляем карточку в начало списка
    endInsertRows();
}

int CardsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cards.size();
}

QVariant CardsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_cards.size())
        return QVariant();

    const auto &card = m_cards[index.row()];

    switch (role) {
    case CardRole:
        return QVariant::fromValue(card);
    case QuestionRole:
        return card->question();
    case AnswerRole:
        return card->answer();
    default:
        return QVariant();
    }
}

bool CardsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_cards.size())
        return false;

    auto &card = m_cards[index.row()];

    switch (role) {
    case QuestionRole:
        card->setQuestion(value.toString());
        emit dataChanged(index, index, {QuestionRole});
        return true;
    case AnswerRole:
        card->setAnswer(value.toString());
        emit dataChanged(index, index, {AnswerRole});
        return true;
    default:
        return false;
    }
}

QHash<int, QByteArray> CardsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CardRole] = "card";
    roles[QuestionRole] = "question";
    roles[AnswerRole] = "answer";
    return roles;
}

Qt::ItemFlags CardsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

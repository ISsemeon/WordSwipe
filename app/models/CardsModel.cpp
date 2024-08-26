#include "CardsModel.h"
#include <random>
#include <algorithm>

CardsModel::CardsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CardsModel::addCard(const QSharedPointer<Card> &card)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_cards.prepend(card);
    m_indexMapping.append(m_indexMapping.size());  // Добавляем новый индекс в маппинг
    endInsertRows();
}

void CardsModel::addCards(const QList<QSharedPointer<Card>> &cards)
{
    if (cards.isEmpty()) {
        return;
    }

    beginInsertRows(QModelIndex(), 0, cards.size() - 1);
    for (const auto &card : cards) {
        m_cards.prepend(card);
        m_indexMapping.append(m_indexMapping.size());  // Добавляем индексы для новых карточек
    }
    endInsertRows();
}

void CardsModel::shuffle()
{
    if (m_cards.isEmpty()) return;

    beginResetModel();  // Начинаем сброс модели для перемешивания
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_indexMapping.begin(), m_indexMapping.end(), g);  // Перемешиваем индексы
    endResetModel();  // Заканчиваем сброс модели
}

void CardsModel::unshuffle()
{
    if (m_indexMapping.isEmpty()) return;

    beginResetModel();  // Начинаем сброс модели для возврата исходного состояния
    std::iota(m_indexMapping.begin(), m_indexMapping.end(), 0);  // Возвращаем индексы в исходное состояние
    endResetModel();  // Заканчиваем сброс модели
}

int CardsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cards.size();
}

QVariant CardsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_indexMapping.size())
        return QVariant();

    const auto &card = m_cards[m_indexMapping[index.row()]];  // Используем маппинг для доступа к данным

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
    if (!index.isValid() || index.row() >= m_indexMapping.size())
        return false;

    auto &card = m_cards[m_indexMapping[index.row()]];  // Используем маппинг для доступа к карточке

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

QList<QSharedPointer<Card>> CardsModel::cards() const
{
    return m_cards;
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

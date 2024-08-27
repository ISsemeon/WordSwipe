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
    applyFilter();  // Применяем фильтр после добавления карточки
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
    applyFilter();  // Применяем фильтр после добавления карточек
}

void CardsModel::shuffle()
{
    if (m_cards.isEmpty()) return;

    beginResetModel();  // Начинаем сброс модели для перемешивания
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_indexMapping.begin(), m_indexMapping.end(), g);  // Перемешиваем индексы
    endResetModel();  // Заканчиваем сброс модели
    applyFilter();  // Применяем фильтр после перемешивания
}

void CardsModel::unshuffle()
{
    if (m_indexMapping.isEmpty()) return;

    beginResetModel();  // Начинаем сброс модели для возврата исходного состояния
    std::iota(m_indexMapping.begin(), m_indexMapping.end(), 0);  // Возвращаем индексы в исходное состояние
    endResetModel();  // Заканчиваем сброс модели
    applyFilter();  // Применяем фильтр после возврата индексов
}

int CardsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_filteredIndices.size();  // Количество строк теперь зависит от отфильтрованных индексов
}

QVariant CardsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredIndices.size())
        return QVariant();

    const auto &card = m_cards[m_filteredIndices[index.row()]];  // Используем отфильтрованные индексы для доступа к данным

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
    if (!index.isValid() || index.row() >= m_filteredIndices.size())
        return false;

    auto &card = m_cards[m_filteredIndices[index.row()]];  // Используем отфильтрованные индексы для доступа к карточке

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

void CardsModel::setFilter(const QString &filter)
{
    m_filter = filter;
    applyFilter();  // Применяем фильтр при его изменении
}

void CardsModel::clearFilter()
{
    m_filter.clear();
    applyFilter();  // Применяем сброс фильтра
}

void CardsModel::applyFilter()
{
    beginResetModel();  // Начинаем сброс модели

    m_filteredIndices.clear();  // Очищаем список отфильтрованных индексов

    if (m_filter.isEmpty()) {
        // Если фильтра нет, показываем все карточки
        m_filteredIndices = m_indexMapping;
    } else {
        // Фильтрация на основе вопроса и ответа
        for (int i = 0; i < m_indexMapping.size(); ++i) {
            const auto &card = m_cards[m_indexMapping[i]];

            // Проверяем, начинается ли вопрос или ответ с фильтра
            if (card->question().startsWith(m_filter, Qt::CaseInsensitive) ||
                card->answer().startsWith(m_filter, Qt::CaseInsensitive)) {
                m_filteredIndices.append(m_indexMapping[i]);
            }
        }
    }

    endResetModel();  // Завершаем сброс модели
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

QList<QSharedPointer<Card>> CardsModel::cards() const
{
    return m_cards;
}

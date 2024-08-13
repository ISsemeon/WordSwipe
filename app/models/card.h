#pragma once

#include <QString>

/**
 * @brief Represents a flashcard with a question and answer.
 */
class Card {
public:
    int id;                 // Unique identifier for the card
    QString question;       // Question or text on the card
    QString answer;         // Answer or translation
    QString image;          // Path to the image, if any
};

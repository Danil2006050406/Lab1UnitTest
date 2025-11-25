#pragma once
#include <string>

/**
 * @brief Клас, що представляє одну книгу в бібліотеці.
 *
 * Зберігає основні метадані: назву, автора та ISBN.
 */
class Book {
public:
    /**
     * @brief Створює нову книгу.
     * @param title Назва книги.
     * @param author Автор книги.
     * @param isbn Унікальний ідентифікатор книги (ISBN).
     */
    Book(const std::string& title,
         const std::string& author,
         const std::string& isbn);

    /**
     * @brief Повертає назву книги.
     * @return Рядок із назвою книги.
     */
    std::string getTitle() const;

    /**
     * @brief Повертає автора книги.
     * @return Рядок із ПІБ автора.
     */
    std::string getAuthor() const;

    /**
     * @brief Повертає ISBN книги.
     * @return Рядок із ISBN.
     */
    std::string getIsbn() const;

    /// @brief Порівняння книг за ISBN.
    bool operator==(const Book& other) const;

private:
    std::string title_;
    std::string author_;
    std::string isbn_;
};



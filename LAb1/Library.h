#pragma once

#include "Book.h"
#include "Loan.h"
#include <vector>
#include <string>

/**
 * @brief Проста бібліотека, що зберігає книги та операції з ними.
 *
 * @example
 * @code
 * Library lib;
 * Book book("1984", "George Orwell", "12345");
 * lib.addBook(book);
 * lib.loanBook("12345", "reader-001");
 * lib.returnBook("12345", "reader-001");
 * @endcode
 */
class Library {
public:
    /**
     * @brief Додає нову книгу в бібліотеку.
     * @param book Книга, що додається.
     */
    void addBook(const Book& book);

    /**
     * @brief Видає книгу читачу.
     *
     * @param isbn ISBN книги, яку потрібно видати.
     * @param readerId Ідентифікатор (логін / номер квитка) читача.
     * @return true, якщо видача пройшла успішно, false якщо книги немає.
     *
     * @throws std::runtime_error Якщо немає доступних примірників книги.
     */
    bool loanBook(const std::string& isbn, const std::string& readerId);

    /**
     * @brief Приймає книгу назад від читача.
     * @param isbn ISBN книги.
     * @param readerId Ідентифікатор читача.
     * @return true, якщо повернення успішне, false якщо такого запису не знайдено.
     */
    bool returnBook(const std::string& isbn, const std::string& readerId);

    /**
     * @brief Повертає кількість книг у бібліотеці.
     * @return Ціла кількість книг.
     */
    std::size_t getBooksCount() const;

private:
    std::vector<Book> books_;
    std::vector<Loan> loans_;
};

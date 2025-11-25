<<<<<<< HEAD
﻿#pragma once
#include <string>
#include <ctime>

class Loan {
private:
    std::string loanId, bookIsbn, userId;
    time_t loanDate, dueDate;
    bool returned;
public:
    Loan(const std::string& lid, const std::string& isbn, const std::string& uid,
        time_t loanD, time_t dueD);

    void markReturned();
    bool isReturned() const;
    bool isOverdue() const;
    int daysLeft() const;

    const std::string& getISBN() const;
    const std::string& getUserId() const;
    const std::string& getLoanId() const;
};
=======
#pragma once
#include "Book.h"
#include <string>
#include <optional>

/**
 * @brief Запис про видачу книги читачу.
 *
 * Містить інформацію про книгу, читача та статус повернення.
 */
class Loan {
public:
    /**
     * @brief Створює новий запис про видачу.
     * @param book Книга, яку видають.
     * @param readerId Ідентифікатор читача.
     */
    Loan(const Book& book, const std::string& readerId);

    /**
     * @brief Позначає, що книга повернена.
     *
     * @throws std::logic_error Якщо книга вже була повернена раніше.
     */
    void returnBook();

    /**
     * @brief Перевіряє, чи книга вже повернена.
     * @return true, якщо книга повернена, false інакше.
     */
    bool isReturned() const;

    /**
     * @brief Повертає ідентифікатор читача.
     * @return Рядок із ID читача.
     */
    std::string getReaderId() const;

    /**
     * @brief Повертає видану книгу.
     * @return Константне посилання на книгу.
     */
    const Book& getBook() const;

private:
    Book book_;
    std::string readerId_;
    bool returned_ = false;
};
>>>>>>> 92840df9e87a9a7efd417d6bf0ee0e70cb849c1a

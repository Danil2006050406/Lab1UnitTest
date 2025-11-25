#pragma once
#include <string>

<<<<<<< HEAD
class Book {
private:
    std::string title, author, isbn;
    int year, totalCopies;
public:
    Book(const std::string& t, const std::string& a, const std::string& i, int y, int copies = 1);
    void displayInfo() const;
    bool matchesTitle(const std::string& q) const;
    bool checkout();
    void checkin();
    bool isOldEdition(int thresholdYear = 2000) const;
    bool isAvailable() const;
    const std::string& getISBN() const;
};

class EBook : public Book {
private:
    std::string downloadUrl;
    double fileSizeMB;
public:
    EBook(const std::string& t, const std::string& a, const std::string& i, int y,
        const std::string& url, double size);
    void getDownloadInfo() const;
};
=======
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

>>>>>>> 92840df9e87a9a7efd417d6bf0ee0e70cb849c1a


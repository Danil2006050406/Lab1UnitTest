# Lab1UnitTest

## Призначення програми
Проєкт **Lab1UnitTest** реалізує базову систему керування бібліотекою.  
Програма дозволяє додавати книги, видавати їх читачам, повертати після користування, а також контролювати кількість доступних примірників.  
Основна мета — відпрацювати принципи об’єктно-орієнтованого програмування (класи, спадкування, інкапсуляція) та ознайомитися з базовими підходами до юніт-тестування.

---

##  Структура проєкту

---

## Тестування
Тестування реалізовано у гілці [`feature/unit-tests`](https://github.com/Danil2006050406/Lab1UnitTest/tree/feature/unit-tests).  
У проєкті використовується **Google Test Framework** для перевірки основних методів класів:

- `Library::addBook()`  
- `Library::loanBook()`  
- `Loan::returnBook()`  

### Приклад тесту:
```cpp
TEST(LibraryTest, AddBookIncreasesCount) {
    Library lib;
    Book b("1984", "George Orwell", "12345");
    lib.addBook(b);
    EXPECT_EQ(lib.getBooksCount(), 1);
}
У ході роботи над лабораторною студент відпрацював базові команди:

git init
git add .
git commit -m "Initial project version"
git branch feature/unit-tests
git checkout feature/unit-tests
git push -u origin feature/unit-tests
git merge feature/unit-tests
Сахно Данило
Студент групи ІПС-21,
Київський національний університет імені Тараса Шевченка, 2025 рік.

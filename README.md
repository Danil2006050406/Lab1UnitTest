# Lab1UnitTest
##  Автор
Сахно Данило
Студент групи ІПС-21,
Київський національний університет імені Тараса Шевченка, 2025 рік.

---

## Призначення програми
Проєкт **Lab1UnitTest** реалізує базову систему керування бібліотекою.  
Програма дозволяє додавати книги, видавати їх читачам, повертати після користування, а також контролювати кількість доступних примірників.  
Основна мета — відпрацювати принципи об’єктно-орієнтованого програмування (класи, спадкування, інкапсуляція) та ознайомитися з базовими підходами до юніт-тестування.

---

##  Структура проєкту
Lab1UnitTest/
├── src/ # Вихідні файли (реалізація класів)
│ ├── Book.cpp
│ ├── Loan.cpp
│ ├── Library.cpp
│ └── ...
├── include/ # Заголовкові файли (*.h / *.hpp)
│ ├── Book.h
│ ├── Loan.h
│ ├── Library.h
│ └── ...
├── tests/ # Тести (Google Test або власні)
│ ├── LibraryTests.cpp
│ └── LoanTests.cpp
├── CMakeLists.txt # Конфігурація збірки
└── README.md # Опис проєкту

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
* * *
## Documentation

Автоматично згенеровану документацію до проєкту можна переглянути за посиланням (GitHub Pages):

> https://danil2006050406.github.io/Lab1UnitTest/

Документація створюється з коментарів у форматі Doxygen під час CI-пайплайну GitHub Actions (workflow `docs.yml`).

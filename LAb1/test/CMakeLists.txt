# Цей файл знаходиться в tests/CMakeLists.txt

# Створюємо окремий виконуваний файл для тестів
# (Використовуємо tests.cpp, як у оригінальному проекті)
add_executable(library_tests tests.cpp)

# Лінкуємо наш тестовий .exe з трьома речами:
# 1. Lab1Core - щоб тести мали доступ до класів Book, Library тощо.
# 2. GTest::gtest / GTest::gmock - бібліотеки GTest, які ми завантажили.
target_link_libraries(library_tests
        PRIVATE
        Lab1Core
        GTest::gtest
        GTest::gtest_main
)

# Реєструємо наш 'library_tests.exe' в CTest під іменем "LibraryTests"
# Ми використовуємо add_test(), оскільки tests.cpp має власний main()
gtest_discover_tests(library_tests)
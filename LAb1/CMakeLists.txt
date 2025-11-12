# Встановлюємо мінімальну версію CMake
cmake_minimum_required(VERSION 3.16)
# Назва проекту (з твого оригінального файлу)
project(LibrarySystem CXX)

# Встановлюємо стандарт C++17 (як було в оригінальному файлі)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Правильне налаштування бібліотек часу виконання для Visual Studio
if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# --- GTest (Google Test) ---
# Використовуємо FetchContent для автоматичного завантаження GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
# Налаштування для GTest
set(GTEST_DONT_DEFINE_TEST_MACRO_BY_DEFAULT ON)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Вмикаємо систему тестування CTest
enable_testing()

# --- Основна бібліотека ---
# Визначаємо Lab1Core як STATIC бібліотеку з усіма її .cpp файлами
# (Це виправлення порівняно з INTERFACE з твого прикладу)
add_library(Lab1Core STATIC
        Book.cpp
        Loan.cpp
        User.cpp
        Library.cpp
        LibraryUtils.cpp
)
# Вказуємо, що заголовні файли лежать у корені проекту
target_include_directories(Lab1Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- Основний додаток ---
# Створюємо виконуваний файл Lab1App з LAb1.cpp
add_executable(Lab1App LAb1.cpp)
# Лінкуємо (підключаємо) Lab1App з нашою бібліотекою Lab1Core
target_link_libraries(Lab1App PRIVATE Lab1Core)

# --- Тести ---
# Додаємо підкаталог 'tests', який містить свій власний CMakeLists.txt
add_subdirectory(test)
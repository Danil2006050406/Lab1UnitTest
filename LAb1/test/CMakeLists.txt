add_executable(library_tests tests.cpp)

target_link_libraries(library_tests
        PRIVATE
        Lab1Core
        GTest::gtest
        GTest::gtest_main
)

gtest_discover_tests(library_tests)
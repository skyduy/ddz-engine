find_package(GTest CONFIG REQUIRED)

add_executable(testRule testRule.cpp)
target_link_libraries(testRule GTest::gtest_main ddz::card)

add_test(test_all testRule)

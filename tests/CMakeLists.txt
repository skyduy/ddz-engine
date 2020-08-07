find_package(GTest CONFIG REQUIRED)

add_executable(rule_test "rule_test.cpp")
target_link_libraries(rule_test GTest::gtest_main ddz::rule)

add_test(test_all rule_test)

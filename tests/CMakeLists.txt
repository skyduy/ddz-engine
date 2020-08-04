find_package(GTest CONFIG REQUIRED)

add_executable(testCore testCore.cpp)
target_link_libraries(testCore GTest::gtest_main DDZ_CORE)

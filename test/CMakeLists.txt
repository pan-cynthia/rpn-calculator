find_package(GTest REQUIRED)

set(TEST_FILES tests.cpp runTests.cpp)
add_executable(runTests ${TEST_FILES})

target_include_directories(runTests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(runTests PRIVATE rpn_lib GTest::gtest GTest::gtest_main)

target_compile_options(runTests PRIVATE -Wall -Werror)

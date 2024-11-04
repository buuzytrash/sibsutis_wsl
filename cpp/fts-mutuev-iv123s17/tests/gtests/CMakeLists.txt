enable_testing()
add_executable(
    addition_test
)

include(GoogleTest)
include(CompileOptions)
set_compile_options(addition_test)

target_sources(
    addition_test
    PRIVATE
    gtest_addition.test.cpp
)

target_link_libraries(
    addition_test
    PRIVATE
    GTest::gtest_main
    libmath
)

gtest_discover_tests(addition_test)

add_executable(
    parse_test
)

set_compile_options(parse_test)

target_sources(
    parse_test
    PRIVATE
    gtest_parse.test.cpp
)

target_link_libraries(
    parse_test
    PRIVATE
    GTest::gtest_main
    libparse
    pugixml
)

gtest_discover_tests(parse_test)
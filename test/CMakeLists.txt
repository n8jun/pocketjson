add_subdirectory(googletest)
include_directories(
    SYSTEM
    ../include
    googletest/include
)
set(TEST_LIBS gtest gtest_main pthread)
set(TEST_SOURCES
    parse_null.cc
    parse_boolean.cc
    parse_number.cc
    parse_string.cc
    parse_array.cc
    parse_object.cc
    serialize_null.cc
    serialize_boolean.cc
    serialize_number.cc
    serialize_string.cc
    serialize_array.cc
    serialize_object.cc
)

add_executable(unittest ${TEST_SOURCES})
target_link_libraries(unittest ${TEST_LIBS})

add_dependencies(unittest gtest gtest_main)

add_test(NAME unittest COMMAND unittest)


add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(WordFrequencyTest test.cc main.cc)

target_link_libraries(WordFrequencyTest WordFrequency gtest_main)

add_test(NAME WordFrequencyTest COMMAND WordFrequencyTest)


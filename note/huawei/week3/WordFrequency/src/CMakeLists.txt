
set(headers ${CMAKE_SOURCE_DIR}/include)


add_library(WordFrequency word_frequency.c input.c list.c)
target_include_directories(WordFrequency  PUBLIC "${headers}")

add_executable(WordFrequencyExe main.c)

target_link_libraries(WordFrequencyExe WordFrequency)


cmake_minimum_required(VERSION 3.27)
project(Transazioni_finanziarie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Transazioni_finanziarie
        main.cpp
        Client.cpp
        CC.cpp
        Client.h
        CC.h
)

add_subdirectory(Tests/lib/googletest-main)
include_directories(Tests/lib/googletest-main/googletest/include)

add_executable(Transazioni_finanziarie_tests
        Client.cpp
        CC.cpp
        Client.h
        CC.h
        Tests/Client_Test.cpp
        Tests/CC_Test.cpp
)

target_include_directories(Transazioni_finanziarie_tests PRIVATE "${CMAKE_SOURCE_DIR}")

enable_testing()
add_test(NAME Transazioni_finanziarie_tests COMMAND Transazioni_finanziarie_tests)
target_link_libraries(Transazioni_finanziarie_tests gtest gtest_main pthread)

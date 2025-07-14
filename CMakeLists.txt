cmake_minimum_required(VERSION 3.27)
project(Transazioni_finanziarie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Transazioni_finanziarie
        main.cpp
        Cliente.cpp
        CC.cpp
        Cliente.h
        CC.h
        Banca.cpp
        Banca.h
)

add_subdirectory(Tests/lib/googletest-main)
include_directories(Tests/lib/googletest-main/googletest/include)

add_executable(Transazioni_finanziarie_tests
        Cliente.cpp
        CC.cpp
        Cliente.h
        CC.h
        Banca.h
        Banca.cpp
        Tests/CC_Test.cpp
        Tests/Cliente_Test.cpp
        Tests/Banca_Test.cpp
)

target_include_directories(Transazioni_finanziarie_tests PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(Transazioni_finanziarie_tests gtest gtest_main pthread)

enable_testing()
add_test(NAME Transazioni_finanziarie_tests COMMAND Transazioni_finanziarie_tests)
cmake_minimum_required(VERSION 3.27)
project(Transazioni_finanziarie)

set(CMAKE_CXX_STANDARD 17)

# Main project executable
add_executable(Transazioni_finanziarie
        main.cpp
        Client.cpp
        CC.cpp
        Client.h
        CC.h
)
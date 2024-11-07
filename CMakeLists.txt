cmake_minimum_required(VERSION 3.28)
project(TestWork)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestWork 1.1.cpp
        1.2.cpp
        2.1.cpp
        3.1.cpp
        4.1.cpp
        4.2.cpp
        5.cpp
        6.cpp
        7.cpp
        8.1.cpp
        "8.2(include).cpp"
        8.2.cpp
        9.1.cpp
        9.2.cpp
        10.1.cpp
        10.2.cpp
        "10.2(no filecode).cpp"
)

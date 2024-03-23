cmake_minimum_required(VERSION 3.26)
project(P1)

set(CMAKE_CXX_STANDARD 17)

add_executable(P1 p1.cpp
        MemberList.cpp
        BookList.cpp
        RatingList.cpp
)

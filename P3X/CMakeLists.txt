cmake_minimum_required(VERSION 3.26)
project(P3X)

set(CMAKE_CXX_STANDARD 17)

add_executable(P3X p3x.cpp
        PatientPriorityQueuex.h
        Patient.h)

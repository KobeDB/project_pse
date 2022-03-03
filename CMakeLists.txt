cmake_minimum_required(VERSION 3.21)
project(project_pse)

set(CMAKE_CXX_STANDARD 98)

add_executable( project_pse main.cpp
        tinystr.cpp
        tinyxmlerror.cpp
        tinystr.h
        tinyxml.h
        tinyxml.cpp
        tinyxmlparser.cpp
        )

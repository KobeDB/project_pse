cmake_minimum_required(VERSION 3.21)
project(project_pse)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/main.cpp
        src/tinystr.cpp
        src/tinyxmlerror.cpp
        src/tinystr.h
        src/tinyxml.h
        src/tinyxml.cpp
        src/tinyxmlparser.cpp
        src/Baan.cpp
        src/Baan.h
        src/Verkeerslicht.cpp
        src/Verkeerslicht.h
        src/Verkeerssimulatie.cpp
        src/Verkeerssimulatie.h
        src/Voertuig.cpp
        src/Voertuig.h src/VerkeerssituatieReader.cpp src/VerkeerssituatieReader.h
        src/TicTacToeUtils.cpp
        src/TicTacToeUtils.h
        )

# Set source files for RELEASE target
set(DEBUG_SOURCE_FILES
        src/VerkeerssimulatieTests.cpp
        src/tinystr.cpp
        src/tinyxmlerror.cpp
        src/tinystr.h
        src/tinyxml.h
        src/tinyxml.cpp
        src/tinyxmlparser.cpp
        src/Baan.cpp
        src/Baan.h
        src/Verkeerslicht.cpp
        src/Verkeerslicht.h
        src/Verkeerssimulatie.cpp
        src/Verkeerssimulatie.h
        src/Voertuig.cpp
        src/Voertuig.h
        src/VerkeerssituatieReader.cpp src/VerkeerssituatieReader.h
        src/TicTacToeUtils.cpp
        src/TicTacToeUtils.h
        )

# Create RELEASE target
add_executable(project_pse ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(project_pse_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(project_pse_debug gtest)
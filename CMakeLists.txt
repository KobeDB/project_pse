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
        src/tinyxml/tinystr.cpp
        src/tinyxml/tinyxmlerror.cpp
        src/tinyxml/tinystr.h
        src/tinyxml/tinyxml.h
        src/tinyxml/tinyxml.cpp
        src/tinyxml/tinyxmlparser.cpp
        src/Baan.cpp
        src/Baan.h
        src/Verkeerslicht.cpp
        src/Verkeerslicht.h
        src/Verkeerssimulatie.cpp
        src/Verkeerssimulatie.h
        src/voertuigen/Voertuig.cpp
        src/voertuigen/Voertuig.h src/VerkeerssituatieReader.cpp src/VerkeerssituatieReader.h
        src/test_utils/TicTacToeUtils.cpp
        src/test_utils/TicTacToeUtils.h
        src/Prioriteitsvoertuig.cpp src/Prioriteitsvoertuig.h src/voertuigen/Auto.cpp src/voertuigen/Auto.h src/VoertuigFactory.cpp src/VoertuigFactory.h src/voertuigen/Brandweerwagen.cpp src/voertuigen/Brandweerwagen.h src/voertuigen/Politiecombi.cpp src/voertuigen/Politiecombi.h src/voertuigen/Ziekenwagen.cpp src/voertuigen/Ziekenwagen.h src/voertuigen/Bus.cpp src/voertuigen/Bus.h src/Voertuig_generator.cpp src/Voertuig_generator.h)

# Set source files for RELEASE target
set(DEBUG_SOURCE_FILES
        src/VerkeerssimulatieTests.cpp
        src/tinyxml/tinystr.cpp
        src/tinyxml/tinyxmlerror.cpp
        src/tinyxml/tinystr.h
        src/tinyxml/tinyxml.h
        src/tinyxml/tinyxml.cpp
        src/tinyxml/tinyxmlparser.cpp
        src/Baan.cpp
        src/Baan.h
        src/Verkeerslicht.cpp
        src/Verkeerslicht.h
        src/Verkeerssimulatie.cpp
        src/Verkeerssimulatie.h
        src/voertuigen/Voertuig.cpp
        src/voertuigen/Voertuig.h
        src/VerkeerssituatieReader.cpp src/VerkeerssituatieReader.h
        src/test_utils/TicTacToeUtils.cpp
        src/test_utils/TicTacToeUtils.h
        src/VoertuigTests.cpp src/VerkeerslichtTests.cpp src/BaanTests.cpp src/Prioriteitsvoertuig.cpp src/Prioriteitsvoertuig.h src/voertuigen/Auto.cpp src/voertuigen/Auto.h src/VoertuigFactory.cpp src/VoertuigFactory.h src/voertuigen/Brandweerwagen.cpp src/voertuigen/Brandweerwagen.h src/voertuigen/Bus.cpp src/voertuigen/Bus.h src/voertuigen/Politiecombi.cpp src/voertuigen/Politiecombi.h src/voertuigen/Ziekenwagen.cpp src/voertuigen/Ziekenwagen.h src/Voertuig_generator.cpp src/Voertuig_generator.h src/VerkeerssimulatieOutputTests.cpp src/VoertuigFactoryTests.cpp src/Voertuig_generatorTests.cpp src/OurTestingUtils.cpp src/OurTestingUtils.h)

# Create RELEASE target
add_executable(project_pse ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(project_pse_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(project_pse_debug gtest)
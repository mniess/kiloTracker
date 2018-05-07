cmake_minimum_required(VERSION 3.1.0)
project(KiloTracker)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)

# Find dependencies
find_package(OpenCV REQUIRED)

# Source files
SET(KILOTRACKER_SRC
        ${RESOURCE_FILE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Gui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Settings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Detector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Tracer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Cli.cpp)

# Build
ADD_EXECUTABLE(KiloTracker ${KILOTRACKER_SRC})
target_link_libraries(KiloTracker ${OpenCV_LIBS})


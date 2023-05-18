cmake_minimum_required(VERSION 3.23)
project (bejeveled)

find_package(OpenCV CONFIG REQUIRED)

set(GAME_FILES 
    src/Pattern.hpp
    src/Pattern.cpp
    src/Solver.hpp
    src/Solver.cpp
    src/Window.hpp
    src/Window.cpp
    src/main.cpp
)

add_executable(bejeveled ${GAME_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})
target_link_libraries(bejeveled ${OpenCV_LIBS})
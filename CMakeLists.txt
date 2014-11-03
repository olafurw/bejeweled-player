cmake_minimum_required (VERSION 2.8.11)
project (bejeveled)

# OpenCV
set(OPENCV_INCLUDE_DIR "libraries/opencv/include/")
set(OPENCV_LIBRARY_DIR "libraries/opencv/x86/vc11/lib/")
set(OPENCV_DLL_DIR "libraries/opencv/x86/vc11/bin/")
set(OPENCV_LIBRARY "opencv_core2410" "opencv_highgui2410")

set(INCLUDE_DIRS ${OPENCV_INCLUDE_DIR})
set(LINK_DIRS ${OPENCV_LIBRARY_DIR})
set(LIBRARIES ${OPENCV_LIBRARY})

include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})

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
target_link_libraries(bejeveled ${LIBRARIES})

add_custom_command(TARGET bejeveled POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${OPENCV_DLL_DIR}opencv_core2410.dll ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
add_custom_command(TARGET bejeveled POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${OPENCV_DLL_DIR}opencv_highgui2410.dll ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
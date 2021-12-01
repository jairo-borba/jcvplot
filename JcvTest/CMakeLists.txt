cmake_minimum_required(VERSION 3.20)
project(JcvTest)

set(CMAKE_CXX_STANDARD 14)
set(JcvPlotLib ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/libjcvplot.a)
set(JcvPlotInc ${CMAKE_CURRENT_SOURCE_DIR}/../srclib/include)
find_package(OpenCV)

link_libraries(${JcvPlotLib})
include_directories(${OpenCV_INCLUDE_DIRS} ${JcvPlotInc})

add_executable(JcvTest main.cpp)
target_link_libraries(JcvTest ${OpenCV_LIBS})
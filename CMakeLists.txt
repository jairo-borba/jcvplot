cmake_minimum_required(VERSION 3.20)
project(jcvplot)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
add_library(jcvplot library.cpp ID.h Figure.cpp Figure.h Form.cpp Form.h XAxis.cpp XAxis.h Window.cpp Window.h Series.cpp Series.h Line.cpp Line.h YAxis.cpp YAxis.h Axis.cpp Axis.h Border.cpp Border.h Ruler.cpp Ruler.h Stem.cpp Stem.h Tensor.cpp Tensor.h Transform2D.cpp Transform2D.h AxisAngle.h)
target_link_libraries(jcvplot ${OpenCV_LIBS})
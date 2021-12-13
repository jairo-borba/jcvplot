cmake_minimum_required(VERSION 3.20)
project(jcvplot)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV)

set(JcvPlotLib ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/libjcvplot.a)
set(JcvPlotInc ${CMAKE_CURRENT_SOURCE_DIR}/../srclib/include)

include_directories(${OpenCV_INCLUDE_DIRS} srclib/include/jcvplot)
add_library(jcvplot srclib/cpp/library.cpp srclib/include/jcvplot/ID.h srclib/cpp/Figure.cpp srclib/include/jcvplot/Figure.h srclib/cpp/Form.cpp srclib/include/jcvplot/Form.h srclib/cpp/XAxis.cpp srclib/include/jcvplot/XAxis.h srclib/cpp/Window.cpp srclib/include/jcvplot/Window.h srclib/cpp/Series.cpp srclib/include/jcvplot/Series.h srclib/cpp/Line.cpp srclib/include/jcvplot/Line.h srclib/cpp/YAxis.cpp srclib/include/jcvplot/YAxis.h srclib/cpp/Border.cpp srclib/include/jcvplot/Border.h srclib/cpp/Ruler.cpp srclib/include/jcvplot/Ruler.h srclib/cpp/Stem.cpp srclib/include/jcvplot/Stem.h srclib/cpp/Tensor.cpp srclib/include/jcvplot/Tensor.h srclib/cpp/Transform2D.cpp srclib/include/jcvplot/Transform2D.h srclib/include/jcvplot/AxisAngle.h srclib/cpp/Transform3D.cpp srclib/include/jcvplot/Transform3D.h srclib/cpp/MovingX.cpp srclib/include/jcvplot/MovingX.h)
target_link_libraries(jcvplot ${OpenCV_LIBS})

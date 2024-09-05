# CMakeList.txt: panorama 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


project ("panorama")


cmake_minimum_required(VERSION 2.8)


set(OpenCV_DIR E:/opencv/build)
FIND_PACKAGE(OpenCV REQUIRED)
if(OpenCV_FOUND)
	message(STUTUS "THE OPENCV LIB IS FOUND!")
endif()
include_directories(${OpenCV_INCLUDE_DIR})
link_directories(${OpenCV_LIBRARY_DIRS})
# 将源代码添加到此项目的可执行文件。
add_executable (panorama "panorama.cpp" "panorama.h")
add_executable(img_stiched "img_stiched")
target_link_libraries(panorama ${OpenCV_LIBS})
target_link_libraries(img_stiched ${OpenCV_LIBS})
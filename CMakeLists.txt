cmake_minimum_required(VERSION 2.8)
PROJECT(progress)
set(CMAKE_BUILD_TYPE "Release")

# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

set( CMAKE_BUILD_TYPE Debug  )
# 寻找OpenCV库
find_package(OpenCV REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})

# pcl 
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})


#添加一个可执行程序
add_executable(sgbm sgbm.cpp)
target_link_libraries(sgbm ${OpenCV_LIBS})

#添加一个可执行程序
add_executable(dis2dep dis2dep.cpp)
target_link_libraries(dis2dep ${OpenCV_LIBS})

#添加一个可执行程序
add_executable(dep2pcl dep2pcl.cpp)
target_link_libraries(dep2pcl ${OpenCV_LIBS} ${PCL_LIBRARIES})

#添加一个可执行程序
add_executable(img2dis img2dis.cpp)
target_link_libraries(img2dis ${OpenCV_LIBS})


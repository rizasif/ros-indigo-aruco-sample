cmake_minimum_required(VERSION 2.8.3)
project(aruco_test)

SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )

find_package(catkin REQUIRED
             roscpp
             roslib
             cv_bridge)
find_package(aruco REQUIRED )
include_directories(include ${aruco_INCLUDE_DIR})
link_libraries(${aruco_LIBRARIES})
find_package(OpenCV REQUIRED)
include_directories(include ${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBRARIES})

catkin_package(
  #include
  #LIBRARIES aruco
  LIBRARIES ${PROJECT_NAME}
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(test1 test1_node.cpp)
target_link_libraries(test1  ${catkin_LIBRARIES})

add_executable(test2 test2_node.cpp)
target_link_libraries(test2  ${catkin_LIBRARIES})

#add_executable(aruco_simple aruco_simple.cpp)
#target_link_libraries(aruco_simple  ${aruco_LIBS})


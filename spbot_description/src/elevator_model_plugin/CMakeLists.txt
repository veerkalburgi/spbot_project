cmake_minimum_required(VERSION 2.8.3)
project(elevator_plugin)

find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS
roscpp
gazebo_ros
std_msgs
)
#Depend on system install of gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
add_library(elevator_plugin src/ElevatorPlugin.cc)
target_link_libraries(elevator_plugin ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
catkin_package(
  DEPENDS
    roscpp
    gazebo_ros
    std_msgs
)

# Build the stand-alone test program
add_executable(button src/button.cc)

if (${gazebo_VERSION_MAJOR} LESS 6)
  # These two
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(button ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(button ${GAZEBO_LIBRARIES})
endif()

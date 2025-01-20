cmake_minimum_required(VERSION 3.14)
project(bt_drone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(behaviortree_cpp REQUIRED)

add_library(waypoint_gen_lib src/waypoint_gen.cpp)

target_include_directories(waypoint_gen_lib PUBLIC include)

enable_testing()

add_executable(
  wp_test
  tests/wp_test.cpp
)

target_link_libraries(wp_test
  waypoint_gen_lib
)

target_link_libraries(
  wp_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(wp_test)

# include_directories(${GTEST_INCLUDE_DIRS})

ament_target_dependencies(waypoint_gen_lib 
  rclcpp
  geometry_msgs
  tf2
)

ament_target_dependencies(wp_test
  rclcpp
  geometry_msgs
  behaviortree_cpp
  tf2
)


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  #[[
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME} tests/wp_test.cpp)
  target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  ament_target_dependencies(waypoint_gen_lib 
    rclcpp
    geometry_msgs
    tf2
  )

  ament_target_dependencies(wp_test
    rclcpp
    geometry_msgs
    behaviortree_cpp
  )
  ]]

endif()

ament_package()

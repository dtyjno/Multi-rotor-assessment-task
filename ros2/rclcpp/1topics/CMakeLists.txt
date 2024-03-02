cmake_minimum_required(VERSION 3.8)
project(cpp_simtop)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
add_executable(talker src/publisher_lambda_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
add_executable(listener src/subscriber_lambda_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
add_executable(node_01 src/1node_1.cpp)
ament_target_dependencies(node_01 rclcpp)
add_executable(node_02 src/2not_composable.cpp)
ament_target_dependencies(node_02 rclcpp std_msgs)
add_executable(node_03 src/3member_function.cpp)
ament_target_dependencies(node_03 rclcpp std_msgs)
add_executable(node_04 src/4not_composable.cpp)
ament_target_dependencies(node_04 rclcpp std_msgs)
add_executable(node_05 src/5lambda.cpp)
ament_target_dependencies(node_05 rclcpp std_msgs)
install(TARGETS
  talker
  listener
  node_01
  node_02
  node_03
  node_04
  node_05
  DESTINATION lib/${PROJECT_NAME}
)

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
endif()

ament_package()

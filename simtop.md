```sh
#引入底层ros2环境
source /opt/ros/humble/setup.bash
#创建工作空间
mkdir -p ~/simtop/src
cd ~/simtop/src/
#创建软件包
ros2 pkg create --build-type ament_cmake --license Apache-2.0 cpp_simtop
cd cpp_simtop
cd src
#写入发布者节点，通过输入以下命令下载示例代码：
#wget -O publisher_lambda_function.cpp https://raw.githubusercontent.com/ros2/examples/rolling/rclcpp/topics/minimal_publisher/lambda.cpp
code /publisher_lambda_function.cpp
#写入订阅节点
#wget -O subscriber_lambda_function.cpp https://raw.githubusercontent.com/ros2/examples/rolling/rclcpp/topics/minimal_subscriber/lambda.cpp
code /subscriber_lambda_function.cpp
cd ..
code CMakeLists.txt 
code package.xml 

#rosdep查找依赖项
cd ~/simtop
rosdep install -i --from-path src --rosdistro humble -y
#colcon构建
colcon build --packages-select cpp_simtop

#   打开新终端
#进入工作区的根目录：
cd ~/simtop
#在根目录中，获取覆盖层：
source install/local_setup.bash #或   
#. install/setup.bash
ros2 run cpp_simtop talker

#   打开新终端
#进入工作区的根目录：
cd ~/simtop
#在根目录中，获取覆盖层：
source install/local_setup.bash #或   
#. install/setup.bash
ros2 run cpp_simtop listener
```
<description>Examples of minimal publisher/subscriber using rclcpp</description>
<maintainer email="you@email.com">Your Name</maintainer>
<license>Apache License 2.0</license>

<depend>rclcpp</depend>
<depend>std_msgs</depend>

find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/publisher_lambda_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

add_executable(listener src/subscriber_lambda_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

publisher_lambda_function.cpp
```cpp

```

subscriber_lambda_function.cpp
```cpp

```

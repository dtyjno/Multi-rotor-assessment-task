#include <chrono>//处理时间
#include <string>//字符串操作

#include "rclcpp/rclcpp.hpp"//ROS2的主要库
#include "std_msgs/msg/string.hpp"//ROS2的标准消息类型之一

using namespace std::chrono_literals;//使用便捷的时间字面量

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);//初始化rclcpp
  auto node=std::make_shared<rclcpp::Node>("node");//创建node节点
  auto publisher=node->create_publisher<std_msgs::msg::String>("topic" , 10);//创建一个发布者，发布者使用 `String` 消息类型，主题名称 `topic`，以及在发生备份时限制消息所需的队列大小为 10 。
  std_msgs::msg::String message;//创建一个 `String` 消息
  auto publish_count=0;
  rclcpp::WallRate looprate(500ms);//创建一个循环速率，以保持500毫秒的循环速率
  while(rclcpp::ok()){//当节点还在运行时
    message.data="Hello,world!"+std::to_string(publish_count++);//更新消息的内容
    RCLCPP_INFO(node->get_logger(),"%s",message.data.c_str());//打印一句话,c_str()取址
    try {
      publisher->publish(message);//尝试使用`publisher->publish(message);`来发布一个消息。
      rclcpp::spin_some(node);//创建一个默认的单线程执行程序，并执行任何立即可用的工作。 
    } catch (const rclcpp::exceptions::RCLError & e) {//捕获类型的异常。这是ROS2中所有运行时错误的基类。
      RCLCPP_ERROR(//使用RCLCPP_ERROR宏来记录一个错误日志。
        node->get_logger(),
        "unexpectedly failed with %s",
        e.what());//e.what()是std::exception类的一个成员函数，它返回一个描述异常的字符串。
    }
    looprate.sleep();//让循环速率休眠一段时间，以保持500毫秒的循环速率
  }
  rclcpp::shutdown();//关闭节点
  return 0;
}

//source ~/simtop/install/local_setup.bash 
//ros2 run cpp_simtop node_02

/*这段代码是一个简单的ROS2（Robot Operating System 2）发布者节点的实现，
  但是它并不推荐使用，因为它不支持在同一个可执行文件中组合多个节点。这个例子
  只是为了完整性而包含，因为它类似于“经典”的独立ROS节点。

首先，我们包含了必要的头文件，包括`<chrono>`，`<string>`，`"rclcpp/rclcpp.hpp"`和`"std_msgs/msg/string.hpp"`。其中，`<chrono>`用于处理时间，`<string>`用于字符串操作，`"rclcpp/rclcpp.hpp"`是ROS2的主要库，`"std_msgs/msg/string.hpp"`是ROS2的标准消息类型之一。

然后，我们使用`std::chrono_literals`命名空间，这样我们就可以使用便捷的时间字面量，如`500ms`。

在`main`函数中，我们初始化ROS2，创建一个名为"minimal_publisher"的节点
，并创建一个发布者，用于发布`std_msgs::msg::String`类型的消息到"topic"
主题。我们还创建了一个`std_msgs::msg::String`消息和一个发布计数器，以及
一个每500毫秒触发一次的循环速率。

在主循环中，只要ROS2节点还在运行，我们就会更新消息的内容，将其设置为
"Hello, world!"加上一个递增的计数器，然后尝试发布这个消息。我们使用
`rclcpp::spin_some`函数处理一些待处理的ROS2事件。如果在发布消息时
发生错误，我们会捕获`rclcpp::exceptions::RCLError`异常，并记录一
个错误日志。每次循环结束后，我们都会让循环速率休眠一段时间，以保持500毫秒
的循环速率。

最后，当主循环结束后，我们关闭ROS2并退出程序。*/
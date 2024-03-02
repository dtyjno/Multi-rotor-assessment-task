

#include "rclcpp/rclcpp.hpp"
#include"std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc ,char * argv[]){
    rclcpp::init(argc,argv);
    auto node=rclcpp::Node::make_shared("node04");
    auto sub=node->create_subscription<std_msgs::msg::String>(
        "topic04",10,
        [](const std_msgs::msg::String::SharedPtr msg){
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "I heard: '%s'", msg->data.c_str());
        }
    );
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

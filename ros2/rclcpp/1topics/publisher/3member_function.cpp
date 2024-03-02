#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Minimalpublisher : public rclcpp::Node
{
public:
    Minimalpublisher():Node("node03"),count(0)//构造函数中的初始化列表
    {
        publisher_=this->create_publisher<std_msgs::msg::String>("topic03",10);
        timer_=this->create_wall_timer(
            500ms,std::bind(&Minimalpublisher::timer_callback,this));
        /*auto timer_callback =[this]() -> void {
            auto message = std_msgs::msg::String();
            message.data = "Hello, world! " + std::to_string(this->count_++);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(500ms, timer_callback);*/
    }
private:
    void timer_callback()
    {
        std_msgs::msg::String message;
        message.data="Hello,world!"+std::to_string(count++);
        RCLCPP_INFO(this->get_logger(),"Publishing: '%s'",message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count;
};


int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Minimalpublisher>()); // Change MinimalPublisher to Minimalpublisher
    rclcpp::shutdown();
}

//source ~/simtop/install/local_setup.bash 
//ros2 run cpp_simtop node_03
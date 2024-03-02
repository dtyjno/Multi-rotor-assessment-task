#include "rclcpp/rclcpp.hpp"

int main(int argc ,char * argv[]){
    rclcpp::init(argc, argv);//初始化rclcpp
    auto node=std::make_shared<rclcpp::Node>("Node_01");//产生一个Node_1节点
    RCLCPP_INFO(node->get_logger(),"Node_01节点已经启动.");//打印一句话
    rclcpp::spin(node);//运行节点，并检测退出信号 Ctrl+C
    rclcpp::shutdown();//关闭节点
    return 0;
}

//ros2 run cpp_simtop node_01 

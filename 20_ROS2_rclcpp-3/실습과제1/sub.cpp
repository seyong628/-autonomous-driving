#include "rclcpp/rclcpp.hpp"//헤더파일
#include "std_msgs/msg/string.hpp"//헤더파일
#include <memory>//헤더파일
#include <functional>//헤더파일
void mysub_callback(rclcpp::Node::SharedPtr node, const
std_msgs::msg::String::SharedPtr msg)//mysub_callback
{
    RCLCPP_INFO(node->get_logger(), "Received message: %s", msg->data.c_str());//출력
}
int main(int argc, char* argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS2초기화
    auto node = std::make_shared<rclcpp::Node>("node_sub1");//node
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS
    std::function<void(const std_msgs::msg::String::SharedPtr)> fn =
    std::bind(mysub_callback, node, std::placeholders::_1);//bind
    auto mysub = node->create_subscription<std_msgs::msg::String>("topic_pub1",qos_profile,fn);//sub
    rclcpp::spin(node);//spin
    rclcpp::shutdown();//shutdown
    return 0;//0을반환하고 함수 종료
}
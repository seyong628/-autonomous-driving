#include "rclcpp/rclcpp.hpp"    //헤더파일
#include "std_msgs/msg/int32.hpp"//헤더파일
#include <memory>//헤더파일
#include <functional>//헤더파일
void mysub_callback(rclcpp::Node::SharedPtr node, const
std_msgs::msg::Int32::SharedPtr msg)//mysub_callback함수
{
    RCLCPP_INFO(node->get_logger(), "Received message: %d", msg->data);//출력
}
int main(int argc, char* argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS2 초기화
    auto node = std::make_shared<rclcpp::Node>("node_sub1");//node선언
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS선언
    std::function<void(const std_msgs::msg::Int32::SharedPtr)> fn =
    std::bind(mysub_callback, node, std::placeholders::_1);//bind
    auto mysub = node->create_subscription<std_msgs::msg::Int32>("topic_pub1",qos_profile,fn);//sub
    rclcpp::spin(node);//spin
    rclcpp::shutdown();//shutdown
    return 0;   //0을 반환하고 함수 종료
}
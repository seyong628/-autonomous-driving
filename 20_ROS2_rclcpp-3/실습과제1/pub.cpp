#include "rclcpp/rclcpp.hpp"//헤더파일
#include "std_msgs/msg/string.hpp"//헤더파일
#include <memory>//헤더파일
#include <chrono>//헤더파일
#include <functional>//헤더파일
using namespace std::chrono_literals;//이름공간
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mypub)//callback함수
{
    auto message = std_msgs::msg::String();//auto변수 선언
    message.data = "Hello world!";//message.data에 문자열 저장
    RCLCPP_INFO(node->get_logger(), "Publish: %s", message.data.c_str());//출력
    mypub->publish(message);//토픽에 추가
}
int main(int argc, char* argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS2초기화
    auto node = std::make_shared<rclcpp::Node>("node_pub1");//노드
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS
    auto pub = node->create_publisher<std_msgs::msg::String>("topic_pub1", qos_profile);//pub
    std::function<void()> fn = std::bind(callback, node, pub);//bind
    auto timer = node->create_wall_timer(100ms, fn);//timer
    rclcpp::spin(node);//spin
    rclcpp::shutdown();//shutdown
    return 0;//0을 반환하고 함수 종료
}
#include "rclcpp/rclcpp.hpp"//헤더파일
#include "std_msgs/msg/int32.hpp"//헤더파일
#include <memory>//헤더파일
#include <chrono>//헤더파일
#include <functional>//헤더파일
using namespace std::chrono_literals;//이름공간
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr mypub)//callback함수
{
    static int count = 0;//변수 선언
    auto message = std_msgs::msg::Int32();//auto변수 선언
    message.data = count++; //message.data에 count증가하면서 저장
    RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);//출력
    mypub->publish(message);//토픽에 추가
}
int main(int argc, char* argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS2초기화
    auto node = std::make_shared<rclcpp::Node>("node_pub1");//node설정
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS선언
    auto pub = node->create_publisher<std_msgs::msg::Int32>("topic_pub1", qos_profile);//pub선언
    std::function<void()> fn = std::bind(callback, node, pub);//bind를 이용한 함수
    auto timer = node->create_wall_timer(50ms, fn);//timer
    rclcpp::spin(node);//spin함수
    rclcpp::shutdown();//shutdown
    return 0;   //0을 반환하고 함수 종료
}
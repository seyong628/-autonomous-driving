#include "rclcpp/rclcpp.hpp"        //헤더파일
#include "geometry_msgs/msg/twist.hpp"   //헤더파일
#include <memory>                   //헤더파일
#include <chrono>                   //헤더파일
#include <functional>               //헤더파일
using namespace std::chrono_literals;   //이름공간
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr mypub)//callback함수 구현
{
    auto message = geometry_msgs::msg::Twist();  //auto를 이용한 변수 선언
    message.linear.x = 3;   //선속도 설정
    message.angular.z = 3;  //각속도 설정
    RCLCPP_INFO(node->get_logger(), "Publish: ");//출력
    mypub->publish(message);    //토픽으로 발행
}   
int main(int argc, char* argv[])    //메인 함수
{
    rclcpp::init(argc, argv);   //ROS초기화
    auto node = std::make_shared<rclcpp::Node>("mynode");//스마트 포인터
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS선언
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);//publisher 선언
    std::function<void()> fn = std::bind(callback, node, pub);//bind함수로 매개변수 변경
    auto timer = node->create_wall_timer(100ms, fn);//timer설정
    rclcpp::spin(node); //무한 반복
    rclcpp::shutdown(); //셧다운
    return 0;   //0을 반환하고 함수 종료
}
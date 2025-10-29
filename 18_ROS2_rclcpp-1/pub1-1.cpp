#include "rclcpp/rclcpp.hpp"        //ROS2 cpp include
#include "std_msgs/msg/int32.hpp"   //헤더파일 포함
#include <memory>                   //헤더파일 포함
#include <chrono>                   //헤더파일 포함
int main(int argc, char * argv[])   //main함수
{                                   //함수 시작
    rclcpp::init(argc, argv);       //ROS 초기화
    auto node = std::make_shared<rclcpp::Node>("node_pub1");//스마트포인터 생성
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));   //QoS 선언
    auto mypub = node->create_publisher<std_msgs::msg::Int32>("topic_pub1",
    qos_profile );  //publisher 생성
    std_msgs::msg::Int32 message;   //객체멤버변수 값 생성
    message.data = 0;       // 객체멤버변수 값 초기화
    rclcpp::WallRate loop_rate(2.0); //반복주파수를 저장하는 객체(단위 Hz)
    while(rclcpp::ok()) //while 반복문 ctrl+c누르면 종료
    {
        RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);//터미널에 출력
        mypub->publish(message);    //토픽으로 발행
        loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
        message.data++; //message.data증가
    }
    rclcpp::shutdown();//시스템 출력
    return 0;   //0을 반환하고 함수 종료
}   //함수끝
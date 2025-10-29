#include "rclcpp/rclcpp.hpp"    //헤더파일 포함
#include "geometry_msgs/msg/vector3.hpp"//헤더파일 포함
#include <memory>//헤더파일 포함
#include <chrono>//헤더파일 포함
using namespace std;//이름공간 std
int main(int argc, char * argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS 초기화
    auto node = std::make_shared<rclcpp::Node>("node_pub1");//스마트 포인터
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));   //QoS 선언
    auto mypub = node->create_publisher<geometry_msgs::msg::Vector3>("topic_pub1", qos_profile );//publisher 선언
    geometry_msgs::msg::Vector3 message;    //벡터 선언
    float a[3]; //실수 배열 선언
    rclcpp::WallRate loop_rate(1.0); //반복주파수를 저장하는 객체(단위 Hz)
    while(rclcpp::ok()) //while 반복문 ctrl+c누르면 종료
    {
        for(int i = 0; i < 3; i++){//for반복문 i가 0부터 3까지 반복
            RCLCPP_INFO(node->get_logger(), "%d번째 실수를 입력 : ", i+1);//출력
            cin >> a[i];    //입력
        }
        message.x = a[0];//입력받은 값 저장
        message.y = a[1];//입력받은 값 저장
        message.z = a[2];//입력받은 값 저장
        RCLCPP_INFO(node->get_logger(), "Publish: %f, %f, %f", message.x, message.y,message.z);//출력
        mypub->publish(message);    //토픽으로 발행
        loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
    }
    rclcpp::shutdown();//시스템 종료
    return 0;   //0을 반환하고 함수 종료
}
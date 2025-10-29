#include "rclcpp/rclcpp.hpp"    //헤더파일 포함
#include "geometry_msgs/msg/twist.hpp"//헤더파일 포함
#include "std_msgs/msg/string.hpp"  //헤더파일 포함
#include <memory>//헤더파일 포함
#include <chrono>//헤더파일 포함
using namespace std;//이름공간 std
int main(int argc, char * argv[])//main함수
{
    rclcpp::init(argc, argv);//ROS 초기화
    auto node = std::make_shared<rclcpp::Node>("node_pub1");//스마트 포인터
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));   //QoS 선언
    auto mypub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile );//publisher 선언
    geometry_msgs::msg::Twist message;    //벡터 선언
    std_msgs::msg::String str;      //string 선언
    while(rclcpp::ok()) //while 반복문 ctrl+c누르면 종료
    {
        message.linear.x = 0;   //message.linear.x 0으로 초기화
        message.angular.z = 0;  //message.angular.z 0으로 초기화
        RCLCPP_INFO(node->get_logger(), "f, b, l, r 중 입력: ");//출력
        cin >> str.data;    //입력받은 값 str.data에 저장
        if(str.data == "f"){    //if 조건문 str.data이 f이면 
            message.linear.x = 3;   //message.linear.x에 3저장
        }
        else if(str.data == "b"){   //else if조건문 str.data이 b일때
            message.linear.x = -3;  //message.linear.x에 -3 저장
        }
        else if(str.data == "r"){   //else if조건문 str.data이 r일때
            message.angular.z = -1; //message.angular.z에 -1저장
        }
        else if(str.data == "l"){   //else if조건문 str.data이 l일때
            message.angular.z = 1;  //message.angular.z에 1저장
        }
        else {                      //else조건문
            RCLCPP_INFO(node->get_logger(), "f, b, l, r 중 입력");//출력
        }
        mypub->publish(message);    //토픽으로 발행
    }
    rclcpp::shutdown();//시스템 종료
    return 0;   //0을 반환하고 함수 종료
}
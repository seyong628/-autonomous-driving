#include "rclcpp/rclcpp.hpp"        //헤더파일
#include "geometry_msgs/msg/vector3.hpp"   //헤더파일
#include <memory>                   //헤더파일
#include <chrono>                   //헤더파일
#include <functional>               //헤더파일
using namespace std;
using namespace std::chrono_literals;   //이름공간
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr mypub)//callback함수 구현
{
    static float a[3];       //배열 선언
    auto message = geometry_msgs::msg::Vector3();  //auto를 이용한 변수 선언
    for(int i = 0; i < 3; i++){         //for반복문 i가 0부터 3까지
        RCLCPP_INFO(node->get_logger(), "%d번째 실수를 입력 : ", i+1);//출력
        cin >> a[i];    //입력
    }
    message.x = a[0];       //message.x에 a[0]저장
    message.y = a[1];       //message.y에 a[1]저장
    message.z = a[2];       //message.z에 a[2]저장
    RCLCPP_INFO(node->get_logger(), "Publish: %f, %f, %f", message.x, message.y, message.z);//출력
    mypub->publish(message);    //토픽으로 발행
}   
int main(int argc, char* argv[])    //메인 함수
{
    rclcpp::init(argc, argv);   //ROS초기화
    auto node = std::make_shared<rclcpp::Node>("mynode");//스마트 포인터
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS선언
    auto pub = node->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile);//publisher 선언
    std::function<void()> fn = std::bind(callback, node, pub);//bind함수로 매개변수 변경
    auto timer = node->create_wall_timer(10ms, fn);//timer설정
    rclcpp::spin(node); //무한 반복
    rclcpp::shutdown(); //셧다운
    return 0;   //0을 반환하고 함수 종료
}
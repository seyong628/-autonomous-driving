#include "rclcpp/rclcpp.hpp"        //헤더파일
#include "std_msgs/msg/int32.hpp"   //헤더파일
#include <memory>                   //헤더파일
#include <chrono>                   //헤더파일
#include <functional>               //헤더파일
using namespace std::chrono_literals;   //이름공간
void callback(rclcpp::Node::SharedPtr node,
rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr mypub)//callback함수 구현
{
    static int count = 0;       //변수 선언
    auto message = std_msgs::msg::Int32();  //auto를 이용한 변수 선언
    message.data = count++; //count를 증가 시키면서 message.data에 저장
    RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);//출력
    mypub->publish(message);    //토픽으로 발행
}   
int main(int argc, char* argv[])    //메인 함수
{
    rclcpp::init(argc, argv);   //ROS초기화
    auto node = std::make_shared<rclcpp::Node>("mynode");//스마트 포인터
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));//QoS선언
    auto pub = node->create_publisher<std_msgs::msg::Int32>("mytopic", qos_profile);//publisher 선언
    std::function<void()> fn = std::bind(callback, node, pub);//bind함수로 매개변수 변경
    auto timer = node->create_wall_timer(100ms, fn);//timer설정
    rclcpp::spin(node); //무한 반복
    rclcpp::shutdown(); //셧다운
    return 0;   //0을 반환하고 함수 종료
}
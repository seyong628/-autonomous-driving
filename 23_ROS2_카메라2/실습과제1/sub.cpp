#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>
using std::placeholders::_1;
  
void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat frame1 = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_GRAYSCALE);
    //cv::Mat frame2 = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_GRAYSCALE);
    cv::Mat frame2;
    cv::threshold(frame1, frame2, 127, 255, cv::THRESH_BINARY);
    cv::imshow("wsl1",frame1);
    cv::imshow("wsl2",frame2);
    cv::waitKey(1);
    RCLCPP_INFO(node->get_logger(), "Received Image1 : %s,%d,%d\r\nReceived Image2 : %s,%d,%d", msg->format.c_str(),frame1.rows,frame1.cols,msg->format.c_str(),frame2.rows,frame2.cols);
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("camsub_wsl5");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); //TCP
    //auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort(); //UDP
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, _1);
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>("image/compressed5",qos_profile,fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
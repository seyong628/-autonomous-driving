#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include <memory>
#include <chrono>
#include <iostream>

//std::string src = "/home/linux/ros2_ws/src/simulation/7_lt_ccw_100rpm_in.mp4"; 
std::string src = "/home/linux/ros2_ws/src/simulation/5_lt_cw_100rpm_out.mp4"; 

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("campub5");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); 

    // 토픽 이름 설정 
    auto mypub = node->create_publisher<sensor_msgs::msg::CompressedImage>("image/compressed_5", qos_profile);
    
    std_msgs::msg::Header hdr;
    sensor_msgs::msg::CompressedImage::SharedPtr msg;
    
    // 영상 프레임 속도에 맞춰 발행 주기 설정
    rclcpp::WallRate loop_rate(30.0); 

    cv::VideoCapture cap(src);
    if (!cap.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Could not open video! Check file path: %s", src.c_str());
        rclcpp::shutdown();
        return -1;
    }

    cv::Mat frame;
    while(rclcpp::ok())
    {
        cap >> frame;
        if (frame.empty()) { 
            RCLCPP_INFO(node->get_logger(), "Video finished."); 
            break;
        }

        msg = cv_bridge::CvImage(hdr, "bgr8", frame).toCompressedImageMsg();
        
        mypub->publish(*msg);
        
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
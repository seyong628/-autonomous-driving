#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include <memory>
#include <chrono>
#include <iostream>

std::string src = "ros2_ws/simulation/5_it_cw_100rpm_out.mp4";

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("campub5");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); //TCP
    //auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort(); //UDP
    auto mypub = node->create_publisher<sensor_msgs::msg::CompressedImage>("image/compressed_5", qos_profile );
    
    std_msgs::msg::Header hdr;
    sensor_msgs::msg::CompressedImage::SharedPtr msg;
    rclcpp::WallRate loop_rate(10.0);

    cv::VideoCapture cap(src, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Could not open video!");
        rclcpp::shutdown();
        return -1;
    }
    cv::Mat frame;

    while(rclcpp::ok())
    {
        cap >> frame;
        if (frame.empty()) { RCLCPP_ERROR(node->get_logger(), "frame empty"); break;}
        msg = cv_bridge::CvImage(hdr, "bgr8", frame).toCompressedImageMsg();
        mypub->publish(*msg);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
    return 0;
}
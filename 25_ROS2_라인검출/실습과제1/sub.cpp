#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
#include <functional>
#include <iostream>
#include <chrono>
using namespace std;
using std::placeholders::_1;

cv::VideoWriter recorder("save.mp4",cv::VideoWriter::fourcc('X','2','6','4'),10,cv::Size(640, 360));
void mysub_callback(rclcpp::Node::SharedPtr node, const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    auto startTime = std::chrono::steady_clock::now();
    cv::Mat gray, bin, frame2, ;
    cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    recorder.write(frame);
    cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);
    frame2 = gray + (100.0 - cv::mean(gray)[0]);
    cv::threshold(gray,bin,120,255,cv::THRESH_BINARY);
    cv::Mat roi = bin(cv::Rect(0,270,640,90));
    cv::Mat labels, stats, centroids;
    int num = cv::connectedComponentsWithStats(roi, labels, stats, centroids);
    int max_area = 0, max_label = -1;
    for(int i = 1; i < num; i++){
        int area = stats.at<int>(i, cv::)
    }
    
    //cv::imshow("gray",gray);
    //cv::imshow("frame2",frame2);
    cv::imshow("wsl",frame);
    cv::imshow("wsl2",roi);
    
    cv::waitKey(1);
    RCLCPP_INFO(node->get_logger(), "Received Image : %s,%d,%d", msg->format.c_str(),frame.rows,frame.cols);
    auto endTime = std::chrono::steady_clock::now(); // 종료시간 저장
    float totalTime = std::chrono::duration<float, std::milli>(endTime - startTime).count();
    cout << totalTime << endl; // 시간차이(msec)출력
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("camsub_wsl5");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)); //TCP
    //auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort(); //UDP
    std::function<void(const sensor_msgs::msg::CompressedImage::SharedPtr msg)> fn;
    fn = std::bind(mysub_callback, node, _1);
    auto mysub = node->create_subscription<sensor_msgs::msg::CompressedImage>("image/compressed_5",qos_profile,fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

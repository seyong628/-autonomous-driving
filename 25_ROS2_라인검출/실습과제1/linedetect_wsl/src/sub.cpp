#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "opencv2/opencv.hpp"
#include "class.hpp"
#include <memory>
#include <functional>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using std::placeholders::_1;

class LineDetectNode : public rclcpp::Node {
private:
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr sub_;
    cv::VideoWriter recorder_;
    LineDetector detector_;

public:
    LineDetectNode() : Node("camsub_wsl5") {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        
        sub_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
            "image/compressed_5", 
            qos_profile, 
            std::bind(&LineDetectNode::mysub_callback, this, _1)
        );
    }

    void mysub_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
        auto startTime = std::chrono::steady_clock::now();

        Mat frame = imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
        if (frame.empty()) {
            RCLCPP_WARN(this->get_logger(), "Empty frame");
            return;
        }
        recorder_.write(frame);
        
        // 전처리
        Mat thresh = detector_.preprocess(frame);

        // 객체 감지
        Mat stats, centroids;
        detector_.findObjects(thresh, stats, centroids);

        // 그리기
        detector_.drawObjects(stats, centroids, thresh);

        // 에러 계산
        int error = detector_.getError(thresh.cols);

        // 결과 출력
        imshow("wsl", frame);
        imshow("wsl2", thresh);
        waitKey(1);

        // 시간 측정 및 로그 출력
        auto endTime = std::chrono::steady_clock::now();
        float totalTime_s = std::chrono::duration<float, std::milli>(endTime - startTime).count() / 1000.0f;

        RCLCPP_INFO(this->get_logger(), "err:%d, time:%.5f", error, totalTime_s);
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LineDetectNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
#ifndef CLASS_HPP
#define CLASS_HPP

#include "opencv2/opencv.hpp"

class LineDetector {
private:
    bool has_tmp_pt = false;
    cv::Point tmp_pt;

public:
    // 생성자
    LineDetector();
    // 전처리 함수
    cv::Mat preprocess(const cv::Mat& frame);
    // 객체 감지 및 추적 함수
    void findObjects(cv::Mat& thresh, cv::Mat& stats, cv::Mat& centroids);
    // 객체 바운딩 박스 그리기 함수
    void drawObjects(const cv::Mat& stats, const cv::Mat& centroids, cv::Mat& thresh);
    // 에러 계산 함수
    int getError(int width);
    // 현재 추적 점 확인용
    cv::Point getPoint() const;
};

#endif
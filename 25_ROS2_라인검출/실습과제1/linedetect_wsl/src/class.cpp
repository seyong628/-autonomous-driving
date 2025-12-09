#include "class.hpp"
#include <iostream>

using namespace cv;
using namespace std;

LineDetector::LineDetector() : has_tmp_pt(false), tmp_pt(Point(0, 0)) {}

// 전처리 함수
Mat LineDetector::preprocess(const Mat& frame) {
    Mat gray, thresh;
    
    // 그레이스케일 변환
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // 밝기 보정
    gray = gray + (100 - mean(gray)[0]);
    
    // 이진화
    threshold(gray, thresh, 130, 255, THRESH_BINARY);
    
    // ROI 설정
    int r_pts = thresh.rows / 4 * 3;
    Rect r(0, r_pts, thresh.cols, thresh.rows - r_pts);
    
    // ROI 영역만 잘라서 리턴
    Mat roi_img = thresh(r).clone();
    
    // 첫 프레임일 경우 초기 좌표 설정
    if (!has_tmp_pt) {
        tmp_pt = Point(roi_img.cols / 2, roi_img.rows / 2);
        has_tmp_pt = true;
    }
    return roi_img;
}

// 객체 감지 및 추적 함수
void LineDetector::findObjects(Mat& thresh, Mat& stats, Mat& centroids) {
    Mat labels;
    // 라벨링 실행
    int cnt = connectedComponentsWithStats(thresh, labels, stats, centroids);
    
    // 시각화를 위해 1채널 -> 3채널 변환
    cvtColor(thresh, thresh, COLOR_GRAY2BGR);

    int min_index = -1;
    int min_dist = thresh.cols;

    for (int i = 1; i < cnt; i++) {
        int area = stats.at<int>(i, 4);

        if (area > 100) {
            int x = cvRound(centroids.at<double>(i, 0));
            int y = cvRound(centroids.at<double>(i, 1));

            int dist = norm(Point(x, y) - tmp_pt);

            if (dist < min_dist && dist <= 150) {
                min_dist = dist;
                min_index = i;
            }
        }
    }

    // 추적할 객체를 찾았다면 tmp_pt 갱신
    if (min_index != -1 && min_dist <= 150) {
        tmp_pt = Point(cvRound(centroids.at<double>(min_index, 0)), cvRound(centroids.at<double>(min_index, 1)));
    } else {
        // 못 찾았으면 이전 위치 표시만 (그리기용)
        circle(thresh, tmp_pt, 5, Scalar(0, 0, 255), -1);
    }
}

// 객체 바운딩 박스 그리기 함수
void LineDetector::drawObjects(const Mat& stats, const Mat& centroids, Mat& thresh) {
    for (int i = 1; i < stats.rows; i++) {
        int area = stats.at<int>(i, 4);
        
        if (area > 100) {
            int x = cvRound(centroids.at<double>(i, 0));
            int y = cvRound(centroids.at<double>(i, 1));
            
            int left   = stats.at<int>(i, 0); 
            int top    = stats.at<int>(i, 1); 
            int width  = stats.at<int>(i, 2); 
            int height = stats.at<int>(i, 3); 

            Rect box(left, top, width, height);

            if (x == tmp_pt.x) {
                rectangle(thresh, box, Scalar(0, 0, 255), 2);
                circle(thresh, Point(x, y), 5, Scalar(0, 0, 255), -1);
            } else {
                rectangle(thresh, box, Scalar(255, 0, 0), 2);
                circle(thresh, Point(x, y), 5, Scalar(255, 0, 0), -1);
            }
        }
    }
}

// 에러 계산 함수
int LineDetector::getError(int width) {
    return (width / 2) - tmp_pt.x;
}

Point LineDetector::getPoint() const {
    return tmp_pt;
}
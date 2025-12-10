# 실행 결과
- outline검출

  https://www.youtube.com/watch?v=a-AYH1y72Ds

- inline검출

  https://www.youtube.com/watch?v=UJcVf9efM58

# <linedetect_wsl/src/class.cpp>
## 설명
https://github.com/seyong628/-autonomous-driving/blob/0e4a2e6c0ee129dc3b2e4f16eaba3749b5b19922/25_ROS2_%EB%9D%BC%EC%9D%B8%EA%B2%80%EC%B6%9C/%EC%8B%A4%EC%8A%B5%EA%B3%BC%EC%A0%9C1/linedetect_wsl/src/class.cpp#L10-L35

- LineDetector::preprocess(const Mat& frame) 함수: 영상 전처리 함수
  
  받아온 영상을 그레이스케일로 변환 후 밝기 조정 -> 이진화 -> 영역 설정
  
  has_tmp_pt는 초기 좌표 설정을 하는데 초기값은 false로 두고 좌표는 설정한 영역의 중앙으로 지정.

https://github.com/seyong628/-autonomous-driving/blob/0e4a2e6c0ee129dc3b2e4f16eaba3749b5b19922/25_ROS2_%EB%9D%BC%EC%9D%B8%EA%B2%80%EC%B6%9C/%EC%8B%A4%EC%8A%B5%EA%B3%BC%EC%A0%9C1/linedetect_wsl/src/class.cpp#L38-L72

- LineDetector::findObjects(Mat& thresh, Mat& stats, Mat& centroids) 함수: 객체 감지 및 추적 함수

  레이블링 함수 connectedComponentsWithStats를 이용해 라인 후보 영역을 찾음.

  44줄에 시각화를 위해서 다시 BGR로 변경.

  min_index는 가장 유력한 차선 객체의 인덱스 번호, min_dist는 거리 비교를 위한 초기값이다.
  
  반복문을 통해 객체의 면적을 가져와서 100픽셀보다 큰것 중 객체의 무게중심 좌표를 이용해 이전 프레임의 점과 유클리드 거리 계산을 한다. 거리가 기존 최소값보다 작거나 150픽셀 이내에 있다면 min_dist와 min_index 갱신

  적절한 라인을 찾았으면 새로 찾은 라인의 위치를 갱신한다. 라인을 놓치면 이전 위치에 빨간 점만 찍는다.

  https://github.com/seyong628/-autonomous-driving/blob/0e4a2e6c0ee129dc3b2e4f16eaba3749b5b19922/25_ROS2_%EB%9D%BC%EC%9D%B8%EA%B2%80%EC%B6%9C/%EC%8B%A4%EC%8A%B5%EA%B3%BC%EC%A0%9C1/linedetect_wsl/src/class.cpp#L75-L99

  - LineDetector::drawObjects(const Mat& stats, const Mat& centroids, Mat& thresh) 함수: 객체 바운딩 박스 그리는 함수
 
    객체를 감싸는 사각형의 정보에 따라가는 라인이면 빨간색으로 그리고 아니면 파란색으로 그리기.

  https://github.com/seyong628/-autonomous-driving/blob/0e4a2e6c0ee129dc3b2e4f16eaba3749b5b19922/25_ROS2_%EB%9D%BC%EC%9D%B8%EA%B2%80%EC%B6%9C/%EC%8B%A4%EC%8A%B5%EA%B3%BC%EC%A0%9C1/linedetect_wsl/src/class.cpp#L102-L104

  - LineDetector::getError(int width) 함수: 에러 계산 함수

    로봇의 중심 x좌표 - 라인의 중심 x좌표

# <linedetect_wsl/src/sub.cpp>
## 설명
https://github.com/seyong628/-autonomous-driving/blob/1b730f300826efda1b93517b1e1fee8bfc96b5f0/25_ROS2_%EB%9D%BC%EC%9D%B8%EA%B2%80%EC%B6%9C/%EC%8B%A4%EC%8A%B5%EA%B3%BC%EC%A0%9C1/linedetect_wsl/src/sub.cpp#L14-L64

- class LineDetectNode: ROS2 통신기능과 영상처리 알고리즘 열결하는 클래스

  18줄에 알고리즘 클래스 인스턴스이다.

  생성자에 QoS, sub 선언 후 콜백 함수 호출

  mysub_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg): 콜백 함수

  성능 측정을 위해 시간 기록을 시작하고 ROS 메시지를 OpenCV 이미지로 변환한다. LineDetector클래스의 멤버함수인 preprocess를 이용해 전처리하고 findObjects와 drawObjects를 이용해 객체를 감지하고 바운딩 박스를 그린다. 그 후 결과 출력하고 시간 측정 및 로그, 에러를 출력한다.

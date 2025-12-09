cmake_minimum_required(VERSION 3.16)
project(linedetect_wsl)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# 헤더 파일을 찾을 수 있도록 include와 src 디렉토리 추가
include_directories(include src)

# build
# 실행 파일 이름: linedetect_wsl
# 소스 파일: sub.cpp, linedetector.cpp (사용자가 class.cpp라고 했지만 위 add_executable에 적힌대로 따름)
add_executable(linedetect_wsl src/sub.cpp src/class.cpp)

# 중요: 위에서 만든 target 이름(linedetect_wsl)과 똑같이 써야 합니다. (sub 아님)
ament_target_dependencies(linedetect_wsl rclcpp sensor_msgs cv_bridge OpenCV)

# Install
# 중요: 여기도 target 이름(linedetect_wsl)과 똑같이 써야 합니다.
install(TARGETS
  linedetect_wsl
  DESTINATION lib/${PROJECT_NAME})

ament_package()
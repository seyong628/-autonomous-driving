#### Nvidia사의 Jetson nano 보드에 대하여 조사하라
: Nvidia Jetson Nano는 인공지능과 딥러닝 응용을 위해 설계된 소형 싱글보드 컴퓨터로 라파처럼 작지만 GPU가 내장되어 AI모델을 직접 실행할 수 있다는 점이 특징이다. CPU는 Quad-core ARM Cortex-A57 @ 1.43GHz이고 GPU는 NVIDIA Maxwell 아키텍처 기반 128 CUDA 코어, RAM은 4GB LPDDR4이다.

#### IMX219 카메라의 사양을 조사하라
: 센서는 Sony IMX219를 사용하고 8백만 화소, 해상도는 3280x2464 픽셀, 인터페이스는 CSI이다. 렌즈 사양은 CMOS 크기 1/4인치, 조리개 F2.35, 초점 거리 3.15mm, 화각은 제품에 따라 다르지만 160도, 175도 등의 광각 렌즈가 많이 사용된다. 전원은 4개의 나사 구멍으로 3.3V 직류 공급이 가능하다.

#### 카메라의 리눅스 장치파일 이름은?
: ls -l /dev/video*를 치면 /dev/video0이 출력되는데 파일 이름은 /dev/video0이다.

#### CSI(camera serial interface)에 대하여 조사하라
: CSI는 카메라 모듈을 프로세서에 고속으로 연결하기 위한 직렬 데이터 전송 인터페이스 표준이다. CSI는 세 가지 주요 구성요소로 이루어지는데 첫번째는 Camera Sensor은 실제 영상을 촬영하고 디지털 신호로 변환하는 장치이고 두번째 CSI Interface는 센서의 데이터를 직렬 형태로 전송하는 통신선, 마지막은 Receiver은 데이터를 받아서 메모리나 GPU에서 처리하는 요소이다. 동작 방식은 1개의 클럭 레인과 N개의 데이터 레인으로 구성되는데 각 데이터 레인은 차동신호로 데이터를 송수신하고, 레이인 수가 많을 수록 대역폭이 커집니다. CSI의 장점은 고속 전송과 저전력 소모, 잡음 저항성, 소형화 가능이 있는데 단점으로는 케이블 길이 제한이 있고, 전용 포트가 필요가 필요하다는 단점이 있다.

#### Gstreamer에 대하여 자세히 조사하라
: Gstreamer는 Pipeline 개념으로 작동하는데 데이터가 여러 처리 단계를 연결된 요소들을 통해 흐르는데 구성 요소는 PipeLine, Element, Pad, Bin, Plugin으로 구성된다.
Pipeline : 전체 스트림 처리 구조
Element : 각각의 처리 단계
Pad : 데이터 입출력 단자
Bin : 여러 Element를 묶은 그룹
Plugin : Element들의 묶음
장점으로는 모듈식 구조라 필요 요소만 연결해서 사용 가능하고, 범용성이 뛰어나고, 하드웨어 가속을 지원하고 멀티 플랫폼지원, 스트리밍 지원이 장점이다. 단점은 학습 곡선이 높고 버전 호환성 문제가 있다.

#### Dynamixel에 대하여 자세히 조사하라
: Dynamixel은 ROBOTIS에서 개발한 지능형 서보 모터 브랜드이다. 주요 특징은 모터 내부에 제어회로 내장, PID 제어가 가능하고, TTL, RS-485, CAN 등 시리얼 통신으로 제어하고 여러 모터를 직렬로 연결해 개별 제어가 가능하다는 특징이 있다. Dynamixel의 내부 구조는 DC 모터와 감속기, 엔코더, 제어 보드, 통신 포트, 온도/전류 센서로 구성되고 통신 방식은 전용 버스 통신을 사용해 여러 모터를 하나의 케이블로 연결한다.
주요 제어 모드
Position Control Mode : 각도를 지정하여 정확한 위치로 이동
Velocity Control Mode : 특정 속도로 지속 회전
PWM Control Mode : PWM 신호를 직접 제어
Current Control Mode : 전류 제어
Extended Position Mode : 0~360도 이상, 다회전 가능
Multi-turn Mode : 무한 회전

#### U2D2 장치의 역할은 무엇인가?
: U2D2는 ROBOTIS에서 개발한 통신 변환 장치인데 Jetson nano의 usb포트와 Dynamixel 모터 통신 포트 사이를 연결해주는 통신 변환기이다. Jetson nano에서 보낸 USB 데이터를 Dynamixel 신호로 변환해서 Dynamixel에 보낸다.

#### U2D2 리눅스 장치파일의 이름은?
: ls -l /dev/ttyUSB*을 치면 /dev/ttyUSB0이 출력되는데 파일 이름은 /dev/ttyUSB0이다.

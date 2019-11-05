#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


bool mouse_is_pressing = false;   // 왼쪽 마우스 버튼 상태 체크를 위해 사용
bool drawing_mode = true;       // 현재 그리기 모드 선택을 위해 사용 ( 원 / 사각형 )
int start_x = -1;
int start_y = -1; //최초로 왼쪽 마우스 버튼 누른 위치를 저장하기 위해 사용
Scalar color(255, 255, 255);   // 도형 내부 채울때 사용할 색 지정시 사용 ( 초기값은 흰색 )
Mat img;
RNG rng(543210);


// 1. 마우스 이벤트 발생시 호출될 함수를 정의합니다. 
void mouse_callback(int event, int x, int y, int flags, void* userdata) {

	if (event == EVENT_MOUSEMOVE) {
		if (mouse_is_pressing == true) {  // 마우스 왼쪽 버튼을 누른 채 이동하면 

			if (drawing_mode == true)  // 이동된 마우스 커서 위치를 반영하여 사각형/윈을 그림
				rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
			else
				circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
		}
	}
	else if (event == EVENT_LBUTTONDOWN) {
		// 랜덤으로 (blue, green, red)로 사용될 색을 생성
		color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		mouse_is_pressing = true;     // 왼쪽 마우스 버튼을 누른 것 감지 
		start_x = x;
		start_y = y;     // 최초로 왼쪽 마우스 버튼 누른 위치를 저장 

	}
	else if (event == EVENT_LBUTTONUP) {

		mouse_is_pressing = false;    // 왼쪽 마우스 버튼에서 손뗀 것을 감지   

		if (drawing_mode == true)  // 최종 위치에 마우스 커서 위치를 반영하여 사각형/윈을 그림
			rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
		else
			circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
	}
}


int main()
{
	int width = 500;
	int height = 500;

	img = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));

	namedWindow("image");
	setMouseCallback("image", mouse_callback, 0);


	while (1) {

		imshow("image", img);

		int key = waitKey(1);

		if (key == 'm')
			drawing_mode = !drawing_mode;
		else if (key == 27)
			break;
	}

	destroyAllWindows();
	waitKey(0);
}
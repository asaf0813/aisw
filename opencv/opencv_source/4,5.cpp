#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
Scalar red(0, 0, 255);
Scalar blue(255, 0, 0);
Scalar white(255, 255, 255);
Scalar black(0, 0, 0);
Mat image;
String title = "이벤트그리기";

int line_value = 1;
int radius_value = 1;

void onChangeline(int value, void* userdata)
{
	line_value = 0 + value;
}
void onChangeradius(int value, void* userdata)
{
	radius_value = 0 + value;
}
void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
Point pt(x, y);
Rect rect(pt, Size(30, 30));

	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		if (flags & EVENT_FLAG_CTRLKEY)
		{
			rectangle(image, rect, red, line_value);
			imshow(title, image);
		}
		else if (flags & EVENT_FLAG_SHIFTKEY)
		{
			rectangle(image, rect, blue, line_value);
			imshow(title, image);
		}
		break;
	case EVENT_RBUTTONDOWN:
		if (flags & EVENT_FLAG_CTRLKEY)
		{
			circle(image, pt, radius_value, red, line_value);
			imshow(title, image);
		}
		else if (flags & EVENT_FLAG_SHIFTKEY)
		{
			circle(image, pt, radius_value, blue, line_value);
			imshow(title, image);
		}
		break;
	}
}
int main()
{
	image =  Mat(400, 600, CV_8UC3, white);

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("굵기값", title, &line_value, 10, onChangeline);
	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("반지름", title, &radius_value, 50, onChangeradius);

	imshow(title, image);
	setMouseCallback(title, mouse_callback, 0);
	waitKey(0);
	return 0;
}
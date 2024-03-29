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

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	Point pt(x, y);
	Rect rect(pt, Size(30, 30));

	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		if (flags & EVENT_LBUTTONDOWN)
		{
			rectangle(image, rect, black, -1);
			imshow(title, image);
		}
		break;
	case EVENT_RBUTTONDOWN:
		if (flags & EVENT_RBUTTONDOWN)
		{
			circle(image, pt, 20, black, -1);
			imshow(title, image);
		}
		break;
	}
}
int main()
{
	image = Mat(400, 600, CV_8UC3, white);
	imshow(title, image);
	setMouseCallback(title, mouse_callback, 0);
	waitKey(0);
	return 0;
}
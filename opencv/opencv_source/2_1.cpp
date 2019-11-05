
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void put_string(Mat& frame, string text, Point  pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}

VideoCapture capture;

void contrast_bar(int value, void*)
{
	capture.set(CAP_PROP_CONTRAST, value);
}

void brightenss_bar(int value, void*)
{
	capture.set(CAP_PROP_BRIGHTNESS, value);
}

int main()
{
	capture.open(0);
	CV_Assert(capture.isOpened());

	capture.set(CAP_PROP_FRAME_WIDTH, 1000);
	capture.set(CAP_PROP_FRAME_HEIGHT, 800);
	capture.set(CAP_PROP_AUTOFOCUS, 0);

	int contrast = capture.get(CAP_PROP_CONTRAST);
	int brightenss = capture.get(CAP_PROP_BRIGHTNESS);

	string title = "카메라 속성변경";
	namedWindow(title);
	createTrackbar("contrast", title, &contrast, 40, contrast_bar);
	createTrackbar("brightenss", title, &brightenss, 100, brightenss_bar);

	for (;;)
	{
		Mat frame;
		capture >> frame;

		put_string(frame, "contrast : ", Point(10, 240), contrast);
		put_string(frame, "brightenss : ", Point(10, 270), brightenss);

		imshow(title, frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
Scalar red(0, 0, 255);
Point pt(200, 100);
Rect rect(pt, Size(100, 200));



void put_string(Mat& frame, string text, Point  pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}


int main()
{
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cout << "첫번째 카메라를 열 수 없습니다." << endl;
		exit(1);
	}

	cout << "너비" << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
	cout << "높이" << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
	cout << "노출" << capture.get(CAP_PROP_EXPOSURE) << endl;
	cout << "밝기" << capture.get(CAP_PROP_BRIGHTNESS) << endl;

	for (;;)
	{
		Mat frame;
		capture.read(frame);

		Mat image;
		image = frame(Rect(200, 100, 100, 200));
		image += Scalar(0, 50, 0);

		put_string(frame, "EXPOSE", Point(10, 40), capture.get(CAP_PROP_EXPOSURE));

		rectangle(frame, rect, red, 3);

		imshow("카메라영상보기", frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
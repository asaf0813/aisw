#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture(0);
	CV_Assert(capture.isOpened());

	double fps = 15;
	int delay = cvRound(1000.0 / fps);
	Size  size(640, 480);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');

	capture.set(CAP_PROP_FRAME_WIDTH, size.width);
	capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	cout << "width x height : " << size << endl;
	cout << "VideoWriter::fourcc : " << fourcc << endl;
	cout << "delay : " << delay << endl;
	cout << "fps : " << fps << endl;

	VideoWriter writer;
	writer.open("C:/Users/PIRL/Desktop/flip_test.avi", fourcc, fps, size);
	CV_Assert(writer.isOpened());

	for (;;)
	{
		Mat frame;
		capture >> frame;
		imshow("원본", frame);
		Mat change;
		flip(frame, change, 1);

		imshow("좌우반전", change);
		writer << change;
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
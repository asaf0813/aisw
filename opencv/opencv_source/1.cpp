#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Scalar red(0, 0, 255);
	Scalar white(255, 255, 255);

	Mat image(600, 400, CV_8UC3, white);
	string title = "1������";

	Point pt(100, 100);
	Rect rect(pt, Size(200, 300));

	rectangle(image, rect, red, FILLED);

	namedWindow(title, WINDOW_AUTOSIZE);
	
	imshow(title, image);
	waitKey();
	destroyAllWindows();
	return 0;
}
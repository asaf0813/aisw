#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Scalar red(0, 0, 255);
	Scalar blue(255, 0, 0);
	Scalar white(255, 255, 255);
	Mat image(400, 600, CV_8UC3, white);
	string title = "2¹ø¹®Á¦";
	
	Point center(300, 200);
	Point p1(250, 200);
	Point p2(350, 200);

	ellipse(image, center, Size(100, 100),0, 0, 180, blue, -1);
	ellipse(image, center, Size(100, 100), 0, 180, 360, red, -1);
	ellipse(image, p1, Size(50, 50), 0, 0, 180, red, -1);
	ellipse(image, p2, Size(50, 50), 0, 180, 360, blue, -1);

	namedWindow(title, WINDOW_AUTOSIZE);

	imshow(title, image);
	waitKey();
	destroyAllWindows();
	return 0;
}

#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{

	Mat logo = imread("C:/Users/PIRL/Desktop/logo.jpg", IMREAD_COLOR);

	Mat bgr[3];

	Mat zFillMatrix = cv::Mat::zeros(logo.size(), CV_8UC1);

	split(logo, bgr);

	Mat R[] = { zFillMatrix, zFillMatrix, bgr[2] };
	Mat G[] = { zFillMatrix, bgr[1], zFillMatrix };
	Mat B[] = { bgr[0], zFillMatrix, zFillMatrix };
	merge(R, 3, bgr[2]);
	merge(G, 3, bgr[1]);
	merge(B, 3, bgr[0]);

	namedWindow("Image");
	namedWindow("Red_Image");
	namedWindow("Green_Image");
	namedWindow("Blue_Image");

	imshow("Image", logo);
	imshow("Red_Image", bgr[2]);  
	imshow("Green_Image", bgr[1]);
	imshow("Blue_Image", bgr[0]);
	
	waitKey();
	return 0;
}
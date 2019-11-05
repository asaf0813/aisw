#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void filter(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_32F, Scalar(0));
	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;
			for (int u = 0; u < mask.rows; u++) {
				for (int v = 0; v < mask.cols; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += img.at<uchar>(y, x) * mask.at<float>(u, v);
				}
			}
			dst.at<float>(i, j) = sum;
		}
	}
}

int main()
{
	Mat image = imread("C:/Users/PIRL/Desktop/camp.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	float data1[] = {
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0
	};
	float data2[] = {
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1
	};

	Mat masks1(3, 3, CV_32F, data1);
	Mat masks2(3, 3, CV_32F, data2);

	Mat sharpen1, sharpen2;
	filter(image, sharpen1, masks1);
	filter(image, sharpen2, masks2);

	sharpen1.convertTo(sharpen1, CV_8U);
	sharpen2.convertTo(sharpen2, CV_8U);

	imshow("image", image);
	imshow("sharpen1", sharpen1), imshow("sharpen2", sharpen2);
	waitKey();
	return 0;
}

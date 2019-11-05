#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;

uchar bilinear_value(Mat img, double x, double y) { 
	if (x >= img.cols - 1) x--;
	if (y >= img.rows - 1) y--;


	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 - M1));
	return saturate_cast<uchar>(P);

}
void rotation(Mat img, Mat& dst, double dgree, Point pt) //
{
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0;i < dst.rows;i++) {
		for (int j = 0;j < dst.cols;j++)
		{
			int jj = j - pt.x;
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}
int main()
{
	Mat image = imread("C:/Users/PIRL/Desktop/cat.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2, dst3;
	Point pt1(300, 100);
	Point center = image.size() / 2;

	rotation(image, dst1, 30, center); 
	rotation(image, dst2, 30, pt1);

	Point2f center1(300, 100); 
	double angle = 30.0;
	double scale = 1.0;
	Mat rotMat = getRotationMatrix2D(center1, -(angle), scale);

	Mat dstImage;
	int flags = INTER_LINEAR;
	warpAffine(image, dstImage, rotMat, Size(), flags);

	imshow("어파인 사용", dstImage);

	imshow("image", image);
	imshow("로테이션 사용", dst2);
	waitKey();
	return 0;
}
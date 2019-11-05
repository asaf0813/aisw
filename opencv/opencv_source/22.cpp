#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
using namespace cv;


void draw_histo(vector<int> data, Mat& img, int bins = 1, int height = 1)
{
	int rows, cols;
	rows = height;
	cols = data.size() * bins;
	img = Mat3b(rows, cols, Vec3b(255, 255, 255));

	for (int i = 0; i < data.size(); i++)
	{
		int start_x = (i * bins);
		int end_x = (i + 1) * bins;
		Point2d pt1(start_x, rows - data[i]);
		Point2d pt2(end_x, rows);
		rectangle(img, pt1, pt2, Scalar(0), -1);
	}
}

void draw_histo2(vector<int> data, Mat& img, int bins = 1, int height = 1)
{
	int rows, cols;
	rows = height-50;
	cols = data.size() * bins;
	img = Mat3b(rows, cols, Vec3b(255, 255, 255));

	for (int i = 0; i < data.size(); i++)
	{
		int start_x = (i * bins);
		int end_x = (i + 1) * bins;
		Point2d pt1(start_x, rows - data[i]);
		Point2d pt2(end_x, height);
		rectangle(img, pt1, pt2, Scalar(0), -1);
	}
}

int main()
{
	Mat image = imread("C:/Users/PIRL/Desktop/logo.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat rows, rows_image, cols, cols_image;

	reduce(image, rows, 1, REDUCE_AVG, CV_32S);
	draw_histo(rows, rows_image, 1, 308);

	reduce(image, cols, 0, REDUCE_AVG, CV_32S);
	draw_histo2(cols, cols_image, 1, 250);
	flip(cols_image, cols_image, 1);
	Point2f src_center(cols_image.cols / 2.0F, cols_image.rows / 2.0F);
	Mat rot_mat = getRotationMatrix2D(src_center, 90, 1.0);
	Mat dst;
	warpAffine(cols_image, cols_image, rot_mat, cols_image.size());

	imshow("image", image);
	imshow("project1", rows_image);
	imshow("project2", cols_image);


	waitKey();
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
using namespace cv;


void draw_histo(vector<int> data, Mat& img, int bins = 1, int height = 1)
{
	int Max_value = *max_element(data.begin(), data.end());
	int rows = 0;
	int cols = 0;

	rows = height;

	cols = data.size() * bins;
	img = Mat3b(rows, cols, Vec3b(255, 255, 255));

	for (int i = 0; i < data.size(); i++) {

		int a = rows - data[i];
		rectangle(img, Point(i * bins, a), Point(i * bins + 1, rows), Scalar(0, 0, 0), -1);

	}
}

void draw_histo2(vector<int> data, Mat& img, int bins = 1, int height = 1)
{
	int Max_value = *max_element(data.begin(), data.end());
	int rows = 0;
	int cols = 0;

	rows = height-50;

	cols = data.size() * bins;
	img = Mat3b(rows, cols, Vec3b(255, 255, 255));

	for (int i = 0; i < data.size(); i++) {

		int a = rows - data[i];
		rectangle(img, Point(i * bins, a), Point(i * bins + 1, height), Scalar(0, 0, 0), -1);

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
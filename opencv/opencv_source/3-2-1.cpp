
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


Mat mareHistogram(Mat& img, int t)
{

	//col or row histogram?
	int sz = (t) ? img.rows : img.cols;
	Mat mhist = Mat::zeros(1, sz, CV_8UC3);

	//count nonzero value and check max V
	int max = -100;
	for (int j = 0; j < sz; ++j)
	{
		Mat data = (t) ? img.row(j) : img.col(j);
		int v = countNonZero(data);
		mhist.at< unsigned char >(j) = v;
		if (v > max)
			max = v;
	}

	Mat histo;
	if (t)
	{

		histo = Mat::zeros(Size(256, 256), CV_8U);

		for (int i = 0; i < 256; ++i)
		{
			for (int j = 0; j < mhist.at< unsigned char >(i); ++j)
				histo.at< unsigned char >(i, j) = 256;
		}

	}
	else {

		histo = Mat::zeros(Size(256, 256), CV_8U);

		for (int i = 0; i < 256; ++i)
		{
			for (int j = 0; j < mhist.at< unsigned char >(i); ++j)
				histo.at< unsigned char >(max - j - 1, i) = 256;
		}

	}



	return histo;

}

void main()
{
	Mat img;
	img = imread("C:/Users/PIRL/Desktop/logo.jpg", 0);
	CV_Assert(!img.empty());

	//0 horizontal(width), 1 vertical(height)
	Mat hHisto = mareHistogram(img, 0);
	Mat vHisto = mareHistogram(img, 1);


	imshow("origin", img);
	imshow("hh", hHisto);
	imshow("vv", vHisto);

	waitKey(0);
}
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

void calc_histo(Mat image, Mat& hist, int bins, int range_max = 256)
{
	hist = Mat(bins, 1, CV_32F, Scalar(0));
	float gap = range_max / (float)bins;

	for (int i = 0; i < image.rows; i++)
	{
		{	
			int idx = int(image.at<uchar>(i, j) / gap);
			hist.at<float>(idx)++;
		}
	}
}

int main()
{
	Mat image = imread("C:/Users/PIRL/Desktop/camp.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist;
	calc_histo(image, hist, 256);
	cout << hist.t() << endl;

	imshow("image", image);
	waitKey();
	return 0;
}
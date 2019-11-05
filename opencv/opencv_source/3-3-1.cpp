#include <opencv2\opencv.hpp>

using namespace cv;
int main()
{
	Mat inputImg, resultImg;
	inputImg = imread("city.jpg", IMREAD_COLOR);
	CV_Assert(inputImg.depth() == CV_8U);
	resultImg.create(inputImg.size(), inputImg.type());
	const int nChannels = inputImg.channels();
	for (int j = 1; j < inputImg.rows - 1; ++j)
	{
		const uchar* prev = inputImg.ptr(j - 1);
		const uchar* curr = inputImg.ptr(j);
		const uchar* next = inputImg.ptr(j + 1);
		uchar* output = resultImg.ptr(j);
		for (int i = nChannels; i < nChannels * (inputImg.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * curr[i] - curr[i - nChannels] - curr[i + nChannels] - prev[i] - next[i]);
		}
	}
	resultImg.row(0).setTo(Scalar(0));
	resultImg.row(resultImg.rows - 1).setTo(Scalar(0));
	resultImg.col(0).setTo(Scalar(0));
	resultImg.col(resultImg.cols - 1).setTo(Scalar(0));
	imshow("Original", inputImg);
	imshow("S", resultImg);
	waitKey(0); 
	return 0;
}
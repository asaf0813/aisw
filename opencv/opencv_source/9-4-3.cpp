#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include "fft.hpp";

Mat image, dft_coef, spectrum_img;
int radius, thres = 120;
void remove_moire(int value, void* userdata)
{
	Mat remove_mask, remv_dft_coef, spectrum_tmp;
	spectrum_tmp = spectrum_img;
	threshold(spectrum_tmp, remove_mask, thres, 255, THRESH_TOZERO_INV);
	circle(remove_mask, remove_mask.size() / 2, radius, Scalar(255), -1);

	dft_coef.copyTo(remv_dft_coef, remove_mask);
	log_mag(remv_dft_coef, spectrum_tmp);

	Rect img_rect(Point(0, 0), image.size());
	imshow("모아레 제거", spectrum_tmp);
	imshow("결과영상", IFFT(remv_dft_coef, img_rect.size()));
}

int main()
{
	image = imread("C:/Users/PIRL/Desktop/5.jpg", 0);
	CV_Assert(image.data);
	FFT(image, dft_coef, spectrum_img);
	radius = dft_coef.rows / 4;

	imshow("image", image);
	imshow("모아레 제거", spectrum_img);
	createTrackbar("반지름", "모아레 제거", &radius, 255, remove_moire);
	createTrackbar("임계 값", "모아레 제거", &thres, 255, remove_moire);
	waitKey();
	return 0;
}
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat scramble(Mat signal)
{
	Mat dst = signal.clone();
	for (int i = 0, j = 0;i < dst.cols - 1;i++)
	{
		if (i > j)
		{
			swap(dst.at<Vec2f>(i), dst.at<Vec2f>(j));
		}

		int m = dst.cols >> 1;
		while ((j >= m) && (m >= 2))
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	return dst;
}
Mat zeropadding(Mat img)
{
	int m = 1 << (int)ceil(log2(img.rows));
	int n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());
	img.copyTo(dst(rect));
	dst.convertTo(dst, CV_32F);
	return dst;
}
Mat get_lowpassFilter(Size size, int radius)
{
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));
	circle(filter, center, radius, Vec2f(1, 1), -1);
	return filter;
}
Mat get_highpassFilter(Size size, int radius)
{
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(1, 1));
	circle(filter, center, radius, Vec2f(0, 0), -1);
	return filter;
}
void shuffling(Mat mag_img, Mat& dst)
{
	int cx = mag_img.cols / 2;
	int cy = mag_img.rows / 2;
	Rect q1(cx, 0, cx, cy);
	Rect q2(0, 0, cx, cy);
	Rect q3(0, cy, cx, cy);
	Rect q4(cx, cy, cx, cy);

	dst = Mat(mag_img.size(), mag_img.type());
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}
void butterfly(Mat& dst, int dir)
{
	int length = dst.cols;
	int pair = 1;

	for (int k = 0; k < ceil(log2(length)); k++)
	{
		int half_pair = pair;
		pair <<= 1;
		float theta = dir * (-2.0 * CV_PI / pair);
		float wpr = -2.0 * sin(0.5 * theta) * sin(0.5 * theta);
		float wpi = sin(theta);
		float wre = 1.0;
		float wim = 0.0;

		for (int m = 0; m < half_pair; m++)
		{
			for (int even = m; even < length; even += pair)
			{
				int odd = even + half_pair;
				Vec2f G_even = dst.at<Vec2f>(even);
				Vec2f G_odd = dst.at<Vec2f>(odd);

				Vec2f G_odd_W(0, 0);
				G_odd_W[0] = G_odd[0] * wre - G_odd[1] * wim;
				G_odd_W[1] = G_odd[1] * wre + G_odd[0] * wim;

				dst.at<Vec2f>(even) = G_even + G_odd_W;
				dst.at<Vec2f>(odd) = G_even - G_odd_W;
			}
			float tmp = wre;
			wre += tmp * wpr - wim * wpi;
			wim += wim * wpr + tmp * wpi;
		}
		if (dir == -1) dst /= dst.cols;
	}
}

void FFT_2D(Mat complex_img, Mat& dst, int dir)
{
	dst = Mat(complex_img.size(), complex_img.type());

	for (int i = 0; i < complex_img.rows;i++)
	{
		Mat scr_sn = scramble(complex_img.row(i));
		butterfly(scr_sn, dir);
		scr_sn.copyTo(dst.row(i));
	}
	transpose(dst, dst);
	for (int i = 0; i < dst.rows;i++)
	{
		Mat scr_sn = scramble(dst.row(i));
		butterfly(scr_sn, dir);
		scr_sn.copyTo(dst.row(i));
	}
	transpose(dst, dst);
}
void log_mag(Mat complex_mat, Mat& dst)
{
	Mat planes[2];
	split(complex_mat, planes);
	magnitude(planes[0], planes[1], dst);
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	dst.convertTo(dst, CV_8U);
}
void FFT(Mat image, Mat& dft_coef, Mat& dft_img)
{
	Mat complex_img;
	Mat pad_img = zeropadding(image);
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(),pad_img.type()) };
	merge(tmp, 2, complex_img);
	FFT_2D(complex_img, dft_coef, 1);
	dft(complex_img, dft_coef, 0);
	shuffling(dft_coef, dft_coef);
	log_mag(dft_coef, dft_img);

}
Mat IFFT(Mat dft_coef, Size size)
{
	Mat idft_coef, idft_img[2];
	shuffling(dft_coef, dft_coef);
	FFT_2D(dft_coef, idft_coef, -1);
	dft(dft_coef, idft_coef, DFT_INVERSE + DFT_SCALE);

	split(idft_coef, idft_img);

	Rect img_rect(Point(0, 0), size);
	idft_img[0](img_rect).convertTo(idft_img[0], CV_8U);
	return idft_img[0];
}

Mat getGausianFilter(Size size, int _sigma)
{
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));
	double sigma = 2 * _sigma * _sigma;

	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j<size.width; j++)
		{
			int x2 = (j - center.y) * (j - center.y);
			int y2 = (i - center.y) * (i - center.y);
			float w = exp(-(x2 + y2) / sigma);
			filter.at<Vec2f>(i, j) = Vec2f(w, w);
		}
	}
	return filter;
}
Mat getButterworthFilter(Size size, int D, int n)
{
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));
	
	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j < size.width; j++)
		{
			int x2 = (j - center.y) * (j - center.y);
			int y2 = (i - center.y) * (i - center.y);
			float distance = sqrt(x2 + y2);
			float w = 1 / (1 + pow(distance / D, 2 + n));
			filter.at<Vec2f>(i, j) = Vec2f(w, w);
		}
	}
	return filter;
}

int main()
{
	Mat image = imread("C:/Users/PIRL/Desktop/cat.jpg", 0);
	CV_Assert(image.data);

	Rect img_rect(Point(0, 0), image.size());
	Mat dft_coef, dft_img, low_dft, high_dft, filtered_mat1, filtered_mat2;

	FFT(image, dft_coef, dft_img);
	Mat gauss_filter = getGausianFilter(dft_coef.size(), 30);
	Mat butter_filter = getButterworthFilter(dft_coef.size(), 30, 4);

	multiply(dft_coef, gauss_filter, filtered_mat1);
	multiply(dft_coef, butter_filter, filtered_mat2);
	log_mag(filtered_mat1, gauss_filter);
	log_mag(filtered_mat2, butter_filter);

	imshow("image", image);
	imshow("dft_img", dft_img);
	imshow("gauss_filter", gauss_filter);
	imshow("butter_filter", butter_filter);
	imshow("gauss_filter_img", IFFT(filtered_mat1, image.size()));
	imshow("butter_filter_img", IFFT(filtered_mat2, image.size()));
	waitKey();
	return 0;
}
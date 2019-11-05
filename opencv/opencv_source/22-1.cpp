#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

void cDraw_Histo(Mat hist, Mat& hist_img, Size size = Size(256, 200)) {
	hist_img = Mat(size, CV_8U, Scalar(255));

	for (int i = 0; i < hist.cols; i++) {
		float start_x = i;
		float end_x = (i + 1);
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at<uchar>(0, i));

		rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}
void rDraw_Histo(Mat hist, Mat& hist_img, Size size = Size(256, 200)) {
	hist_img = Mat(size, CV_8U, Scalar(255));

	for (int i = 0; i < hist.rows; i++) {
		float start_x = i;
		float end_x = (i + 1);
		Point2f pt1(0, start_x);
		Point2f pt2(hist.at<uchar>(i, 0), end_x);

		rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, -1);
}
void test_main() {
	Mat logo = imread("C:/Users/PIRL/Desktop/logo.jpg", IMREAD_GRAYSCALE);
	CV_Assert(logo.data);

	Mat hist_img[2], c_projection, r_projection;

	reduce(logo, c_projection, 0, REDUCE_AVG);
	reduce(logo, r_projection, 1, REDUCE_AVG);
	cDraw_Histo(c_projection, hist_img[0]);
	imshow("c_chist_img", hist_img[0]);

	rDraw_Histo(r_projection, hist_img[1]);
	imshow("r_hist_img", hist_img[1]);
	waitKey();

}
int main() {
	test_main();
	//projection_main();
	//sharpening_main();
	return 0;
}
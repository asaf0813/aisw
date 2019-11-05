#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void print_matInfo(string name, Mat img) {
	string mat_type;
	if (img.depth() == CV_8U) mat_type = "CV_8U";
	else if (img.depth() == CV_8S) mat_type = "CV_8S";
	else if (img.depth() == CV_16U) mat_type = "CV_16U";
	else if (img.depth() == CV_16S) mat_type = "CV_16S";
	else if (img.depth() == CV_32S) mat_type = "CV_32S";
	else if (img.depth() == CV_32F) mat_type = "CV_32F";
	else if (img.depth() == CV_64F) mat_type = "CV_64F";

	cout << name << format(": depth(%d) channels(%d) -> data type : ", img.depth(), img.channels());
	cout << mat_type << "C" << img.channels() << endl;
}
int main() {

	string filename = "C:/Users/PIRL/Desktop/camp.jpg";
	Mat img = imread("C:/Users/PIRL/Desktop/camp.jpg", IMREAD_COLOR);
	CV_Assert(img.data);
	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);
	params_jpg.push_back(100);
	params_png.push_back(IMWRITE_PNG_COMPRESSION);
	params_png.push_back(0);

	imwrite("C:/Users/PIRL/Desktop/test.jpg", img, params_jpg);
	imwrite("C:/Users/PIRL/Desktop/test.png", img, params_png);

	Mat gray2gray = imread(filename, IMREAD_GRAYSCALE);
	Mat gray2color = imread(filename, IMREAD_COLOR);
	CV_Assert(gray2color.data && gray2color.data);

	Rect roi(100, 100, 1, 1);
	cout << "Matrix coordinate (100, 100) pixel value" << endl;
	cout << "gray2gray : " << gray2gray(roi) << endl;
	cout << "gray2color : " << gray2color(roi) << endl;

	print_matInfo("gray2gray", gray2gray);
	print_matInfo("gray2color", gray2color);
	imshow("gray2gray", gray2gray);
	imshow("gray2color", gray2color);

	waitKey(0);

	return 0;

}

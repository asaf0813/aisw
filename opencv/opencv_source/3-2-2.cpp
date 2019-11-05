#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void drawHist(const vector<int>& data, Mat3b& dst, int binSize = 1, int height = 0)
{
	int max_value = *max_element(data.begin(), data.end());  // 전체 vector 크기 결정
	int rows = 0; // row지만 세로라고 이해하면 편함
	int cols = 0; // column 이지만 가로라고 이해하면 편함
	if (height == 0) {
		rows = max_value + 10;
	}
	else {
		rows = max(max_value + 10, height); // 사실 row가 height라고 이해하면 됨.
	}

	cols = data.size() * binSize; // col 크기 --> 따라서 binsize가 커질수록 cols의 크기가 커지므로 그래프가 옆으로 늘어짐.

	dst = Mat3b(rows, cols, Vec3b(255, 255, 255)); // 흰색 도화지 만들기

	for (int i = 0; i < data.size(); ++i)
	{
		int h = rows - data[i];  // height에서 data[i]값을 빼준거임(시작 좌표 정의)
		rectangle(dst, Point(i * binSize, h), Point((i + 1) * binSize - 1, rows), Scalar(0, 0, 0), -1); // dst도화지 위에 네모바로 그리기
	}

}
int main() {
	Mat image = imread("C:/Users/PIRL/Desktop/logo.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat new_img_H, new_img_V;
	reduce(image, new_img_V, 1, REDUCE_AVG, CV_32S); // 단일 행으로 출력 --> 그래프는 세로로 출력
	vector<int> hist_V = new_img_V; //reduce로 만들어진 값을 hist_V에 넣음 
	Mat3b image_1; // 도화지 만들기
	drawHist(hist_V, image_1, 1, 308);

	reduce(image, new_img_H, 0, REDUCE_AVG, CV_32S); // 단일 열로 출력 --> 그래프는 가로로 출력
	vector<int> hist_H = new_img_H;
	Mat3b image_2; //

	drawHist(hist_H, image_2, 1, 308);
	flip(image_2, image_2, 1); // 좌우반전
	Point2f src_center(image_2.cols / 2.0F, image_2.rows / 2.0F); // 90도 회전하려면 자료형이 같아야 해서 자료형 맞춰주기
	Mat rot_mat = getRotationMatrix2D(src_center, 90, 1.0); // 자료형 맞춰서 90도 회전
	Mat dst;
	warpAffine(image_2, dst, rot_mat, image_2.size()); // rot_mat의 자료형을 다시 바꿔줘야 그림으로 출력됨

	imshow("Histogram_V", image_1);
	imshow("Histogram_H", dst);
	imshow("original", image);
	waitKey();
	return 0;
}

//int max = *max_element(hist.begin(), hist.end());
//cout << max << endl; // 크기의 최대값 찾기
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void drawHist(const vector<int>& data, Mat3b& dst, int binSize = 1, int height = 0)
{
	int max_value = *max_element(data.begin(), data.end());  // ��ü vector ũ�� ����
	int rows = 0; // row���� ���ζ�� �����ϸ� ����
	int cols = 0; // column ������ ���ζ�� �����ϸ� ����
	if (height == 0) {
		rows = max_value + 10;
	}
	else {
		rows = max(max_value + 10, height); // ��� row�� height��� �����ϸ� ��.
	}

	cols = data.size() * binSize; // col ũ�� --> ���� binsize�� Ŀ������ cols�� ũ�Ⱑ Ŀ���Ƿ� �׷����� ������ �þ���.

	dst = Mat3b(rows, cols, Vec3b(255, 255, 255)); // ��� ��ȭ�� �����

	for (int i = 0; i < data.size(); ++i)
	{
		int h = rows - data[i];  // height���� data[i]���� ���ذ���(���� ��ǥ ����)
		rectangle(dst, Point(i * binSize, h), Point((i + 1) * binSize - 1, rows), Scalar(0, 0, 0), -1); // dst��ȭ�� ���� �׸�ٷ� �׸���
	}

}
int main() {
	Mat image = imread("C:/Users/PIRL/Desktop/logo.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat new_img_H, new_img_V;
	reduce(image, new_img_V, 1, REDUCE_AVG, CV_32S); // ���� ������ ��� --> �׷����� ���η� ���
	vector<int> hist_V = new_img_V; //reduce�� ������� ���� hist_V�� ���� 
	Mat3b image_1; // ��ȭ�� �����
	drawHist(hist_V, image_1, 1, 308);

	reduce(image, new_img_H, 0, REDUCE_AVG, CV_32S); // ���� ���� ��� --> �׷����� ���η� ���
	vector<int> hist_H = new_img_H;
	Mat3b image_2; //

	drawHist(hist_H, image_2, 1, 308);
	flip(image_2, image_2, 1); // �¿����
	Point2f src_center(image_2.cols / 2.0F, image_2.rows / 2.0F); // 90�� ȸ���Ϸ��� �ڷ����� ���ƾ� �ؼ� �ڷ��� �����ֱ�
	Mat rot_mat = getRotationMatrix2D(src_center, 90, 1.0); // �ڷ��� ���缭 90�� ȸ��
	Mat dst;
	warpAffine(image_2, dst, rot_mat, image_2.size()); // rot_mat�� �ڷ����� �ٽ� �ٲ���� �׸����� ��µ�

	imshow("Histogram_V", image_1);
	imshow("Histogram_H", dst);
	imshow("original", image);
	waitKey();
	return 0;
}

//int max = *max_element(hist.begin(), hist.end());
//cout << max << endl; // ũ���� �ִ밪 ã��
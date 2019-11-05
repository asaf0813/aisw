#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(void) {
	FileStorage fs("C:/Users/PIRL/Desktop/test.xml", FileStorage::WRITE);
	string name = "배종욱";
	fs << "name" << name;
	fs << "age" << 20;
	fs << "university" << "창원대학교";

	fs << "hardware" << "{";
	fs << "cpu" << 25;
	fs << "mainboard" << 10;
	fs << "ram" << "}";

	int data[] = { 1,2,3,4,5,6 };
	vector <int> vec(data, data + sizeof(data) / sizeof(float));
	fs << "vector" << vec;
	Mat m(2, 3, CV_32S, data);
	fs << "Mat" << m;

	Point2d pt(10.5, 200);
	Rect rect(pt, Size(100, 200));
	fs << "point" << pt;
	fs << "Rect" << rect;
}


//time_t date;
//time(&date);
//
//fs << "Date" << asctime(localtime(&date));
//fs << "string" << "TEST"; // write as string
//fs << "integer" << 180; // write as int(eventually write string)
//
//// [ ] : 시퀀스 컬렉션
//fs << "collection_seq" << "[";
//fs << "sequence1" << "sequence2";
//fs << "sequence3" << "]"; // end of sequence collection
//
//// { } : 매핑 컬렉션
//fs << "collection_map" << "{";
//fs << "mapping1" << 100;
//fs << "mapping2" << "someString2";
//fs << "}"; // end of maaping collection

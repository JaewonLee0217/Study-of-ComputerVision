// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include <math.h>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main() {

	Mat image = imread("Lena_256x256.png");
	Mat image_gr;
	cvtColor(image, image, 7);
	double h_rate = 2.0;
	double w_rate = 2.0;

	int h = image.rows * h_rate;
	int w = image.cols * w_rate;

	Mat result_img(h, w, CV_8UC1, Scalar(0));

	for (int y = 0; y < result_img.rows - 1; y++) {
		for (int x = 0; x < result_img.cols - 1; x++) {
			int px = (int)(x / w_rate);
			int py = (int)(y / h_rate);

			if (px >= image.cols - 1 || py >= image.rows - 1) break;

			double fx1 = (double)x / (double)w_rate - (double)px;
			double fx2 = 1 - fx1;
			double fy1 = (double)y / (double)h_rate - (double)py;
			double fy2 = 1 - fy1;

			double w1 = fx2 * fy2;
			double w2 = fx1 * fy2;
			double w3 = fx2 * fy1;
			double w4 = fx1 * fy1;

			uchar p1 = image.at<uchar>(py, px);
			uchar p2 = image.at<uchar>(py, px + 1);
			uchar p3 = image.at<uchar>(py + 1, px);
			uchar p4 = image.at<uchar>(py + 1, px + 1);
			result_img.at<uchar>(y, x) = w1 * p1 + w2 * p2 + w3 * p3 + w4 * p4;
		}
	}

	/// Create Windows
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("result Image", WINDOW_AUTOSIZE);

	/// Show stuff
	imshow("Original Image", image);
	imshow("result Image", result_img);

	/// Wait until user press some key
	waitKey(0);
	return 0;
}
/*
#include "stdafx.h"
#include <math.h>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;
//임이의 x_size,y_size를 받았을 때 그 만큼 확대.
void BilinearInterpolation(Mat &in,Mat &out, int x_size, int y_size);
int main()
{
	Mat img_in,img_gr;

	// image 읽고 gray로 바꾸기
	img_in = imread("Lena_256x256.png");
	img_gr = img_in;
	//cvtColor(img_in, img_gr, COLOR_RGB2GRAY);
	//그레이 버전만 진행.
	
	int w = img_gr.cols;
	int h = img_gr.rows;
	int imgst = (img_gr.channels() == 1) ? CV_8UC1 : CV_8UC3;
	if (img_gr.empty())
	{
		printf("no image");
		return 0;
	}
	namedWindow("origin", WINDOW_AUTOSIZE);
	imshow("origin", img_gr);
	while (1)
	{
		int key = waitKey(50);
		if (key == '1') {
			w *= 1.1;
			h *= 1.1;
		}
		else if (key == '2') {
			w /= 1.1;
			h /= 1.1;
		}
		if (key == '1' || key == '2') 
		{
			Mat img_out(h, w, imgst,Scalar(0));
			//436x436, 512x512의 경우를 볼 것.
			BilinearInterpolation(img_gr, img_out, 512, 512);


			//namedWindow("img_out", WINDOW_AUTOSIZE);
			//원본과 interpolation한 부분 출력.

			imshow("img_out", img_out);
		}
		}
		//여까지 문제없고,
		
	
	
	//아무 키나 누르면 종료.
	//waitKey(0);
	//확대 영상 열고,
	return 0;
}
//임의의 값 x_size, y_size로 변환시키는 BilinearInterpolation함수.
void BilinearInterpolation(Mat &in,Mat &out, int x_size, int y_size)
{
	double rate = 0;
	int x = 0;//out의 너비
	int y = 0;//out의 높이

	//out의 이미지에서 원본 이미지 픽셀
	int row_image_x = 0;
	int row_image_y = 0;

	printf("높이: %d \n", y_size);
	printf("너비: %d \n", x_size);

	printf("변환된 높이: %d \n", y_size);
	printf("원본: %d \n", in.rows);
	rate = (double)y_size / (double)in.rows;

	printf("rate: %f\n", rate);
	printf("\n");
	

	
	//바뀐 이미지에서 원본 이미지와 대응되는픽셀 p1 rate만큼 확대했으니 rate만큼 나눔.


	for (int y = 0;y < out.rows;y++)
	{
		for (int x = 0;x < out.cols;x++)
		{
			//거리 비는 
			int px = (int)(x / rate);
			int py = (int)(y /rate);

			//if (px >= in.cols - 1 || py >= in.rows - 1) break;

			double fx1 = (double)x /(double)rate - (double)px;
			double fx2 = 1 - fx1;
			double fy1 = (double)y *(double)rate - (double)py;
			double fy2 = 1 - fy1;
			//Pn에 대한 가중치 계산
			double w1 = fx2 * fy2;
			double w2 = fx1 * fy2;
			double w3 = fx2 * fy1;
			double w4 = fx1 * fy1;
			if (in.channels() == 1) {
				//한 픽셀에 대헛 1만큼씩 차이가 나게 되므로 
				uchar P1 = in.at<uchar>(py, px);
				uchar P2 = in.at<uchar>(py, px + 1);
				uchar P3 = in.at<uchar>(py + 1, px);
				uchar P4 = in.at<uchar>(py + 1, px + 1);

				out.at<uchar>(y, x) = (w1 * P1) + (w2 * P2) + (w3 * P3) + (w4 * P4);
			}
			else if (in.channels() == 3) {
				Vec3b P1 = in.at<Vec3b>(py, px);
				Vec3b P2 = in.at<Vec3b>(py, px + 1);
				Vec3b P3 = in.at<Vec3b>(py + 1, px);
				Vec3b P4 = in.at<Vec3b>(py + 1, px + 1);

				out.at<Vec3b>(y, x) = (w1 * P1) + (w2 * P2) + (w3 * P3) + (w4 * P4);
			}

		}
	}
	
	
}
*/
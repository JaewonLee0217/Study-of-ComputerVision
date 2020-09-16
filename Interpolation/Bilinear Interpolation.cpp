// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <math.h>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main()
{
	Mat img_in;

	// image 읽고 gray로 바꾸기
	img_in = imread("Lena_256x256.png");
	cvtColor(img_in, img_in, COLOR_RGB2GRAY);
	imshow("원본256x256", img_in);
	//436x436, 512x512
	unsigned char* pData;
	pData = (unsigned char*)img_in.data;

	///////////////////// 처리하기 ///////////////////
	

	waitKey(0);

	return 0;
}
//임의의 값 x_size, y_size로 변환시키는 BilinearInterpolation함수.
void BilinearInterpolation(Mat& out, int x_size, int y_size)
{
	for (int y = 0;y < out.rows;y++)
	{
		for (int x = 0;x < out.cols;x++)
		{

		}
	}
}
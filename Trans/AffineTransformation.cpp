#include "opencv2//imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#define PI 3.14159265358979323846

using namespace cv;
using namespace std;

int main()
{
	//이미지 로드
	Mat src = imread("lena.jpg");
	
	//affine transform을 위해 3개의 점을 설정
	Point2f srcTri[3];
	srcTri[0] = Point2f(10.f, 30.f);
	srcTri[1] = Point2f(src.cols - 1.f, 0.f);
	srcTri[2] = Point2f(20.f, src.rows - 1.f);

	Point2f dstTri[3];
	dstTri[0] = Point2f(50.f, src.rows * 0.33f);
	dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
	dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);

	//affineTransform함수 불러와서
	Mat warp_mat = getAffineTransform(srcTri, dstTri);

	//dst이미지를 src와 타입과 사이즈를 동일하게 설정
	Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	//Rotating the image after warp
	//이미지의 센터를 기준으로 회전 행렬을 적용하여 계산
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	//getRotationMatrix2D
	Mat rot_mat = getRotationMatrix2D(center, angle, scale);

	//Rotate the warped image
	Mat warp_rotate_dst;
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
	
	imshow("Source image", src);
	
	imshow("Warp", warp_dst);
	imshow("Warp+Rotate", warp_rotate_dst);
	waitKey(0);

	return 0;
	
}
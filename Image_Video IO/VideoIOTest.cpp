/*#include <opencv2/opencv.hpp>

using namespace cv;

void main()
{
	VideoCapture capture("video.mp4");

	Mat Frame;
	if (!capture.isOpened())
	{
		printf("Video file can not open \n");
		return;
	}

	namedWindow("video");

	while (1) {
		capture >> Frame;//ĸó�� ���� �������� Mat�� ����.

		if (Frame.empty())
			break;

		imshow("video", Frame);
		if (waitKey(10) > 0)
			break;
	}
}
*/
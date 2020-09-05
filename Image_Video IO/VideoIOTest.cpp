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
		capture >> Frame;//캡처한 비디오 프레임을 Mat에 저장.

		if (Frame.empty())
			break;

		imshow("video", Frame);
		if (waitKey(10) > 0)
			break;
	}
}
*/
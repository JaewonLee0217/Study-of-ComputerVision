#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

void main()
{
	VideoCapture capture("Test321count.mp4");

	Mat frame;

	if (!capture.isOpened())
	{
		printf("video file cannot open\n");
		return;
	}

	VideoWriter writer;

	vector<Mat> video;

	writer.open("Reverse321count.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, Size(1920, 1080), true);

	while (1)
	{
		Mat frame;
		capture >> frame;
		if (frame.empty())
			break;

		video.push_back(frame);
	}
	for (int i = 0;i < video.size();i++)
		writer.write(video[video.size() - (i + 1)]);
}
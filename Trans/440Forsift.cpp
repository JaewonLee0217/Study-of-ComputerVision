//Dog 연산?
//본래 scale space를 구한 후 Laplacian of Gaussian (LoG)를 통해 Keypoint를 찾을 수 있다
//그러나 LoG는 많은 연산을 필요로 해서 비교서 간단한 Diffterence of Gaussian(DoG)방법을 사용

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

int main()
{
    //비교할 두 이미지 image1, image2 정의
    Mat img1 = imread("DetectImage/image1.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("DetectImage/image2.jpg", IMREAD_GRAYSCALE);
   
    //keypoint와 descriptor pointer 선언.
    Ptr<Feature2D> backend;
    Ptr<DescriptorMatcher> matcher;

    matcher = DescriptorMatcher::create("FlannBased");
    //매칭된 키포인트를 그려줄 최대 직선 개수 
    int maxlines = 100;

    //SIFT::create()함수로 keypoint와 descriptor를 가리키는 ext선언.
    Ptr<SIFT> ext = SIFT::create();

    //각 이미지에 대한 KeyPoints
    vector<KeyPoint> kp1, kp2;

    //각 이지미에 대한 descriptors
    Mat desc1, desc2;

    //detectAndCompute를 통해 각 이미지의 keypoint와 descriptor추출.
    ext->detectAndCompute(img1, Mat(), kp1, desc1);
    ext->detectAndCompute(img2, Mat(), kp2, desc2);

    //keyPoint및 decriptor를 뽑아냈으면 매칭 시작.
    vector< vector<DMatch> > rawMatches;
    vector<Point2f> p1, p2;
    vector<float> distances;

    //유사도가 높은 keypoint쌍들을 찾은 결과들이 rawMatches에 저장.
    matcher->knnMatch(desc1, desc2, rawMatches, 2);

    // filter_matches
    for (size_t i = 0; i < rawMatches.size(); i++)
    {
        const vector<DMatch>& m = rawMatches[i];
        if (m.size() == 2 && m[0].distance < m[1].distance * 0.75)
        {
            //기준이 되는 Keypoint의 index를 p1에 넣음.
            p1.push_back(kp1[m[0].queryIdx].pt);

            //매칭된 desciptor의 index를 p2에 넣음.
            p2.push_back(kp2[m[0].trainIdx].pt);

            //매칭된 사이의 거리 즉, 유사도를 distances에 넣음.
            distances.push_back(m[0].distance);
        }
    }
    vector<uchar> status;
    //백터 쌍으로 만들어 줄 것.
    vector< pair<Point2f, Point2f> > pointPairs;
   // p1, p2사이의 호모그래피를 찾고, 상태를 status에 저장.
    Mat H = findHomography(p1, p2, status, RANSAC);
    int inliers = 0;
    for (size_t i = 0; i < status.size(); i++)
    {
        if (status[i])
            //일치하면
        {
            //p1,p2를 쌍으로 만들어서 pointPairs벡터에 push_back해준다.
            pointPairs.push_back(make_pair(p1[i], p2[i]));
            //앞에서 만들어둔 distances를 바꿔준다.
            distances[inliers] = distances[i];
            inliers++;
        }
    }
    //일치한 크기만큼 distances사이즈를 조정해준다.
    distances.resize(inliers);


    
    //인트형 벡터로 정의
    vector<int> indices(inliers);
    //행렬 요소들을 정렬시켜준다.
    sortIdx(distances, indices, SORT_EVERY_ROW + SORT_ASCENDING);

    // 출력될 이미지 사이즈 정의.
    int h1 = img1.size().height;
    int w1 = img1.size().width;
    int h2 = img2.size().height;
    int w2 = img2.size().width;
    Mat vis = Mat::zeros(max(h1, h2), w1 + w2, CV_8U);
    img1.copyTo(Mat(vis, Rect(0, 0, w1, h1)));
    img2.copyTo(Mat(vis, Rect(w1, 0, w2, h2)));
    //vis이미지를 RGB로 바꿔준다.
    cvtColor(vis, vis, COLOR_GRAY2BGR);

    //코너에 대한 포인터정의.
    vector<Point2f> corners(4);
    corners[0] = Point2f(0, 0);
    corners[1] = Point2f((float)w1, 0);
    corners[2] = Point2f((float)w1, (float)h1);
    corners[3] = Point2f(0, (float)h1);
    //int형 포인터벡터 icorners
    vector<Point2i> icorners;
    // 3D벡터 변환
    perspectiveTransform(corners, corners, H);
    transform(corners, corners, Matx23f(1, 0, (float)w1, 0, 1, 0));
    //float to int변환
    Mat(corners).convertTo(icorners, CV_32S);
    //코너에 대한 다각형 곡선을 흰색으로 그려준다.
    polylines(vis, icorners, true, Scalar(255, 255, 255));

    //매칭되는 지점에 녹색 circle과 line으로 표시.
    for (int i = 0; i < min(inliers, maxlines); i++)
    {
        int idx = indices[i];
        //pointPairs의 처음과 끝을 잡아주고
        const Point2f& pi1 = pointPairs[idx].first;
        const Point2f& pi2 = pointPairs[idx].second;
        //두 포인터를 녹색 원으로 표시해준다.
        circle(vis, pi1, 2, Scalar(0, 255, 0), -1);
        circle(vis, pi2 + Point2f((float)w1, 0), 2, Scalar(0, 255, 0), -1);
        //표시한 두 포인터를 직선으로 그려 이미지에 그려준다.
        line(vis, pi1, pi2 + Point2f((float)w1, 0), Scalar(0, 255, 0));
    }
    //결과 화면 vis출력.
    imshow("result", vis);
    waitKey();  
    return 0;
}
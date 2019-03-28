#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "car_control.h"
#include "lane_detect.h"
using namespace cv;

class TrafficSign
{
#pragma region static var
	static int iHighH;
	static int iLowH;
	static int iHighL;
	static int iLowL;
	static int iHighS;
	static int iLowS;
	static int CountFrame;
	static const int MinSquare; // 200 pixel - That is a size that use for identifi sign
	static const int LockFlag; // 10 frame - after 10 frame detect a same sign, lock that result and stop detect
	static const int UnlockFlag; // ~2s
	static bool flag;
	static int OldSign;

	static const int SkyLine; // line x=SkyLine use for cut image
	static const int LeftLine; // Line y=LeftLine use for cut image
public:
	static int Sign; // -1 is turn left; 1 is turn right; 0 is nothing
#pragma endregion
public:
	void Setting();
	int Find(const Mat &src);
private:
	Mat PreFix(const Mat &src); // return a matrix Threshold for detection
	Mat ThresholdDetection(Mat &draw, const Mat &Thres); // return a matrix what is most likely a traffic sign
	int CheckSign(const Mat &src); // return 0 if none sign, -1 if turn left, 1 if turn right
};
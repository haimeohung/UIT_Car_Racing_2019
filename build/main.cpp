#include <opencv2/opencv.hpp>
#include <iostream>
#include "setting.h"
using namespace std;
using namespace cv;
CarControl *car;
LaneDetect *detect;
TrafficSign *sign;
void call_back()
{
	
	cv::Mat out;
	cv::Mat out2;
	cv::Mat out3;
	cv::Rect ros;
	try
	{
		out = LaneDetect::draw;
	
		resize(out, out2, Size(205, 154), 0, 0);
		resize(out2, out3, Size(320, 240), 0, 0);
		detect->Detect(out3);
		detect->DrawLane();
		car->driverCar(out3);
		imshow("View", LaneDetect::draw);
		waitKey(30);
	}
	catch (Exception e)
	{
	}
}

int main(int, char** argv)
{
	Mat src;
	detect = new LaneDetect();
	car = new CarControl();

	while (true)
	{
		try
		{
			LaneDetect::draw = imread("C:\\Users\\Admin\\Downloads\\Unity_UITCar-master\\Unity_UITCar-master\\Window\\window_version_Data\\Snapshots\\fx_UIT_Car.png");
			//src.resize((240, 320));
			imshow("camera", LaneDetect::draw);
			//detect->Detect(LaneDetect::draw);
			call_back();
			waitKey(30);
		}
		catch (Exception){

		}
	}
		

	
	return 0;
}
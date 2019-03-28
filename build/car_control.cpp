#include "car_control.h"
float static_speed_unity;
CarControl::CarControl()
{
	
}
CarControl::~CarControl() {}
void sleep(int milliseconds)
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{

	}
}
void CarControl::get_speed_unity(float speed_unity)
{
	static_speed_unity = speed_unity;
	cout << speed_unity << endl;
}
void CarControl::driverCar(Mat & out)
{
	int velocity;

	double angle_info;

	// TrafficSign *F ;
	// if (F->Find(out) == -1)
	// {
		// angle_info = -45;
	// }
	// else if (F->Find(out) == 1)
	// {
		// angle_info = 45;
	// }
	// else
	// {
	angle_info = CarControl::GetAngle();
	//}
	velocity = CarControl::GetSpeed(angle_info);

	//cv::imshow("sign", out);

	

}

void CarControl::UpdateSizeLane(int NewSizeLane)
{
	SizeLane = SizeLane * (1 - Alpha) + NewSizeLane * Alpha;
}

double CarControl::Fx(int x)
{
	return FxSize_a * x + FxSize_b;
}

double CarControl::ReduceAngle(const double & angle)
{
	return (CarControl::OldAngle*0.8 + angle * 0.2)*0.8;
}

double CarControl::GetAngle()
{
	Line res;
	LineFunction F;
	LaneDetect L;
	ObjectDetect O;
	O.ClearObject();
	L.DrawLane();
	// Lost lane, kept old angle
	if (LaneDetect::LaneL.size() + LaneDetect::LaneR.size() < (LaneDetect::TooFew << 1))
		return OldAngle;
	// Lost left lane, follow right lane
	if (LaneDetect::LaneL.size() < LaneDetect::TooFew)
	{
		res = ObjectDetect::laneR;
		OldAngle = F.Angle(CarLocation, Point(F.ReturnX(res, LineDetect) - (SizeLane >> 1), LineDetect));
		line(LaneDetect::draw, CarLocation, Point(F.ReturnX(res, LineDetect) - (SizeLane >> 1), LineDetect + LaneDetect::SkyLine), Scalar(0, 0, 255));
		return OldAngle;
	}
	// Lost right lane, follow left lane
	if (LaneDetect::LaneR.size() < LaneDetect::TooFew)
	{
		res = ObjectDetect::laneL;
		OldAngle = F.Angle(CarLocation, Point(F.ReturnX(res, LineDetect) + (SizeLane >> 1), LineDetect));
		line(LaneDetect::draw, CarLocation, Point(F.ReturnX(res, LineDetect) + (SizeLane >> 1), LineDetect + LaneDetect::SkyLine), Scalar(0, 0, 255));
		return OldAngle;
	}
	// no lost lane
	L.UpdateMidLane();
	res = F.Linear(LaneDetect::LaneM);
	int delta = CarLocation.x - F.ReturnX(res, CarLocation.y);
	if (F.Angle(res) > 0)
	{
		if (delta < -7)
		{
			//delta/=2;
		}
		else
		{
			delta = 0;
		}
	}
	else
	{
		if (delta > 7)
		{
			//delta/=2;
		}
		else
		{
			delta = 0;
		}
	}
	if (TrafficSign::Sign == 0)
		UpdateSizeLane(F.ReturnX(ObjectDetect::laneL, LineDetect) + F.ReturnX(ObjectDetect::laneR, LineDetect) >> 1);
	OldAngle = ReduceAngle(F.Angle(CarLocation, Point(F.ReturnX(res, LineDetect) - delta, LineDetect + LaneDetect::SkyLine)));
	// draw

	line(LaneDetect::draw, Point(F.ReturnX(res, 0), LaneDetect::SkyLine), Point(F.ReturnX(res, 160), 160 + LaneDetect::SkyLine), Scalar(255, 255, 255));
	line(LaneDetect::draw, CarLocation, Point(F.ReturnX(res, LineDetect) - delta, LineDetect + LaneDetect::SkyLine), Scalar(0, 0, 255));

	return OldAngle;
}

int CarControl::GetSpeed(const double & angle)
{
	int res = MaxSpeed - abs(angle);
	return res < MinSpeed ? MinSpeed : res;
}
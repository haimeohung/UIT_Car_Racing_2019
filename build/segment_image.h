#pragma once
#include <iostream>
#include <omp.h>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"
#include <vector>
using namespace std;
using namespace cv;

class segment_image
{
public:
	segment_image();
	~segment_image();
	float weight(int p1[], int p2[]);
	int root(vector <int> &Arr, int i);

};


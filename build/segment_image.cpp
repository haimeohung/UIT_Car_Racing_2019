#include "segment_image.h"



segment_image::segment_image()
{
}


segment_image::~segment_image()
{
}


float segment_image::weight(int p1[], int p2[])
{
	float weight = (p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]) + (p1[2] - p2[2])*(p1[2] - p2[2]);
	weight = sqrt(weight);
	return weight;
}
int segment_image::root(vector <int> &Arr, int i)
{
	while (Arr[i] != i)
	{
		Arr[i] = Arr[Arr[i]];
		i = Arr[i];
	}
	return i;
}

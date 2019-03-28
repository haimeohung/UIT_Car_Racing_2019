#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img, img2;
	img = imread("bongcay.png");
	img2 = imread("da.png");
	imshow("Meanshift", e(img));
	imshow("Meanshift2", e(img2));

	waitKey();

	return 0;
}
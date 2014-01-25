#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
using namespace cv;
class Thresholding
{
public:
	static IplImage* shapeRamesh(IplImage *image);
	static IplImage* findPath(IplImage *image,IplImage *dst);
	static IplImage* adaptiveThreshMean(IplImage *image);
	static IplImage* adaptiveThreshGaussian(IplImage *image);
	static IplImage* Thresh(IplImage *image,int threshold);
	static IplImage* hsvConvert(IplImage *image);
	vector<Rect> *findRect(IplImage *image,vector<Rect> *vecR);
	int FindObjects(IplImage *image,vector<Rect> *objects);
};
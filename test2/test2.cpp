#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "FindObj.h"
#include "Otsu.h"

using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	IplImage *image = cvLoadImage( "1.jpg" ,1);
	IplImage *image2=cvCloneImage(image);
	IplImage *image3=cvCloneImage(image);
	IplImage *image4=cvCloneImage(image);
	IplImage *image5=cvCloneImage(image);
	IplImage *dst,*gray,*dst1;
	Thresholding *fo=new Thresholding();
	/*cvMorphologyEx(image,image2,NULL,0,CV_MOP_OPEN,1);
	cvMorphologyEx(image,image3,NULL,0,CV_MOP_CLOSE,1);
	cvMorphologyEx(image,image4,image5,0,CV_MOP_GRADIENT,1);
	dst=Thresholding::shapeRamesh(image);
	image=Thresholding::findPath(image,dst);
	cvShowImage( "image",image );
	dst=Thresholding::shapeRamesh(image2);
	image2=Thresholding::findPath(image2,dst);
	cvShowImage( "image2",image2 );

	dst=Thresholding::shapeRamesh(image3);
	image3=Thresholding::findPath(image3,dst);
	cvShowImage( "image3",image3 );

	dst=Thresholding::shapeRamesh(image4);
	image4=Thresholding::findPath(image4,dst);
	cvShowImage( "image4",image4 );
	/*dst=Thresholding::adaptiveThreshMean(image2);
	image2=Thresholding::findPath(image2,dst);
	cvShowImage( "image2",image2 );
	dst=Thresholding::adaptiveThreshGaussian(image3);
	image3=Thresholding::findPath(image3,dst);
	cvShowImage( "image3",image3 );
	int h=otsuThreshold(image4->imageData,image4->nSize);
	dst=Thresholding::Thresh(image4,abs(h));
	image4=Thresholding::findPath(image4,dst);
	cvShowImage( "image4",image4 );*/
	
	//cvDilate(image2,image2,NULL,1); //дилатация
	/*gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	dst1 = cvCreateImage(cvGetSize(image), image->depth, 1);
	cvConvertImage(image, gray, 0);
	cvCanny(gray,  dst1,300,250,3);
	dst=Thresholding::shapeRamesh(image);
	image=Thresholding::findPath(image,dst);
	cvShowImage( "image",image );
	dst=Thresholding::shapeRamesh(dst1);
	image2=Thresholding::findPath(image2,dst1);
	cvShowImage("image2",image2);*/
//	image=Thresholding::findPath(image,h_plane);
	//cvShowImage( "image",image );
	vector<Rect> *objects=new vector<Rect>();
	fo->FindObjects(image,objects);
	waitKey( 0 );
	return 0;
}


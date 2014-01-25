#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "FindObj.h"
IplImage* Thresholding::shapeRamesh(IplImage *image)
{
	//переход к серому изображению
	IplImage *gray=0,*dst=0;
	gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	dst = cvCreateImage( cvGetSize(gray), IPL_DEPTH_8U, 1);
    cvConvertImage(image, gray, 0);
	//создание гистограммы
	CvHistogram* hist;
	int hist_size = 256;
	float range_0[]={0,256};
	float* ranges[] = { range_0 };
	hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	cvCalcHist( &gray, hist, 0, NULL );
	//поиск оптимального порога
	double p[256],mm[256],P=0,mf=0;
	for(int i=0;i<256;i++)
	{
		p[i]=(*cvGetHistValue_1D(hist,i))/(gray->width*gray->height);
	}
	
	for(int i=0;i<256;i++)
	{
		mm[i]=i*p[i];
	}
	
	double mb=0,b1=0,b2=0;
	int k=0;
	double f[256],tt[256];
	for(int i=0;i<256;i++)
	{
		for(int l=0;l<i+1;l++)
		{
			P = P+ p[l];
			mf = mf +mm[l];
		}
		if (i<255)
		{
			
			for(int m=i+2;m<255;m++)
				mb+=mm[m];
		}
		else
		{
			mb=0;
		}
		if (P!=0.0&&P!=1.0)
		{
			b1 = mf/P; 
			b2 = mb/(1-P);
			P=0;
			mf=0;
			mb=0;
			f[k]=0;
			for(int j=0;j<256;j++)
			{
				if(j<=i)
					f[k]=f[k]+(b1-j)*(b1-j);
				else
					if(j>=i+1)
						f[k]=f[k]+(b2-j)*(b2-j);
			}
		tt[k]=i;
		k++;
		}
	}
	double min=f[0];
	int minX=0;;
	for (int r=0;r<k;r++)
	{
		if(f[r]<min) 
		{
			min=f[r];
			minX=r;
		}
	}
	if (minX>=0)
	{
	int T=tt[minX];
	//порогова€ обработка
	cvThreshold(gray, dst, T, 255, CV_THRESH_BINARY);
	}
	//cvShowImage("dst",dst);
	/*//вывод гистограммы
	int bin_w;
	IplImage *hist_image = cvCreateImage(cvSize(320,200), 8, 1);
	bin_w = cvRound((double)hist_image->width/hist_size); 
	cvSet( hist_image, cvScalarAll(255), 0 );
	for(int i = 0; i < hist_size; i++ )
	cvRectangle( hist_image, cvPoint(i*bin_w, hist_image->height), cvPoint((i+1)*bin_w, hist_image->height -cvRound(cvGetReal1D(hist->bins,i))),cvScalarAll(0), -1, 8, 0 );
 

	cvShowImage( "histogram", hist_image );*/
	
	//возвращаем обработанное изображение
return dst;
}
IplImage* Thresholding::findPath(IplImage *image, IplImage *dst)
{
	int minRectDim = (image->height*image->width)/30000;//макс и мин размеры объектов
	int maxRectDim = (image->height*image->width)/3000; 
	for (int y=0; y<image->height; y++) 
	{
		uchar* ptr = (uchar*) (dst->imageData + y * dst->widthStep); // ѕолучаем указатель на начало строки 'y'
		for (int x=0; x<image->width; x++) 
			{
				if (ptr[x]<=30&&ptr[x]>=0||ptr[x]<=255&&ptr[x]>=230) {
				//если значение - 255, то заливаем//значением 200
				 CvConnectedComp comp;
				cvFloodFill( dst, cvPoint( x, y ), cvScalar( 200 ),cvScalarAll(5),cvScalarAll(5),&comp,CV_FLOODFILL_FIXED_RANGE + 8,0);
			if ( comp.rect.width >= minRectDim && comp.rect.width <= maxRectDim&& comp.rect.height >= minRectDim && comp.rect.height <= maxRectDim )
			{
				//центр
				int x = comp.rect.x ;
				int y = comp.rect.y;//радиус
				//рисуем окружность толщиной 2 пиксела
				cvRectangle( image, Point( x, y ), Point( x+comp.rect.width , y+comp.rect.height ), Scalar( 255, 0, 255 ), 1 );
			}
		}}}

	return image;
}
IplImage* Thresholding::adaptiveThreshMean(IplImage *image)
{
	IplImage *gray=0,*dst=0;
	gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	dst = cvCreateImage( cvGetSize(gray), IPL_DEPTH_8U, 1);
	cvConvertImage(image, gray, CV_BGR2GRAY);
	cvAdaptiveThreshold(gray,dst , 255, CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY ,3,5);
	cvShowImage("dst2",dst);
	return dst;
}
IplImage* Thresholding::adaptiveThreshGaussian(IplImage *image)
{
	IplImage *gray=0,*dst=0;
	gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	dst = cvCreateImage( cvGetSize(gray), IPL_DEPTH_8U, 1);
	cvConvertImage(image, gray, CV_BGR2GRAY);
	cvAdaptiveThreshold(gray,dst , 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY ,3,5);
	cvShowImage("dst3",dst);
	return dst;
}
IplImage* Thresholding::Thresh(IplImage *image,int threshold)
{
	IplImage *gray=0,*dst=0;
	gray = cvCreateImage(cvGetSize(image), image->depth, 1);
	dst = cvCreateImage( cvGetSize(gray), IPL_DEPTH_8U, 1);
	cvConvertImage(image, gray, CV_BGR2GRAY);
	cvThreshold(gray,dst , threshold,255,CV_THRESH_BINARY);
	cvShowImage("dst4",dst);
	return dst;
}
IplImage* Thresholding::hsvConvert(IplImage *image)
{
	IplImage* hsv = cvCreateImage( cvGetSize(image), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(image), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(image), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(image), 8, 1 );
	cvCvtColor( image, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
	return h_plane;
}
vector<Rect> * Thresholding::findRect(IplImage *image,vector<Rect> *vecR)
{

	int minRectDim = (image->height*image->width)/30000;//макс и мин размеры объектов
	int maxRectDim = (image->height*image->width)/3000; 
	for (int y=0; y<image->height; y++) 
	{
		uchar* ptr = (uchar*) (image->imageData + y * image->widthStep); // ѕолучаем указатель на начало строки 'y'
		for (int x=0; x<image->width; x++) 
			{
				if (ptr[x]<=30&&ptr[x]>=0||ptr[x]<=255&&ptr[x]>=230) {
				//если значение - 255, то заливаем//значением 200
					CvConnectedComp comp;
					cvFloodFill( image, cvPoint( x, y ), cvScalar( 200 ),cvScalarAll(5),cvScalarAll(5),&comp,CV_FLOODFILL_FIXED_RANGE + 8,0);
					if ( comp.rect.width >= minRectDim && comp.rect.width <= maxRectDim&& comp.rect.height >= minRectDim && comp.rect.height <= maxRectDim )
						vecR->insert(vecR->end(),comp.rect);
				}
			}
	}
	return vecR;
}
int Thresholding::FindObjects(IplImage *image,vector<Rect> *objects)
{
	Rect *shapeRam,*hsv,*dillat;
	IplImage *image1=cvCloneImage(image);//ShapeRamesh без доп. обработки
	IplImage *image2=cvCloneImage(image);//ѕеревод в пространство HSV
	IplImage *image3=cvCloneImage(image);//ƒилатаци€ с последующей обработкой ShapeRamesh
	IplImage *image4=cvCloneImage(image);//ћорфологическа€ операци€ открытие с последующей обработкой ShapeRamesh
	IplImage *image5=cvCloneImage(image);//ћорфологическа€ операци€ закрытие с последующей обработкой ShapeRamesh
	image1=Thresholding::shapeRamesh(image);
	image2=hsvConvert(image);
	cvDilate(image3,image3,NULL,1); //дилатаци€
	image3=Thresholding::shapeRamesh(image3);
	cvMorphologyEx(image,image4,NULL,0,CV_MOP_OPEN,1);
	image4=Thresholding::shapeRamesh(image4);
	cvMorphologyEx(image,image5,NULL,0,CV_MOP_CLOSE,1);
	image5=Thresholding::shapeRamesh(image5);
	objects=this->findRect(image1,objects);
	//cvShowImage( "image1",image1 );
	//cvShowImage( "image2",image2 );
	//cvShowImage( "image3",image3 );
	//cvShowImage( "image4",image4 );
	//cvShowImage( "image5",image5 );
	
return 1;
}
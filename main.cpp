#include<opencv.hpp>
#include <iostream>
#include "facedetect-dll.h"
#include <stdio.h>

//#pragma comment(lib,"libfacedetect.lib")
#pragma comment(lib,"libfacedetect-x64.lib")

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
	
	char filename[100];
	char facefolder[100];
	Mat image;
	Mat gray;
	
	for (unsigned int i = 29589; i < 30010; i++)
	{

		sprintf(filename, "C:/Users/ZBY/Desktop/112_1/%d.jpg", i);
		//sprintf(facefolder, "C:/Users/ZBY/Desktop/faces/%d/", i);
		image = imread(filename, CV_LOAD_IMAGE_UNCHANGED);//导入图片
		//imshow("image", imag);
		//waitKey(0);
		//其他的操作
		//...
		//Mat image = imread(argv[1]);


		//load an image and convert it to gray (single-channel)

		// = imread("lena.png", CV_LOAD_IMAGE_GRAYSCALE);
		cvtColor(image, gray, CV_BGR2GRAY);
		if (gray.empty())
		{
			fprintf(stderr, "Can not load the image file.\n");
			return -1;
		}
		/*
		//Mat image = imread("C:/Users/ZBY/Desktop/test2/1.jpg", CV_LOAD_IMAGE_UNCHANGED);
		//在MyWindow的窗中中显示存储在img中的图片
		imshow("Results_frontal", image);
		//等待直到有键按下
		waitKey(0);
		//销毁MyWindow的窗口
		destroyWindow("Results_frontal");
	
		return 0;
		*/
		
		//Mat gray = imread("C:/Users/ZBY/Desktop/test2/1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		int * pResults = NULL;

		///////////////////////////////////////////
		// frontal face detection 
		// it's fast, but cannot detect side view faces
		//////////////////////////////////////////
		//!!! The input image must be a gray one (single-channel)
		//!!! DO NOT RELEASE pResults !!!
		pResults = facedetect_frontal((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
			1.2f, 3, 24);
		printf("%d frontal faces detected.\n", (pResults ? *pResults : 0));
		//print the detection results
		Mat result_frontal = image.clone();
		for (int j = 0; j < (pResults ? *pResults : 0); j++)
		{
			short * p = ((short*)(pResults + 1)) + 6 * j;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];

			printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x, y, w, h, neighbors);
			rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
			Rect rect(x, y, w, h);
			Mat image_roi = image(rect);
			sprintf(facefolder, "C:/Users/ZBY/Desktop/faces/%d_%d.jpg", i,j);
			
			imwrite( facefolder , image_roi);//riFrame为当前帧
		}
		
		//imshow("Results_frontal", result_frontal);
		//等待直到有键按下
		//waitKey(0);
		//销毁MyWindow的窗口
		//destroyWindow("Results_frontal");
	}
	return 0;
}

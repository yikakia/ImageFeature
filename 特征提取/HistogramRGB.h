#pragma once
//计算图像RGB空间的颜色直方图
#include <opencv2\opencv.hpp>  
#include <iostream>  
#include <fstream>
using namespace std;
using namespace cv;

class HistogramRGB {
private:
	Mat image;//源图像  
	int hisSize[1], hisWidth, hisHeight;//直方图的大小,宽度和高度  
	float range[2];//直方图取值范围  
	const float* ranges;
	Mat channelsRGB[3];//分离的BGR通道  
	MatND outputRGB[3];//输出直方图分量  
	string outputfilename;//输出文件的名字
public:
	HistogramRGB() {
		hisSize[0] = 256;
		hisWidth = 400;
		hisHeight = 400;
		range[0] = 0.0;
		range[1] = 255.0;
		ranges = &range[0];
		outputfilename = "HistogramRGB.txt";
	}

	//导入图片  
	bool importImage(String path);

	//分离通道  
	void splitChannels();

	//计算直方图  
	void getHistogram();

	//显示直方图  
	void displayHisttogram();

	//设置输出文件名
	void setOutputFileName(string str);
};
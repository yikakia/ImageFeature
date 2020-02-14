#pragma once
//计算图像的颜色矩
#include <opencv2\opencv.hpp>  
#include <opencv2/core/core_c.h>
#include <iostream>  
#include <fstream>
using namespace std;
using namespace cv;

class ColorMom
{
private:
	Mat image;//源图像
	Mat hsvimg;//hsv图像
	Mat channelsBGR[3];//分离的BGR通道  
	double cal3orderMom(Mat& channel);	// 计算三阶矩
public:
	double* Mom;//颜色矩数组
	ColorMom() {
		Mom = new double[9];
	}
	//导入图片  
	bool importImage(String path);

	//分离通道
	void splitChannels();

	//计算颜色矩
	void calColorMom();
};


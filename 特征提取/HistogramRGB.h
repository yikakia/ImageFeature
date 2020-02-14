#pragma once
//����ͼ��RGB�ռ����ɫֱ��ͼ
#include <opencv2\opencv.hpp>  
#include <iostream>  
#include <fstream>
using namespace std;
using namespace cv;

class HistogramRGB {
private:
	Mat image;//Դͼ��  
	int hisSize[1], hisWidth, hisHeight;//ֱ��ͼ�Ĵ�С,��Ⱥ͸߶�  
	float range[2];//ֱ��ͼȡֵ��Χ  
	const float* ranges;
	Mat channelsRGB[3];//�����BGRͨ��  
	MatND outputRGB[3];//���ֱ��ͼ����  
	string outputfilename;//����ļ�������
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

	//����ͼƬ  
	bool importImage(String path);

	//����ͨ��  
	void splitChannels();

	//����ֱ��ͼ  
	void getHistogram();

	//��ʾֱ��ͼ  
	void displayHisttogram();

	//��������ļ���
	void setOutputFileName(string str);
};
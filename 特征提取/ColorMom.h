#pragma once
//����ͼ�����ɫ��
#include <opencv2\opencv.hpp>  
#include <opencv2/core/core_c.h>
#include <iostream>  
#include <fstream>
using namespace std;
using namespace cv;

class ColorMom
{
private:
	Mat image;//Դͼ��
	Mat hsvimg;//hsvͼ��
	Mat channelsBGR[3];//�����BGRͨ��  
	double cal3orderMom(Mat& channel);	// �������׾�
public:
	double* Mom;//��ɫ������
	ColorMom() {
		Mom = new double[9];
	}
	//����ͼƬ  
	bool importImage(String path);

	//����ͨ��
	void splitChannels();

	//������ɫ��
	void calColorMom();
};


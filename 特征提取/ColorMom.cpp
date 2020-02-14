#include "ColorMom.h"

//����ͼƬ
bool ColorMom::importImage(String path)
{
	image = imread(path);
	if (!image.data)
		return false;
	if (image.channels() != 3) {
		cout << "���󣬴�ͼ����Ҫ������ɫ��ͼ��" << endl;
	}
	return true;
}


//����ͨ��
void ColorMom::splitChannels()
{
	//channelsBGR[0] = new Mat(image.rows, image.cols, CV_8U);
	//channelsBGR[1] = new Mat(image.rows, image.cols, CV_8U);
	//channelsBGR[2] = new Mat(image.rows, image.cols, CV_8U);
	//
	split(image, channelsBGR);
}


// �������׾�
double ColorMom::cal3orderMom(Mat& channel)
{
	uchar* p;
	double mom = 0;
	double avg = mean(channel)[0];//���㵥ͨ��ͼ��ľ�ֵ
	int nRows = channel.rows;
	int nCols = channel.cols;
	if (channel.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; ++i) {
		p = channel.ptr<uchar>(i);
		for (int  j = 0; j < nCols; j++)
		{
			mom += pow((p[j] - avg), 3);
		}
	}
	float temp;
	temp = cvCbrt((float)(mom / ((float)nRows * (float)nCols)));
	mom = (double)temp;
	//���ֵ��������
	return mom;
}


//������ɫ��
void ColorMom::calColorMom()
{
	Mat tmp_m, tmp_sd;
	//����Bͨ������ɫ��
	meanStdDev(channelsBGR[0], tmp_m, tmp_sd);
	Mom[0] = tmp_m.at<double>(0.0);
	Mom[3] = tmp_sd.at<double>(0, 0);
	Mom[6] = cal3orderMom(channelsBGR[0]);
	//����Gͨ������ɫ��
	meanStdDev(channelsBGR[1], tmp_m, tmp_sd);
	Mom[1] = tmp_m.at<double>(0.0);
	Mom[4] = tmp_sd.at<double>(0, 0);
	Mom[7] = cal3orderMom(channelsBGR[1]);
	//����Bͨ������ɫ��
	meanStdDev(channelsBGR[2], tmp_m, tmp_sd);
	Mom[2] = tmp_m.at<double>(0.0);
	Mom[5] = tmp_sd.at<double>(0, 0);
	Mom[8] = cal3orderMom(channelsBGR[2]);
}

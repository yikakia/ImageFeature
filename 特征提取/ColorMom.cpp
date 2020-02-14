#include "ColorMom.h"

//导入图片
bool ColorMom::importImage(String path)
{
	image = imread(path);
	if (!image.data)
		return false;
	if (image.channels() != 3) {
		cout << "错误，此图像需要是有颜色的图像" << endl;
	}
	return true;
}


//分离通道
void ColorMom::splitChannels()
{
	//channelsBGR[0] = new Mat(image.rows, image.cols, CV_8U);
	//channelsBGR[1] = new Mat(image.rows, image.cols, CV_8U);
	//channelsBGR[2] = new Mat(image.rows, image.cols, CV_8U);
	//
	split(image, channelsBGR);
}


// 计算三阶矩
double ColorMom::cal3orderMom(Mat& channel)
{
	uchar* p;
	double mom = 0;
	double avg = mean(channel)[0];//计算单通道图像的均值
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
	//求均值的立方根
	return mom;
}


//计算颜色矩
void ColorMom::calColorMom()
{
	Mat tmp_m, tmp_sd;
	//计算B通道的颜色矩
	meanStdDev(channelsBGR[0], tmp_m, tmp_sd);
	Mom[0] = tmp_m.at<double>(0.0);
	Mom[3] = tmp_sd.at<double>(0, 0);
	Mom[6] = cal3orderMom(channelsBGR[0]);
	//计算G通道的颜色矩
	meanStdDev(channelsBGR[1], tmp_m, tmp_sd);
	Mom[1] = tmp_m.at<double>(0.0);
	Mom[4] = tmp_sd.at<double>(0, 0);
	Mom[7] = cal3orderMom(channelsBGR[1]);
	//计算B通道的颜色矩
	meanStdDev(channelsBGR[2], tmp_m, tmp_sd);
	Mom[2] = tmp_m.at<double>(0.0);
	Mom[5] = tmp_sd.at<double>(0, 0);
	Mom[8] = cal3orderMom(channelsBGR[2]);
}

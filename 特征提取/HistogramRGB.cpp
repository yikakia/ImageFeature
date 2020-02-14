#include "HistogramRGB.h"
//����ͼƬ 
bool HistogramRGB::importImage(String path) {
	image = imread(path);
	if (!image.data)
		return false;
	return true;
}
//����ͨ��  
void HistogramRGB::splitChannels() {
	split(image, channelsRGB);
}
//����ֱ��ͼ  
void HistogramRGB::getHistogram() {
	ofstream outputfile(outputfilename);//����ļ�
	calcHist(&channelsRGB[0], 1, 0, Mat(), outputRGB[0], 1, hisSize, &ranges);
	calcHist(&channelsRGB[1], 1, 0, Mat(), outputRGB[1], 1, hisSize, &ranges);
	calcHist(&channelsRGB[2], 1, 0, Mat(), outputRGB[2], 1, hisSize, &ranges);

	//�������bin��ֵ  
	for (int i = 0; i < hisSize[0]; ++i) {
		cout << i << "   B:" << outputRGB[0].at<float>(i);
		cout << "   G:" << outputRGB[1].at<float>(i);
		cout << "   R:" << outputRGB[2].at<float>(i) << endl;

		outputfile << i << "   B:" << outputRGB[0].at<float>(i);
		outputfile << "   G:" << outputRGB[1].at<float>(i);
		outputfile << "   R:" << outputRGB[2].at<float>(i) << endl;
	}
	if (outputfile.is_open()) {
		outputfile.close();
	}
}
//��ʾֱ��ͼ  
void HistogramRGB::displayHisttogram() {
	Mat rgbHist[3];
	for (int i = 0; i < 3; i++)
	{
		rgbHist[i] = Mat(hisWidth, hisHeight, CV_8UC3, Scalar::all(0));
	}
	normalize(outputRGB[0], outputRGB[0], 0, (double)hisWidth - 20, NORM_MINMAX);
	normalize(outputRGB[1], outputRGB[1], 0, (double)hisWidth - 20, NORM_MINMAX);
	normalize(outputRGB[2], outputRGB[2], 0, (double)hisWidth - 20, NORM_MINMAX);
	for (int i = 0; i < hisSize[0]; i++)
	{
		int val = saturate_cast<int>(outputRGB[0].at<float>(i));
		rectangle(rgbHist[0], Point(i * 2 + 10, rgbHist[0].rows), Point((i + 1) * 2 + 10, rgbHist[0].rows - val), Scalar(0, 0, 255), 1, 8);
		val = saturate_cast<int>(outputRGB[1].at<float>(i));
		rectangle(rgbHist[1], Point(i * 2 + 10, rgbHist[1].rows), Point((i + 1) * 2 + 10, rgbHist[1].rows - val), Scalar(0, 255, 0), 1, 8);
		val = saturate_cast<int>(outputRGB[2].at<float>(i));
		rectangle(rgbHist[2], Point(i * 2 + 10, rgbHist[2].rows), Point((i + 1) * 2 + 10, rgbHist[2].rows - val), Scalar(255, 0, 0), 1, 8);
	}
	cv::imshow("R", rgbHist[0]);
	imshow("G", rgbHist[1]);
	imshow("B", rgbHist[2]);
	imshow("image", image);
}

//��������ļ���
void HistogramRGB::setOutputFileName(string str) {
	outputfilename = str;
}

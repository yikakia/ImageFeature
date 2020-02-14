#include "HistogramRGB.h"
#include"ColorMom.h"
int main() {
	string path = "C:\\Users\\yika_\\Desktop\\TIMͼƬ20200212180547.jpg";

	//HistogramRGB hist;
	//if (!hist.importImage(path)) {
	//	cout << "Import Error!" << endl;
	//	return -1;
	//}
	//hist.splitChannels();
	//hist.getHistogram();
	//hist.displayHisttogram();
	//waitKey(0);
	ColorMom comom;
	if (!comom.importImage(path)) {
		cout << "Import Error!" << endl;
		return -1;	
	}
	comom.splitChannels();
	comom.calColorMom();
	for (int i = 0; i < 9; i++)
	{
		cout << comom.Mom[i] << "    " << endl;
	}
	waitKey(0);
	return 0;
}
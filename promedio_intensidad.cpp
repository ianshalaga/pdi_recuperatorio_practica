#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

int promedio_intensidad(const Mat &imagen) {
	
	Mat prom_v = promedio_intensidad_v(imagen);
	Mat prom = promedio_intensidad_h(prom_v);
	
	int promedio = prom.at<uchar>(0,0);
	
	return promedio;
}

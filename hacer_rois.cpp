#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "vector"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

vector<Rect> hacer_rois(Mat cajas_cc) {
	
	double min,max;
	minMaxLoc(cajas_cc,&min,&max);
	int numero_objetos = max;
	
	vector<Rect> rois(9);
	
	for(int i=1;i<numero_objetos;i++) { 
		Mat mask = umbral_rango(cajas_cc,i,i);
		Mat promedios_v = promedio_intensidad_v(mask);
		Mat promedios_h = promedio_intensidad_h(mask);
		threshold(promedios_v,promedios_v,127,255,THRESH_BINARY|THRESH_OTSU);
		threshold(promedios_h,promedios_h,127,255,THRESH_BINARY|THRESH_OTSU);
		vector<int> vector_v = blancos_v(promedios_h);
		vector<int> vector_h = blancos_h(promedios_v);
		Rect roi(vector_h[1],vector_v[1],vector_h[2]-vector_h[1],vector_v[2]-vector_v[1]);
		rois[i-1] = roi;
	}
	
	return rois;
}

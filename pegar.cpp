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

Mat pegar(vector<Mat> recuadros,Mat cajas,Mat cajas_mask) {
	
	Mat promedios_v = promedio_intensidad_v(cajas_mask);
	Mat promedios_h = promedio_intensidad_h(cajas_mask);
	threshold(promedios_v,promedios_v,40,255,THRESH_BINARY);
	threshold(promedios_h,promedios_h,40,255,THRESH_BINARY);
	imwrite("promedios_v.png",promedios_v);
	imwrite("promedios_h.png",promedios_h);
	vector<int> vector_v = blancos_v(promedios_h);
	vector<int> vector_h = blancos_h(promedios_v);
	
	for(int i=0;i<recuadros.size();i++) { 
		
		vector<Mat> recuadro_vec;
		split(recuadros[i],recuadro_vec);
		
		Mat red,green;
		threshold(recuadro_vec[2],red,0,255,THRESH_BINARY|THRESH_OTSU);
		threshold(recuadro_vec[1],green,0,255,THRESH_BINARY|THRESH_OTSU);
		Mat RG_u;
		bitwise_or(red,green,RG_u);
		int promGR = promedio_intensidad(RG_u);
		
		cout<<promGR<<endl;
		
		if (promGR < 40)
			recuadros[i].copyTo(cajas(Rect(vector_h[4]+16,vector_v[4]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 60)
			recuadros[i].copyTo(cajas(Rect(vector_h[2]+16,vector_v[4]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 90)
			recuadros[i].copyTo(cajas(Rect(vector_h[0]+16,vector_v[4]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 180)
			recuadros[i].copyTo(cajas(Rect(vector_h[4]+16,vector_v[2]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 198)
			recuadros[i].copyTo(cajas(Rect(vector_h[2]+16,vector_v[2]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 203)
			recuadros[i].copyTo(cajas(Rect(vector_h[0]+16,vector_v[2]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 208)
			recuadros[i].copyTo(cajas(Rect(vector_h[4]+16,vector_v[0]+16,recuadros[i].cols,recuadros[i].rows)));
		else if (promGR < 213)
			recuadros[i].copyTo(cajas(Rect(vector_h[2]+16,vector_v[0]+16,recuadros[i].cols,recuadros[i].rows)));
		else
			recuadros[i].copyTo(cajas(Rect(vector_h[0]+16,vector_v[0]+16,recuadros[i].cols,recuadros[i].rows)));
	}
	
	return cajas;
}

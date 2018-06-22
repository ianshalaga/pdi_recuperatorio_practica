#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

int posicion_y(vector<int> vector_h,int indice) {
	
	int x;
	
	if (indice == 0)
		x = vector_h[1]+(vector_h[2]-vector_h[1])/2;
	else if (indice == 1)
		x = vector_h[1]+(vector_h[2]-vector_h[1])/2;
	else if (indice == 2)
		x = vector_h[1]+(vector_h[2]-vector_h[1])/2;
	else if (indice == 3)
		x = vector_h[5]+(vector_h[6]-vector_h[5])/2;
	else if (indice == 4)
		x = vector_h[5]+(vector_h[6]-vector_h[5])/2;
	else if (indice == 5)
		x = vector_h[5]+(vector_h[6]-vector_h[5])/2;
	else if (indice == 6)
		x = vector_h[9]+(vector_h[10]-vector_h[9])/2;
	else if (indice == 7)
		x = vector_h[9]+(vector_h[10]-vector_h[9])/2;
	else if (indice == 8)
		x = vector_h[9]+(vector_h[10]-vector_h[9])/2;
	
	return x;
}

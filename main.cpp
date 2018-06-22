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

int main(int argc, char** argv) {

	//	Carga de imagenes
	Mat frutas = imread("Frutas_parcial02.jpg");
	Mat cajas = imread("CAJAS_test.jpg");
	
	Mat cajas_hsv;
	cvtColor(cajas,cajas_hsv,CV_BGR2HSV);
	vector<Mat> cajas_vec;
	split(cajas_hsv,cajas_vec);
	
//	imwrite("cajas_gris.png",cajas);
	
	Mat cajas_mask;
	threshold(cajas_vec[2],cajas_mask,175,255,THRESH_BINARY_INV);
	
	Mat cajas_cc,cajas_est,cajas_cen;
	connectedComponentsWithStats(cajas_mask,cajas_cc,cajas_est,cajas_cen);
	cajas_cc.convertTo(cajas_cc,CV_8UC(1));
	
	//
	Mat frutas_mediana;
	medianBlur(frutas,frutas_mediana,7);
	imwrite("frutas_mediana.png",frutas_mediana);	
	
	Mat frutas_hsv;
	cvtColor(frutas,frutas_hsv,CV_BGR2HSV);
	vector<Mat> frutas_vec;
	split(frutas_hsv,frutas_vec);
	
	Mat frutas_mask;
	threshold(frutas_vec[2],frutas_mask,230,255,THRESH_BINARY);
	
	Mat promedios_v = promedio_intensidad_v(frutas_mask);
	Mat promedios_h = promedio_intensidad_h(frutas_mask);
	threshold(promedios_v,promedios_v,40,255,THRESH_BINARY);
	threshold(promedios_h,promedios_h,40,255,THRESH_BINARY);
//	imwrite("promedios_v.png",promedios_v);
//	imwrite("promedios_h.png",promedios_h);
	vector<int> vector_v = blancos_v(promedios_h);
	vector<int> vector_h = blancos_h(promedios_v);
	
	Rect roi1(vector_h[1],vector_v[1],vector_h[2]-vector_h[1],vector_v[2]-vector_v[1]);
	Rect roi2(vector_h[3],vector_v[1],vector_h[4]-vector_h[3],vector_v[2]-vector_v[1]);
	Rect roi3(vector_h[5],vector_v[1],vector_h[6]-vector_h[5],vector_v[2]-vector_v[1]);
	Rect roi4(vector_h[1],vector_v[3],vector_h[2]-vector_h[1],vector_v[4]-vector_v[3]);
	Rect roi5(vector_h[3],vector_v[3],vector_h[4]-vector_h[3],vector_v[4]-vector_v[3]);
	Rect roi6(vector_h[5],vector_v[3],vector_h[6]-vector_h[5],vector_v[4]-vector_v[3]);
	Rect roi7(vector_h[1],vector_v[5],vector_h[2]-vector_h[1],vector_v[6]-vector_v[5]);
	Rect roi8(vector_h[3],vector_v[5],vector_h[4]-vector_h[3],vector_v[6]-vector_v[5]);
	Rect roi9(vector_h[5],vector_v[5],vector_h[6]-vector_h[5],vector_v[6]-vector_v[5]);
	
	Mat recuadro1 = frutas(roi1);
	Mat recuadro2 = frutas(roi2);
	Mat recuadro3 = frutas(roi3);
	Mat recuadro4 = frutas(roi4);
	Mat recuadro5 = frutas(roi5);
	Mat recuadro6 = frutas(roi6);
	Mat recuadro7 = frutas(roi7);
	Mat recuadro8 = frutas(roi8);
	Mat recuadro9 = frutas(roi9);
	
	imwrite("recuadro1.png",recuadro1);
	imwrite("recuadro2.png",recuadro2);
	imwrite("recuadro3.png",recuadro3);
	imwrite("recuadro4.png",recuadro4);
	imwrite("recuadro5.png",recuadro5);
	imwrite("recuadro6.png",recuadro6);
	imwrite("recuadro7.png",recuadro7);
	imwrite("recuadro8.png",recuadro8);
	imwrite("recuadro9.png",recuadro9);
	
	vector<Mat> recuadros = {recuadro1,recuadro2,recuadro3,recuadro4,recuadro5,recuadro6,recuadro7,recuadro8,recuadro9};
	
	double min,max;
	minMaxLoc(cajas_cc,&min,&max);
	int numero_objetos = max;
	
	Mat cc1 = umbral_rango(cajas_cc,numero_objetos-1,numero_objetos-1);
	
//	Mat res = pegar(recuadros,cajas_cc,cajas);
	
	promedios_v = promedio_intensidad_v(cajas_mask);
	promedios_h = promedio_intensidad_h(cajas_mask);
	threshold(promedios_v,promedios_v,40,255,THRESH_BINARY);
	threshold(promedios_h,promedios_h,40,255,THRESH_BINARY);
	imwrite("promedios_v.png",promedios_v);
	imwrite("promedios_h.png",promedios_h);
	vector_v = blancos_v(promedios_h);
	vector_h = blancos_h(promedios_v);
	
//	recuadro1.copyTo(cajas(Rect(vector_h[0]+16,vector_v[0]+16,recuadro1.cols,recuadro1.rows)));
	
	pegar(recuadros,cajas,cajas_mask);
	
//	vector<Rect> rois = hacer_rois(cajas_cc);
	
//	Presentacion de resultados
//	vector<Mat> resultados = {recuadro1,recuadro2,recuadro3,recuadro4,recuadro5,recuadro6,recuadro7,recuadro8,recuadro9};
	vector<Mat> resultados = {cajas};
	Mat mosaico_res = concatenar_imagenes(resultados,true,true);
//
////	Ventanas
	namedWindow("resultados",CV_WINDOW_KEEPRATIO); //reserva ventana para imagen
	imshow("resultados",mosaico_res); //muestra la imagen en la ventana
	waitKey(); //espera a una tecla para cerrar la ventana de la image
	
	return 0;
} 

#include "StdAfx.h"
#include "Elemento.h"

Elemento::Elemento(void)
{
	CvMemStorage* memoria = cvCreateMemStorage(0);
	elementos = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(IplImage),memoria);
	
	IplImage* imgAux = cvLoadImage("Elementos/pausa-minima.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/pausa-semi-breve.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/pausa-seminima.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);
	
	//semifusa	
	imgAux = cvLoadImage("Elementos/pausa-semifusa.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	//fusa
	imgAux = cvLoadImage("Elementos/pausa-fusa.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/pausa-semicolcheia.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/pausa-colcheia.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);
	
	imgAux = cvLoadImage("Elementos/cabeca_preenchida.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/semi-breve.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/semi-breve2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);

	imgAux = cvLoadImage("Elementos/minima.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);	

	imgAux = cvLoadImage("Elementos/minima2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(elementos,imgAux);
}

Elemento::~Elemento(void)
{
}
CvSeq* Elemento::getElementos(){
	return elementos;
}

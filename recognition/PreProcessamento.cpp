#include "StdAfx.h"
#include "preProcessamento.h"

PreProcessamento::PreProcessamento(void)
{
}

PreProcessamento::~PreProcessamento(void)
{
}
void PreProcessamento::trataImagem(IplImage* imgOriginal, int imgLargura)
{
	//calculo da propor��o para padroniza��o da imagem.
	int imgAltura = imgOriginal->height * imgLargura / imgOriginal->width;
	
	//cria��o da imagem com a propor��o padronizada.
	IplImage* imgProcess = cvCreateImage(cvSize(imgLargura,imgAltura),8,imgOriginal->nChannels);
	
	//transforma��o da imagem original para a imagem normalizada.
	cvResize(imgOriginal,imgProcess ,1);

	//imgProcess = imgOriginal;
	imgTonsCinza = cvCreateImage(cvSize(imgProcess->width,imgProcess->height),8,1);	
	imgBinarizada = cvCreateImage(cvSize(imgProcess->width,imgProcess->height),8,1);
	imgMapaBordas = cvCreateImage(cvSize(imgProcess->width,imgProcess->height),8,1);
	
	if( imgOriginal->nChannels == 1 ){
		imgTonsCinza = imgProcess;
	}else{
		cvCvtColor(imgProcess,imgTonsCinza,CV_RGB2GRAY);		
	}
	
	cvThreshold(imgTonsCinza,imgBinarizada,230,255,0);

	cvCanny(imgBinarizada,imgMapaBordas,100,100,3);
}
IplImage* PreProcessamento::getImgBinarizada()
{
	return imgBinarizada;
}
IplImage* PreProcessamento::getImgMapaBordas()
{
	return imgMapaBordas;
}
IplImage* PreProcessamento::getImgTonsCinza()
{
	return imgTonsCinza;
}
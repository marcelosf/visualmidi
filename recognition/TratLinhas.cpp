#include <cv.h>
#include <cxcore.h>
#include <cvaux.h>
#include <highgui.h>
#include "stdafx.h"


//Este é o construtor do objeto linhas. O objeto é construído passando-se como parâmetros:
//				*A imagem com o mapa de bordas.
//				*O valor de theta a ser utilizado pela transformada de Hough.
//				*O valor de rho a ser utilizado pela transformada de Hough.
//				*O valor de threshold a ser utilizado pela transformada de Hough.
//				*Uma estrutura de memória onde serão armazenados os parâmetros das linhas detectadas pela transformada de Hough.
//Exemplo de utilização:	linhas hough = linhas(mapa,180,1,300,linhaStorage);

TratLinhas::TratLinhas(IplImage* imagemMapaDeBordas, int val_theta, int val_rho, int val_threshold, CvMemStorage* line_storage)
{
	storage = line_storage;
	lines = 0;
	theta = val_theta;
	threshold = val_threshold;
	imgEdge = imagemMapaDeBordas;
	rho = val_rho;
}


//A função critério estabelece o critério de ordenação da sequência de pontos detectadas pela transformada de Hough.
//É chamada pela função cvSeqSort localizada na linha 85.

int criterio(const void* _a, const void* _b, void* userdata)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	int diff = *a - *b;
	return diff ;
}

//A função detectaLinhas, aplica a transformada de hough na imagem além de retornar a imagem com as linhas detectadas na cor verde.
//Esta função retorna também uma sequencia das coordenadas Y das linhas detectadas de forma ordenada.
//Parâmetros:
//					*imgLinhas é a imagem onde será desehnada as linhas detectadas.
//					*numeroDeLinhas é o limite máximo de linhas que se deseja detectar.
//					*seqPontos retorna a sequência em ordem crescente de pontos Y detectadas pela transformada de Hough.
void TratLinhas::detectaLinhas(IplImage* imgLinhas,CvSeq* seqPontos)
{
	lines = cvHoughLines2(imgEdge,storage,CV_HOUGH_STANDARD,rho,CV_PI/theta,threshold,0,0);		//aplicando a transformada de Hough
	printf("Pontos das  Linhas : \n");
	for( int i = 0; i < lines->total; i++ )
	{
		
		//CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);			//funções para utilização com o 
		//cvLine(img, line[0], line[1], CV_RGB(255,0,0), 1, 8 );	    //hough Probabilistic.

		float* line = (float*)cvGetSeqElem(lines,i);
		float rho = line[0];
		float theta = line[1];
		CvPoint pt1, pt2,pt;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		cvLine(imgLinhas, pt1, pt2, CV_RGB(0,255,0),1, 8 );//---//desenha as linhas detectadas na imagem.
		cvSeqPush(seqPontos,&pt1.y);//-----------------------------//armazena a sequencia de pontos Y detectadas em "pontos".
		printf("Valor de Y = %u\n",pt1.y);
	}															
	cvSeqSort(seqPontos,criterio,0);//-----------------------------/ordena a sequencia pontos.
	printf("\n");
	printf("Pontos Ordenados :\n");
}

//A função larguraLinhas recebe a sequencia de coordenadas Y encontradas pela 
//transformada de Hough e calcula a largura da primeira linha.
int TratLinhas::larguraLinhas(CvSeq* seq)
{
	int* elemento = (int*)cvGetSeqElem(seq,0);
	int* elemento2 = (int*)cvGetSeqElem(seq,1);
	return *elemento2 - *elemento;		
}

//A função distEntreLinhas retorna a médio do espaço entre as linhas de um pentagrama.
//Recebe como entrada uma sequencia com os pontos detectados pela transformada de Hough localizada na linha.
int TratLinhas::distEntreLinhas(CvSeq *seq)
{
	int dist; 
	int* linha1= (int*)cvGetSeqElem(seq,1);//pega a posição da primeira linha
	int* linha2= (int*)cvGetSeqElem(seq,3);//pega a posição da segunda linha
	int dist1= *linha2-*linha1;//calcula a distancia entre as duas
	printf("Distancia1= %u\n",dist1);
	
	int* linha3= (int*)cvGetSeqElem(seq,5);//pega a terceira linha
	int dist2= *linha3-*linha2;//calcula dist entre 2 e 3 linha
	printf("Distancia2= %u\n",dist2);

	if(dist2<=dist1+2 || dist1<=dist2+2)//faz uma media das distancias encontradas se a dif for de até 2 pixels
	{
		dist=(dist1+dist2)/2;//calcula a media da distancia entre as linhas
		printf("Distancia= %u\n",dist);
	}
	return dist;

}

//Esta função tem como propósito a separação da partitura em pentagramas para a realização de processamento
//nesta região.
void TratLinhas::processaPentagrama(CvSeq *seq,int dist, IplImage *partitura,CvSeq *pentagramas,CvMemStorage *imgStorage)
{
	int inicio = 0;
	int fim = 0;
	CvSeq *seqPent;
	storage = imgStorage;
	
	seqPent = cvCreateSeq(0,sizeof(CvSeq),sizeof(IplImage),storage);
	
	for( int i = 0; i <seq->total; i++ )			//entra no for em quantidades de linhas encontradas
	{
		int* lin1= (int*)cvGetSeqElem(seq,i);		//pega lihna i
		int* lin2= (int*)cvGetSeqElem(seq,i+1);		// pega linha i+1
		if((*lin2-*lin1) > dist+2 )					// entra se a dif for maior q a distancia entre duas linhas do mesmo pentagrama
		{
			inicio = fim;
			printf("início= %u\n",inicio);
			fim= *lin1 + ((*lin2-*lin1)/2);			// acha o fim do pentagrama
			printf("fim= %u\n",fim);
			cvLine(partitura,cvPoint(0,fim),cvPoint(partitura->width,fim),CV_RGB(0,0,255),1,8,0);	// traça uma linha entre os pentagramas
			
			//define região de interesse da imagem, ou seja, define um pentagrama
			//td processamento apartir daqui sera feito apenas no pentagrama corrente.

			cvSetImageROI(partitura, cvRect(0,inicio,partitura->width,fim-inicio)); 
			IplImage* imgPent = cvCloneImage(partitura);											//clona a figura partitura
			cvSeqPush(seqPent,&imgPent);	// a região do pentagrama é armazenada em um vetor de sequencias de imagens.
			//cvZero(imgPent);
			cvNamedWindow("Teste pentagrama ",1);
			cvShowImage("Teste pentagrama ",imgPent);

			// retira o ROI, apartir daqui a imagem não sera mais apenas processada na região definida anteriormante.
			cvResetImageROI(partitura);

			cvReleaseImage(&imgPent);
			
		}//cvWaitKey(0);
	}
}

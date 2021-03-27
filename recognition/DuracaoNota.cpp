#include "StdAfx.h"
#include "DuracaoNota.h"
#include "Auxiliar.h"

DuracaoNota::DuracaoNota(void)
{
	CvMemStorage* memoria = cvCreateMemStorage(0);
	tiposDuracao = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(IplImage),memoria);
/*
	IplImage* imgAux = cvLoadImage("Elementos/seminima.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	//cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/colcheia.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/colcheia2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);

	imgAux = cvLoadImage("Elementos/colcheia3.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);

	imgAux = cvLoadImage("Elementos/semicolcheia.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/semicolcheia2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/semicolcheia3.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/fusa.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	
	
	imgAux = cvLoadImage("Elementos/fusa2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	
	
	imgAux = cvLoadImage("Elementos/fusa3.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/semifusa.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	

	imgAux = cvLoadImage("Elementos/semifusa2.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);

	imgAux = cvLoadImage("Elementos/semifusa3.jpg", 0);
	cvThreshold(imgAux,imgAux,230,255,0);
	cvSeqPush(tiposDuracao,imgAux);	
*/
}

DuracaoNota::~DuracaoNota(void)
{
}
CvSeq* DuracaoNota::getTiposDuracao(){
	return tiposDuracao;
}
int DuracaoNota::verificaDuracaoNota(IplImage* imgNota, int x, int width, int height){
	
	Auxiliar a = Auxiliar();
	
	for (int i=1; i!= height; i++){		
		for (int j=(x-5); j!=(x+14); j++){
			if( i > 5 && i<(imgNota->height-5) ){
				bool pinta = true;
				for( int alt=-3; alt<=3; alt++ ){
					
					uchar cor = ((uchar*)(imgNota->imageData + (i+(alt))* imgNota->widthStep))[j];
					if( cor == 255 ){
						pinta = false;
					}
				}
				if(pinta){
					for( int alt=1; alt<height; alt++ ){
						((uchar*)(imgNota->imageData + ((alt))* imgNota->widthStep))[j] = 255;
					}
				}
			}			
		}
	}

	
	int total = 0;
	
	bool encontrou = false;
	bool inc = true;

	int posX = width;
	while( !encontrou ){
		for (int j=1; j!= (height); j++){
			uchar inf = ((uchar*)(imgNota->imageData + (j)* imgNota->widthStep))[posX];
			uchar inf2;
			uchar sup;
			if( j+1 <height ){
				inf2 = ((uchar*)(imgNota->imageData + (j+1)* imgNota->widthStep))[posX];
			}
			if( j+2 <height ){
				sup = ((uchar*)(imgNota->imageData + (j+2)* imgNota->widthStep))[posX];
			}
			if( inf == 0 && inf2==0 && sup==255 ){
				total++;
			}
		}
		
		if( total == 0 ){
			if( inc ){
				posX++;
			}else{
				posX--;
			}

			if(width+6 == posX){
				posX = posX-6;
				inc = false;
			}

		}else{
			encontrou = true;
		}
	}

	
	int duracao = 0;

	switch(total){
		case 1 :
			duracao = 8;
			break;
		case 2 :
			duracao = 16;
			break;
		case 3 :
			duracao = 32;
			break;
		case 4 :
			duracao = 64;
			break;
		default :
			duracao = 64;
			break;
	}

	return duracao;
}
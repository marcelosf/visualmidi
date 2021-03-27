#include "StdAfx.h"
#include "Pentagrama.h"
#include "Imagem.h"
#include "Auxiliar.h"
#include "Elemento.h"
#include "DuracaoNota.h"
#include "math.h"

Pentagrama::Pentagrama(void)
{
}

Pentagrama::~Pentagrama(void)
{
}
/**************************************
*  A função criterio não pertence a   *
*  classe, ela serve apenas para a    *
*  utilização do cvSeqSort.           *
***************************************/
int criterioPontos(const void* _a, const void* _b, void* userdata)
{
	CvPoint3D32f* a = (CvPoint3D32f*)_a;
    CvPoint3D32f* b = (CvPoint3D32f*)_b;
   
    int x_diff = a->x - b->x;
    return x_diff;

}
CvSeq* Pentagrama::getElementosPentagrama(){
	return this->elementosPentagrama;
}
void Pentagrama::interpretaPentagrama(IplImage* pentagrama){
	
	Imagem objPentagrama = Imagem();
	objPentagrama.carregarImagem(pentagrama);
	
	Auxiliar aux = Auxiliar();
	
	objPentagrama.trataImagem(objPentagrama.getImgOriginal(), 827);
	objPentagrama.detectaLinhas(objPentagrama.getImgMapaBordas());
	
	IplImage* tonCinzaAux = limpaPentagrama(objPentagrama.getImgTonsCinza());
	IplImage* ImgLimpa = cvCloneImage(tonCinzaAux);
	
	Elemento e = Elemento();
	DuracaoNota d = DuracaoNota();

	CvMemStorage* memoriaNotas = cvCreateMemStorage(0);
	elementosPentagrama = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(CvPoint3D32f),memoriaNotas);

	// Busca no pentagrama os elementos
	int count = 0;
	for( int i=0; i<e.getElementos()->total; i++ ){
		
		IplImage* imgElemento = (IplImage*)cvGetSeqElem(e.getElementos(), i);				
		
		CvPoint		minloc; 
		CvPoint		maxloc;
		double		minval, maxval;
		int posX;
		int posY;
		
		int linhaMeio = getLinhaMeio(objPentagrama.getLinhas());
		int distLinha = getDistLinhas(objPentagrama.getLinhas());
		int posnota;
		int duracao;

		minloc.x = 1;
		
		IplImage* result = cvCreateImage(cvSize(objPentagrama.getImgTonsCinza()->width - imgElemento->width + 1, objPentagrama.getImgTonsCinza()->height - imgElemento->height + 1),32,1);
		
		while( minloc.x != 0 ){
			
			cvMatchTemplate(tonCinzaAux,imgElemento,result,1);
			cvMinMaxLoc( result, &minval, &maxval, &minloc, &maxloc, 0 );
			
			posX = minloc.x + (imgElemento->width / 2);
			posY = minloc.y + (imgElemento->height / 2);
			
			if( minloc.x != 0 ){
				
				if( i < 7 ){ //Pausas
					if( minval < 0.1 ){
						posnota = 999;
						duracao = getDuracaoPausa(i);
						count++;
					}else{
						minloc.x = 0;
					}				
				}else{ //Notas
					posnota = calculaNota((float)linhaMeio, (float)distLinha, (float)posY);
					count++;
				}
				
				//duracao = i;
				for (int i=(minloc.y-2); i!=(minloc.y+imgElemento->height+2); i++){
					for (int j=(minloc.x-2); j!=(minloc.x+imgElemento->width+2); j++){			
						((uchar*)(tonCinzaAux->imageData + i* tonCinzaAux->widthStep))[j] = 255;
					}
				}	
				
				
				if( minloc.x != 0 ){
					
					cvRectangle( 
						objPentagrama.getImgOriginal(), 
						cvPoint( minloc.x, minloc.y ), 
						cvPoint( minloc.x + imgElemento->width, minloc.y + imgElemento->height ),
						cvScalar( 0, 0, 255, 0 ), 1, 0, 0 
					);


					if( i==7 ){
						int total = 0;
						int verifica = 0;
						int verificapreto = 0;
						for (int j=1; j!= (tonCinzaAux->height); j++){		
							for (int l=(minloc.x-2); l!=(imgElemento->width+minloc.x+2); l++){								
								uchar cor = ((uchar*)(tonCinzaAux->imageData + j* tonCinzaAux->widthStep))[l];
							
								if( cor==0 ){
									total++;						
								}
							}
						}

						printf("x = %d | total = %d %d \n", posX, total, verifica);

						cvSetImageROI(tonCinzaAux, cvRect((minloc.x-5),0,(imgElemento->width+10),pentagrama->height));
						//aux.mostraImagem("teste ROI", tonCinzaAux);						
						IplImage* imgAuxPentagrama = cvCloneImage(tonCinzaAux);
						

						//Seta as dimensoes reais da imagem
						imgAuxPentagrama->width = imgElemento->width+8;
						imgAuxPentagrama->height = pentagrama->height;						

						cvResetImageROI(tonCinzaAux);

						if( total > 3 ){
							duracao = d.verificaDuracaoNota(imgAuxPentagrama, minloc.x, (posX), pentagrama->height);
						}else{
							duracao = 4;
						}						
					}else if(i==8 || i==9){
						duracao = 1;
					}else if(i==10 || i==11){
						duracao = 2;
					}

					CvPoint3D32f nota = cvPoint3D32f((double)minloc.x,(double)posnota,(double)duracao);
					cvSeqPush(elementosPentagrama, &nota);
				}

				for (int i=1; i!=(pentagrama->height); i++){
					for (int j=(minloc.x); j!=(minloc.x+imgElemento->width); j++){			
						((uchar*)(tonCinzaAux->imageData + i* tonCinzaAux->widthStep))[j] = 255;
					}
				}	
			}
			
		}
	}
	
	cvSeqSort(elementosPentagrama, criterioPontos,0);
	

	aux.mostraImagem("tes322", ImgLimpa);
	aux.mostraImagem("tes3213t2e", objPentagrama.getImgOriginal());
}
int Pentagrama::getLinhaMeio( CvSeq* linhas ){
	
	float* linha = (float*)cvGetSeqElem(linhas, 4);
	float* linha2 = (float*)cvGetSeqElem(linhas, 5);

	float rhoLinha = linha[0];
	float thetaLinha = linha[1];
	double aLinha = cos(thetaLinha); 
	double bLinha = sin(thetaLinha);
	
	int yLinha = cvRound((bLinha*rhoLinha) + 1000*(aLinha));	

	float rhoLinha2 = linha2[0];
	float thetaLinha2 = linha2[1];
	double aLinha2 = cos(thetaLinha2); 
	double bLinha2 = sin(thetaLinha2);
	
	int yLinha2 = cvRound((bLinha2*rhoLinha2) + 1000*(aLinha2));	

	return ( yLinha2 + yLinha )/2;
}

int Pentagrama::getDistLinhas( CvSeq* linhas ){

	float* linha = (float*)cvGetSeqElem(linhas, 0);
	float* linha2 = (float*)cvGetSeqElem(linhas, 2);

	float rhoLinha = linha[0];
	float thetaLinha = linha[1];
	double aLinha = cos(thetaLinha); 
	double bLinha = sin(thetaLinha);
	
	int yLinha = cvRound((bLinha*rhoLinha) + 1000*(aLinha));	

	float rhoLinha2 = linha2[0];
	float thetaLinha2 = linha2[1];
	double aLinha2 = cos(thetaLinha2); 
	double bLinha2 = sin(thetaLinha2);
	
	int yLinha2 = cvRound((bLinha2*rhoLinha2) + 1000*(aLinha2));	

	return yLinha2 - yLinha;
}
int Pentagrama::calculaNota(float linhaMeio, float distLinha, float posY){
	
	int posicao = floor( (( posY - linhaMeio ) / ( distLinha / 2 ))+0.5 );
	
	return posicao;
}
int Pentagrama::getDuracaoPausa(int valor){
	
	switch(valor){
		case 0:
			valor = 2;
			//valor = 32;
			break;
		case 1:
			valor = 1;
			//valor = 64;
			break;
		case 2:
			valor = 4;
			//valor = 16;
			break;
		case 3:
			valor = 64;
			//valor = 1;
			break;
		case 4:
			valor = 32;
			//valor = 2;
			break;
		case 5:
			valor = 16;
			//valor = 4;
			break;
		case 6:
			valor = 8;
			break;
	}
	
	return valor;
}
IplImage* Pentagrama::limpaPentagrama( IplImage* pentagrama ){
	//printf("\nfoi\n");
	//Remove As linhas horizontais e verticais
	for (int i=1; i!= pentagrama->height; i++){		
		for (int j=1; j!= (pentagrama->width)+1; j++){
			uchar inf = ((uchar*)(pentagrama->imageData + (i-1)* pentagrama->widthStep))[j];
			uchar pos = ((uchar*)(pentagrama->imageData + (i+1)* pentagrama->widthStep))[j];
			
			if( inf == 255 && pos == 255 ){
				((uchar*)(pentagrama->imageData + i* pentagrama->widthStep))[j] = 255;
			}
		}
	}

	for (int i=1; i!= pentagrama->height; i++){		
		for (int j=1; j!= (pentagrama->width)+1; j++){
			uchar inf = ((uchar*)(pentagrama->imageData + (i-1)* pentagrama->widthStep))[j];
			uchar pos = ((uchar*)(pentagrama->imageData + (i+1)* pentagrama->widthStep))[j];
						
			if( i > 21 && i<(pentagrama->height-21) ){
				bool pinta = true;
				for( int alt=-7; alt<=7; alt++ ){
					
					uchar cor = ((uchar*)(pentagrama->imageData + (i+(alt))* pentagrama->widthStep))[j];
					if( cor == 255 ){
						pinta = false;
					}
				}
				if(pinta){					
					for( int alt=-21; alt<=21; alt++ ){
						uchar prox = ((uchar*)(pentagrama->imageData + (i+(alt))* pentagrama->widthStep))[j-2];
						//uchar prox2 = ((uchar*)(pentagrama->imageData + (i+alt)* pentagrama->widthStep))[j+1];
						uchar ant = ((uchar*)(pentagrama->imageData + (i+(alt))* pentagrama->widthStep))[j+1];

						if( prox == 255 && ant == 255  ){
								((uchar*)(pentagrama->imageData + (i+(alt))* pentagrama->widthStep))[j] = 255;
						}
					}
				}
			}
		}
	}

	//Remove a Clave
	IplImage* clave = cvLoadImage("Elementos/claveG.jpg", 0);
	cvThreshold(clave,clave,230,255,0);
	
	CvPoint		minloc; 
	CvPoint		maxloc;
	double		minval, maxval;

	IplImage* result = cvCreateImage(cvSize(pentagrama->width - clave->width + 1, pentagrama->height - clave->height + 1),32,1);
	
	cvMatchTemplate(pentagrama,clave,result,1);
	cvMinMaxLoc( result, &minval, &maxval, &minloc, &maxloc, 0 );
	
	for (int i=1; i!=(minloc.y+clave->height); i++){
		for (int j=1; j!=(minloc.x+clave->width); j++){
			((uchar*)(pentagrama->imageData + i* pentagrama->widthStep))[j] = 255;
		}
	}
	
	//Remove a Clave
	clave = cvLoadImage("Elementos/c.jpg", 0);
	cvThreshold(clave,clave,230,255,0);

	result = cvCreateImage(cvSize(pentagrama->width - clave->width + 1, pentagrama->height - clave->height + 1),32,1);
	
	cvMatchTemplate(pentagrama,clave,result,1);
	cvMinMaxLoc( result, &minval, &maxval, &minloc, &maxloc, 0 );
	
	for (int i=(minloc.y); i!=(minloc.y+clave->height); i++){
		for (int j=(minloc.x); j!=(minloc.x+clave->width); j++){
			((uchar*)(pentagrama->imageData + i* pentagrama->widthStep))[j] = 255;
		}
	}

	return pentagrama;
}
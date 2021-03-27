#include "StdAfx.h"
#include "Segmentacao.h"

Segmentacao::Segmentacao(void)
{
}

Segmentacao::~Segmentacao(void)
{
}

/**************************************
*  A função criterio não pertence a   *
*  classe, ela serve apenas para a    *
*  utilização do cvSeqSort.           *
***************************************/
int criterio(const void* _a, const void* _b, void* userdata)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	int diff = *a - *b;
	return diff ;
}
void Segmentacao::detectaLinhas(IplImage* imgMapaBordas)
{
	int rho_houghLines = 1;
	int theta_houghLines = 180;
	int tresh = 300;
	int tamanho_linha = 150;

	CvMemStorage* storage = cvCreateMemStorage(0);	
	
	//Detecta os pares de linhas da partitura
	linhas = cvHoughLines2(imgMapaBordas,storage,CV_HOUGH_STANDARD,rho_houghLines,CV_PI/theta_houghLines,tresh,1,5);
	
	//Ordena as linhas de acordo com a função criterio
	cvSeqSort(linhas,criterio,0);
}

void Segmentacao::detectaPentagramas(IplImage* imgBinarizada)
{	
	/*int yLinha1 = this->getYLinha( (float*)cvGetSeqElem(this->linhas,0));
	int yLinha2 = this->getYLinha( (float*)cvGetSeqElem(this->linhas,2));
	int dist = yLinha2 - yLinha1;
*/
	CvMemStorage* memoria = cvCreateMemStorage(0);
	pentagramas = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(IplImage),memoria);

	int largura = imgBinarizada->width;
	int altura = imgBinarizada->height;
	int inicio = 0;
	int fim = 0;

	for( int i=0; i<this->linhas->total; i++ ){
		if( i%2 == 0 ){
			int yLinha1 = this->getYLinha( (float*)cvGetSeqElem(this->linhas,i));
			int yLinha2 = this->getYLinha( (float*)cvGetSeqElem(this->linhas,i+2));
			int yLinha3 = this->getYLinha( (float*)cvGetSeqElem(this->linhas,i+4));
			int dist1 = yLinha2 - yLinha1;
			int dist2 = yLinha3 - yLinha2;
			
			if( dist2 > (dist1+2) ){
				
				if( (i+2) >= this->linhas->total ){
					fim = altura;
				}else{
					fim = yLinha3 - ( dist2/2 );
				}
				
				cvSetImageROI(imgBinarizada, cvRect(0,inicio,imgBinarizada->width,fim-inicio));

				IplImage* imgAux = cvCloneImage(imgBinarizada);
				
				//Seta as dimensoes reais da imagem
				imgAux->width = imgBinarizada->width;
				imgAux->height = (fim-inicio);
				
				cvSeqPush(pentagramas,imgAux);
				cvResetImageROI(imgBinarizada);

				printf("Inicio= %u | Fim= %u total %u i %u\n", inicio, fim, this->linhas->total, i );
				inicio = fim;
			}

		}
	}
	
}

int Segmentacao::getYLinha(float* linha)
{		
	//Calula y da linha
	float rhoLinha = linha[0];
	float thetaLinha = linha[1];
	double aLinha = cos(thetaLinha); 
	double bLinha = sin(thetaLinha);
	int yLinha = cvRound((bLinha*rhoLinha) + 1000*(aLinha));	

	return yLinha;
}

CvSeq* Segmentacao::getLinhas()
{
	return linhas;
}

CvSeq* Segmentacao::getPentagramas()
{
	return pentagramas;
}
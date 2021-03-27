#include "StdAfx.h"
#include "Auxiliar.h"

Auxiliar::Auxiliar(void)
{
}

Auxiliar::~Auxiliar(void)
{
}
void Auxiliar::mostraImagem(char* nome,IplImage* imagem)
{
	cvNamedWindow(nome,1);
	cvShowImage(nome,imagem);
	//cvReleaseImage(&imagem);
}
void Auxiliar::mostraLinhas( IplImage* imagem, CvSeq* linhas )
{
	int tamanho_linha = 150;
	for( int i = 0; i < MIN(linhas->total,tamanho_linha); i++ )
	{

		float* line = (float*)cvGetSeqElem(linhas,i);
		float rho = line[0];
		float theta = line[1];
		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;

		pt1.x = cvRound(x0 + 10000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 10000*(-b));
		pt2.y = cvRound(y0 - (a));

		cvLine(imagem, pt1, pt2, CV_RGB(0,255,0),1, 8 );//desenha as linhas detectadas na imagem.
		
		this->mostraImagem("Linhas", imagem);

		printf("Valor de Y = %u\n",pt1.y);
		

	}
}

void Auxiliar::testaSeq()
{	
	CvMemStorage* memoriaNotas = cvCreateMemStorage(0);
	CvSeq* notas = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(CvPoint3D32f),memoriaNotas);

	CvPoint3D32f nota1 = cvPoint3D32f(50,2,4);
	CvPoint3D32f nota2 = cvPoint3D32f(200,4,5);
	CvPoint3D32f nota3 = cvPoint3D32f(10,0,3);

	cvSeqPush(notas, &nota1);
	cvSeqPush(notas, &nota2);
	cvSeqPush(notas, &nota3);

	for( int i=0; i<notas->total; i++ ){
		CvPoint3D32f* aux = (CvPoint3D32f*)cvGetSeqElem(notas,i);
		printf( "x = %f nota = %f intervalo = %f\n", aux->x, aux->y, aux->z );
	}

//	cvSeqSort(notas, criterioPontos,0);
	printf( "\n ================================================\n " );
	for( int i=0; i<notas->total; i++ ){
		CvPoint3D32f* aux = (CvPoint3D32f*)cvGetSeqElem(notas,i);
		printf( "x = %f nota = %f intervalo = %f\n", aux->x, aux->y, aux->z );
	}
}

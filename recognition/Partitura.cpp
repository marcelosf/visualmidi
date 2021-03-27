#include "StdAfx.h"
#include "Partitura.h"
#include "Pentagrama.h"
#include "XML.h"

Partitura::Partitura(void)
{
}

Partitura::~Partitura(void)
{
}
void Partitura::interpretaPartitura(CvSeq* pentagramas)
{
	CvMemStorage* memoriaNotasPartitura = cvCreateMemStorage(0);
	elementosPartitura = cvCreateSeq(CV_SEQ_ELTYPE_GENERIC,sizeof(CvSeq),sizeof(CvPoint3D32f),memoriaNotasPartitura);

	IplImage* imgPentagrama;
	for( int pentCount=0; pentCount< pentagramas->total; pentCount++ ){
		imgPentagrama = (IplImage*)cvGetSeqElem(pentagramas, pentCount);
		Pentagrama pent = Pentagrama();
		pent.interpretaPentagrama(imgPentagrama);
		for( int i=0; i<pent.getElementosPentagrama()->total; i++ ){
			CvPoint3D32f* aux = (CvPoint3D32f*)cvGetSeqElem(pent.getElementosPentagrama(),i);			
			CvPoint3D32f nota = cvPoint3D32f(aux->x, aux->y, aux->z);
			cvSeqPush(elementosPartitura, &nota);
		}
	}

	printf( "\n ================================================\n " );
	for( int i=0; i<elementosPartitura->total; i++ ){
		CvPoint3D32f* aux3 = (CvPoint3D32f*)cvGetSeqElem(elementosPartitura,i);
		printf( "x = %f nota = %f intervalo = %f\n", aux3->x, aux3->y, aux3->z );
	}

	XML xml = XML();
	xml.gerarXML(elementosPartitura);
}
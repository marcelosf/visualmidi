// Visão.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "Imagem.h"
#include "PreProcessamento.h";
#include "Segmentacao.h";
#include "Auxiliar.h";
#include "Partitura.h";

#include "iostream";
#include "fstream";
using std::ofstream;

//fazer herança 

int _tmain(int argc, _TCHAR* argv[])
{
	
	Imagem objeto = Imagem();
	objeto.capturarImagem();
	
	Auxiliar aux = Auxiliar();

	
	objeto.trataImagem( objeto.getImgOriginal(), 827 );

	objeto.detectaLinhas(objeto.getImgMapaBordas());
	objeto.getLinhas();
	
	//aux.mostraLinhas(objeto.getImgBinarizada(), objeto.getLinhas());
	//aux.mostraImagem("Partitura", objeto.getImgOriginal());

	aux.testaSeq();
	objeto.detectaPentagramas(objeto.getImgBinarizada());
	/*
	IplImage* imgAux = (IplImage*)cvGetSeqElem(objeto.getPentagramas(),0);
	aux.mostraImagem("TESTE", imgAux);
	
	imgAux = (IplImage*)cvGetSeqElem(objeto.getPentagramas(),1);
	aux.mostraImagem("TESTE2", imgAux);

	imgAux = (IplImage*)cvGetSeqElem(objeto.getPentagramas(),2);
	aux.mostraImagem("TESTE3", imgAux);
	
	imgAux = (IplImage*)cvGetSeqElem(objeto.getPentagramas(),3);
	aux.mostraImagem("TESTE4", imgAux);	
	*/

	Partitura p = Partitura();
	p.interpretaPartitura(objeto.getPentagramas());
	cvWaitKey(0);
	
	cvDestroyAllWindows();
}
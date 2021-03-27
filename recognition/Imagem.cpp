#include "StdAfx.h"
#include "Imagem.h"

Imagem::Imagem(void)
{
}

Imagem::~Imagem(void)
{
}
void Imagem::capturarImagem()
{
	imgOriginal = cvLoadImage("imagem.jpg",1);//carregar uma figura;
}
void Imagem::carregarImagem(IplImage* img)
{
	imgOriginal = img;//carregar uma figura;
	//imgOriginal = cvCloneImage( img );

}
IplImage* Imagem::getImgOriginal()
{
	return imgOriginal;
}
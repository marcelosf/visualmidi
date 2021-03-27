#include "StdAfx.h"
#include "Aquisicao.h"

Aquisicao::Aquisicao(void)
{
}

Aquisicao::~Aquisicao(void)
{
}

void Aquisicao::capturarImagem()
{
	imgCapturada = cvLoadImage("imagem.JPG",1);//carregar uma figura;
}

IplImage* Aquisicao::getImgCapturada()
{
	return imgCapturada;
}

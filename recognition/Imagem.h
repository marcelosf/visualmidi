#pragma once

#include "PreProcessamento.h";
#include "Segmentacao.h";

class Imagem:public PreProcessamento, public Segmentacao
{	
private:
	IplImage* imgOriginal;
public:
	Imagem(void);
	~Imagem(void);
	void capturarImagem();
	void carregarImagem(IplImage* img);
	IplImage* getImgOriginal();
};

#pragma once

class PreProcessamento
{
private:
	IplImage* imgBinarizada;
	IplImage* imgMapaBordas;
	IplImage* imgTonsCinza;
public:	
	PreProcessamento(void);
	~PreProcessamento(void);
	void trataImagem(IplImage* imgOriginal, int imgLargura);
	IplImage* getImgBinarizada();
	IplImage* getImgMapaBordas();
	IplImage* getImgTonsCinza();
};

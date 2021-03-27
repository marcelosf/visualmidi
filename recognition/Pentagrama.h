#pragma once

class Pentagrama
{
private:
	CvSeq* elementosPentagrama;
public:
	Pentagrama(void);
	~Pentagrama(void);
	void interpretaPentagrama(IplImage* pentagrama);
	int getLinhaMeio(CvSeq* linhas);
	int getDistLinhas(CvSeq* linhas);
	int calculaNota(float linhaMeio, float distLinha, float posY);
	int getDuracaoPausa(int valor);
	IplImage* limpaPentagrama( IplImage* pentagrama );
	CvSeq* getElementosPentagrama();
};

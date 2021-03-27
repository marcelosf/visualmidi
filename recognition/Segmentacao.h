#pragma once

class Segmentacao
{
private:
	CvSeq* linhas;
	CvSeq* pentagramas;
public:
	Segmentacao(void);
	~Segmentacao(void);
	void detectaLinhas(IplImage* imgMapaBordas);
	void detectaPentagramas(IplImage* imgBinarizada);
	CvSeq* getLinhas();
	CvSeq* getPentagramas();
	int getYLinha(float* linha);
};

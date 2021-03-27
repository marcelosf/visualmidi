#pragma once

class DuracaoNota
{
private:
	CvSeq* tiposDuracao;
public:
	DuracaoNota(void);
	~DuracaoNota(void);
	CvSeq* getTiposDuracao();
	int verificaDuracaoNota(IplImage* imgNota, int x, int width, int height);
	double pghMatchShapes(CvSeq *shape1, CvSeq *shape2);
};

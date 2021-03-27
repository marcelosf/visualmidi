#pragma once

class Auxiliar
{
public:
	Auxiliar(void);
	~Auxiliar(void);
	void mostraImagem(char* nome, IplImage* imagem);
	void mostraLinhas( IplImage* imagem, CvSeq* linhas );
	void testaSeq();
};

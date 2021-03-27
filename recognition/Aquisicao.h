#pragma once

class Aquisicao
{

private:
	IplImage* imgCapturada;// imagem capturada
public:
	Aquisicao(void);
	~Aquisicao(void);

	void capturarImagem();
	IplImage* getImgCapturada();
};


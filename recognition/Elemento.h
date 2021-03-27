#pragma once

class Elemento
{
private:
	CvSeq* elementos;
public:
	Elemento(void);
	~Elemento(void);
	CvSeq* getElementos();
};

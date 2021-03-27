#pragma once

class Partitura
{
private:
	CvSeq* elementosPartitura;
public:
	Partitura(void);
	~Partitura(void);
	void interpretaPartitura(CvSeq* pentagramas);
};

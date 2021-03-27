#pragma once

# include "iostream"
# include "fstream"

using std::ofstream;


class XML
{	
public:
	XML(void);
	
	~XML(void);

	void gerarXML(CvSeq *seqElementos);
};

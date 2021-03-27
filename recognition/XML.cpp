//Classe para gera��o do arquivo MusicXML.


#include "StdAfx.h"
#include "XML.h"

ofstream arquivoXML;

XML::XML(void)
{
}

XML::~XML(void)
{
}
/************************************************************
*	Esta estrutura armazena	os dados de dura��o gr�fica		*
*	da nota e dura��o l�gica do MIDI.						*
*************************************************************/
struct TDuracao
{
	char *duracaoNota;			//dura��o gr�fica
	int   duracaoMIDI;			//dura��o l�gica
};

/***********************************************************************************
*	Esta fun��o recebe como entrada um valor que corresponde					   *
*	a posi��o da nota em rela��o ao pentagrama e o converte na nota correspondente.*
***********************************************************************************/
char getNota(int elemento)
{
	elemento = elemento % 7;
	return elemento;
}

/**********************************************************************************
*	Esta fun��o � respons�vel pela transforma��o de um valor inteiro em sua		  *
*	respectiva nota. Este valor pode variar de -7 � 7.							  *
***********************************************************************************/
char lookupTableNota(int elemento)
{
	switch (elemento)
	{	
		
		case -7 :
			return 'B';
			break;
		case -6 :
			return 'A';
			break;
		case -5 :
			return 'G';
			break;
		case -4 :
			return 'F';
			break;
		case -3 :
			return 'E';
			break;
		case -2 :
			return 'D';
			break;
		case -1 :
			return 'C';
			break;
		case 0:
			return 'B';
			break;
		case 1:
			return 'A';
			break;
		case 2:
			return 'G';
			break;
		case 3:
			return 'F';
			break;
		case 4:
			return 'E';
			break;
		case 5:
			return 'D';
			break;
		case 6:
			return 'C';
			break;
		case 7:
			return 'B';
			break;
	}
	
	return 'X';
}

/************************************************************************************
*	Esta fun��o � respons�vel pela transforma��o de um valor em seu respectivo		*
*	de dura��o de uma nota. O vari�vel de entrada pode assumir os valores			*
*   1  - semibreve;																	*	
*	2  - m�nima;																	*
*	4  - sem�nima;																	*
*	8  - colcheia;																	*
*   16 - semicolcheia;																*
*	32 - fusa;																		*
*	64 - semifusa;																	*
*************************************************************************************/
TDuracao lookupTableDuracao(int elemento)
{
	TDuracao drc;
	switch (elemento)
	{
		case 1:
			drc.duracaoNota = "whole";		//drc.duracao � a representa��o gr�fica da dura��o.
			drc.duracaoMIDI = 64;			//drc.duracaoMIDI � a representa��o l�gica da dura��o.
			break;
		case 2:
			drc.duracaoNota = "half";
			drc.duracaoMIDI = 32;
			break;
		case 4:
			drc.duracaoNota = "quarter";
			drc.duracaoMIDI = 16;
			break;
		case 8:
			drc.duracaoNota = "eighth";
			drc.duracaoMIDI = 8;
			break;
		case 16:
			drc.duracaoNota = "16th";
			drc.duracaoMIDI = 4;
			break;
		case 32:
			drc.duracaoNota = "32nd";
			drc.duracaoMIDI = 2;
			break;
		case 64:
			drc.duracaoNota = "64th";
			drc.duracaoMIDI = 1;
			break;
		default:
			drc.duracaoNota = "Null";
			drc.duracaoMIDI = 0;
			break;
	}

		return drc;
}

/************************************************************************************
*	A fun��o lookupTableRegi�o � respons�vel por determinar a regi�o da nota		*
*	considerando a sua posi��o em rela��o ao pentagrama. As regi�es contempladas	*
*	podem variar entre 1 e 6. Estas s�o as regi�es comumente utilizadas em			*
*   partituras.																		*
*************************************************************************************/
int lookupTableRegiao(int nota)
{
											//caso o valor passado n�o esteja dentro de nenhum dos intervalos
	if((nota >= -7)&(nota <= -1))				//� retornado o valor 777 que � considerado um erro.
		return 5;
	if((nota >= -2)&(nota <= 6))
		return 4;
	if((nota >= 5)&(nota <= 13))
		return 3;
	if((nota >= 12)&(nota <= 20))
		return 2;
	if((nota >= 19)&(nota <= 27))
		return 1;						
}											

/************************************************************************************
*	A fun��o Inserir cabe�alho acrescenta o cabe�alho ao arquivo XML.				*
*************************************************************************************/
void inserirCabecalho()
{
	arquivoXML.open("Partitura.XML");				//cria ou abre um arquivo j� existente para edi��o.

	arquivoXML << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	arquivoXML << "\t<!DOCTYPE score-partwise PUBLIC\n";
	arquivoXML << "\t\"-//Recordare//DTD MusicXML 2.0 Partwise//EN\"\n";
	arquivoXML << "\"http://www.musicxml.org/dtds/partwise.dtd\">\n";

	arquivoXML.close();								//fecha o arquivo ap�s a edi��o.	
}

/************************************************************************************
*	O m�todo inserirDefini��o define o nome da partitura e o n�mero de p�ginas.		*
*************************************************************************************/
void inserirDefinicao(char nome [10], int id)
{
	arquivoXML.open("Partitura.XML",std::ios_base::app);
	
	arquivoXML << "<score-partwise version=\"2.0\">\n";
	arquivoXML << "\t<part-list>\n";
	arquivoXML << "\t\t<score-part id=\"P";
	arquivoXML << id;
	arquivoXML << "\">\n"; 
	arquivoXML << "\t\t\t<part-name>";
	arquivoXML << nome;
	arquivoXML << "</part-name>\n";
	arquivoXML << "\t\t</score-part>\n";
	arquivoXML << "\t</part-list>\n"; 
	arquivoXML << "\t<part id=\"P";
	arquivoXML << id;
	arquivoXML << "\">\n";
	
	arquivoXML.close();
}

/************************************************************************************
*	O m�todo insereCompasso acrescenta um novo compasso � partitura.				*
*************************************************************************************/
void insereCompasso(int numCompasso)
{
	arquivoXML.open("Partitura.XML",std::ios_base::app);

	arquivoXML << "\t\t<measure number=\"";            
    arquivoXML << numCompasso;
    arquivoXML << "\">\n";
	
	arquivoXML.close();
}

/************************************************************************************
*	O m�todo insereAtributos tem por objetivo determinar os seguintes atributos:	*
*		- divis�o l�gica da partitura(utilizada para gera��o do arquivo MIDI.		*
*		- determina��o do n�mero de acidentes na clave.								*
*		- determina��o da formula de compasso:										*
*				*formCn - numerador da formula de compasso.							*
*				*formCd - denominador da formula de compasso.						*
*		- determina��o da clave.													*
*************************************************************************************/
void insereAtributos(int divisao, int acidentes, int formCn, int formCd, char clave, int linhaClave)
{
	arquivoXML.open("Partitura.XML",std::ios_base::app);

	arquivoXML << "\t\t\t<attributes>\n";
       
    arquivoXML << "\t\t\t\t<divisions>";
	arquivoXML << divisao;
	arquivoXML <<"</divisions>\n";
       
    arquivoXML << "\t\t\t\t<key>\n";
    arquivoXML << "\t\t\t\t\t<fifths>";
	arquivoXML << acidentes;
	arquivoXML << "</fifths>\n";
    arquivoXML << "\t\t\t\t</key>\n";
       
    arquivoXML << "\t\t\t\t<time>\n";
    arquivoXML << "\t\t\t\t\t<beats>";
	arquivoXML << formCn;
	arquivoXML <<"</beats>\n";
    arquivoXML << "\t\t\t\t\t<beat-type>";
	arquivoXML << formCd;
	arquivoXML << "</beat-type>\n";
    arquivoXML << "\t\t\t\t</time>\n";
       
    arquivoXML << "\t\t\t\t<clef>\n";
    arquivoXML << "\t\t\t\t\t<sign>";
	arquivoXML << clave;
	arquivoXML << "</sign>\n";
    arquivoXML << "\t\t\t\t\t<line>2</line>\n";
    arquivoXML << "\t\t\t\t</clef>\n";
       
    arquivoXML << "\t\t\t</attributes>\n";
	
	arquivoXML.close();
}

/************************************************************************************
*	O m�todo insereNotas acrescenta notas dentro de um compasso.					*
*		-numNota: n�mero que corresponde a nota.									*
*		-tipo: tempo de dura��o da nota.											*
*************************************************************************************/
void inserirNotas(int numNota,int tipo)
{
	
	arquivoXML.open("Partitura.XML",std::ios_base::app);

	TDuracao tempo = lookupTableDuracao(tipo);
	char nota = lookupTableNota(getNota(numNota));
	int oitava = lookupTableRegiao(numNota);
	
	arquivoXML << "\t\t\t<note>\n";
    arquivoXML << "\t\t\t\t<pitch>\n";
    arquivoXML << "\t\t\t\t\t<step>";
	arquivoXML << nota;
	arquivoXML << "</step>\n";
    arquivoXML << "\t\t\t\t\t<octave>";
	arquivoXML << oitava;
	arquivoXML << "</octave>\n";
    arquivoXML << "\t\t\t\t</pitch>\n";
    arquivoXML << "\t\t\t\t<duration>";
	arquivoXML << tempo.duracaoMIDI;
	arquivoXML << "</duration>\n";
    arquivoXML << "\t\t\t\t<type>";
	arquivoXML << tempo.duracaoNota;
	arquivoXML << "</type>\n";
    arquivoXML << "\t\t\t</note>\n";
	
	arquivoXML.close();
}
/************************************************************************************
*	O m�todo inserePausa acrescenta pausas dentro de um compasso.					*											*
*************************************************************************************/
void inserePausa(int pausa)
{
	TDuracao tempo = lookupTableDuracao(pausa);
	arquivoXML.open("Partitura.XML",std::ios_base::app);
	
	arquivoXML << "\t\t\t<note>\n";
	arquivoXML << "\t\t\t\t<rest/>\n";
	arquivoXML << "\t\t\t\t<duration>";
	arquivoXML << tempo.duracaoMIDI;
	arquivoXML << "</duration>\n";
	arquivoXML <<"\t\t\t</note>\n";

	arquivoXML.close();
}

/************************************************************************************
*	O m�todo encerrarCompasso termina o compasso com uma barra.						*
************************************************************************************/
void encerrarCompasso()
{
	arquivoXML.open("Partitura.XML",std::ios_base::app);
	arquivoXML << "\t\t</measure>\n";
	arquivoXML.close();
}

/************************************************************************************
*	O m�todo encerrarPartitura insere as tags para o termino da partitura.			*
*************************************************************************************/
void encerrarPartitura()
{
	arquivoXML.open("Partitura.XML",std::ios_base::app);
	arquivoXML << "\t</part>\n";
	arquivoXML << "</score-partwise>\n";
	arquivoXML.close();
}

/************************************************************************************
*	gerarXML � a fun��o membro da classe XML. Seu objetivo � gerar um arquivo XML	*
*	obtendo como entrada um vetor com as notas interpretadas atrav�s da imagem de	*
*	uma partitura formatada.														*
*************************************************************************************/
void XML::gerarXML(CvSeq *seqElementos)
{
																		
	CvPoint3D32f *elementos;										//estrutura que contem os elementos.
	inserirCabecalho();												//Insere o cabe�alho para o arquivo XML.
	inserirDefinicao("",1);											//Insere Defini��o do arquivo.
																	
																			
	int contCompasso = 1;											//contagem da numera��o dos compassos.
	float contElementosPorCompasso = 0;								//contador para verifica��o do n�mero limite de elementos dentro do compasso.
	for (int i=0;i<seqElementos->total;i++)						
	{
											
		if(i == 0)													
		{															//se ainda n�o tiver inserido nenhum elemento, insere o compasso
			insereCompasso(contCompasso);							//a clave e os acidentes.
			insereAtributos(16,0,4,4,'G',2);				
		}
		if(contElementosPorCompasso >= 4)							//controle para finalizar cada compasso quando estiver completo.
		{
			contElementosPorCompasso = 0;						
			contCompasso++;											//incrementa o n�mero do compasso.
			encerrarCompasso();
			insereCompasso(contCompasso);							//inicia um novo compasso.
		}


		elementos = (CvPoint3D32f*)cvGetSeqElem(seqElementos,i);
		
		
		if(elementos->y == 999)										//se o valor de elementos->y for igual a 999, significa					
			inserePausa((int)elementos->z);							//que este � uma pausa.
		else
			inserirNotas((int)elementos->y,(int)elementos->z);	                        //inser��o das notas.
		
		contElementosPorCompasso = contElementosPorCompasso + (4/elementos->z);			//incrementa o n�mero permitido de elementos dentro do compasso atual.
	}
	encerrarCompasso();	
	encerrarPartitura();						
	arquivoXML.close();													//termina a edi��o do arquivo.																						
}
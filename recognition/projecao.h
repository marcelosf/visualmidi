/*Projeção vertical e horizontal

Armazena em um vetor a projeção vertical ou horizontal da imagem de entrada.
*/



#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

class projecao{
private:

	CvSeq* seq;
	CvMemStorage* storage;
	IplImage* imagem;

public:

	void projecao(IplImage* img);
	void calcProjVertical();
	void calcProjHorizontal();
	void plotProjVertical();
	void plotProjHorizontal();
	~projecao(void);
	
};



void projecao::projecao(IplImage *img)
{
	imagem = cvCreateImage(cvSize(img->width,img->height),8,1);
	imagem = img;
	storage = cvCreateMemStorage(0);
	seq = cvCreateSeq(CV_32SC1,sizeof(CvSeq),sizeof(int),storage);
}

void projecao::calcProjVertical(CvSeq* projVertical )
{
	for (int y=0; y <= imagem->height; y++)
	{
		for (int x=0; x <= imagem->width; x++)
		{
			uchar pixel = ((uchar*)imagem->imageData + y * imagem->widthStep))[x];
			if (pixel == 0)
				cvSeqPush(seq,&pixel);
			projVertical = seq;
		}
	}
	
}
#pragma once
#include "ImgDib.h"
class HuffmanCoding :public ImgDib
{
public:
	//Ƶ��
	double *dProba;

private:


public:
	HuffmanCoding();
	HuffmanCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	~HuffmanCoding();
	BOOL coding();
};


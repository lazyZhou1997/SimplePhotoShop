#pragma once
#include "imgdib.h"
class LosslessPredictiveCoding :
	public ImgDib
{
	public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

private:
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;

	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
	
public:
	LosslessPredictiveCoding();

	LosslessPredictiveCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//һ������Ԥ��
	BOOL xOneOrderLinearPrediction(double a);

	//һ������Ԥ��
	BOOL yOneOrderLinearPrediction(double a);

	//��������Ԥ��
	BOOL twoOrderLinearPrediction(double a1,double a2);

	//��������Ԥ��
	BOOL threeOrderLinearPrediction(double a1,double a2,double a3);

	~LosslessPredictiveCoding();
};


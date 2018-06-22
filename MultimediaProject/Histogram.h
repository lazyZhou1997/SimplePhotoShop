#pragma once
#include "ImgDib.h"
class Histogram
	:public ImgDib
{
public://ֱ��ͼ����
	int m_histArray[256];
	int m_histArrayY[256];
	int m_histArrayCb[256];
	int m_histArrayCr[256];

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
	//���������Ĺ��캯��
	Histogram();

	//�������Ĺ��캯��
	Histogram(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//��������
	~Histogram();

	//ͳ�ƻҶ�ͼ���ֱ��ͼ
	void computeHistGray();

	//ͳ�Ʋ�ɫͼ������ֱ��ͼ
	void computeHistBrightness();

	//ֱ��ͼ����
	void histogram();
};


#include "ImgDib.h"

class BinaryImg :public ImgDib
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

	// Dither��������м����
	int D[100][100];
	int U[100][100];

public:
	// ���������Ĺ��캯��
	BinaryImg();
	// ���������Ĺ��캯��
	BinaryImg(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	// ����ֵ��ֵ������
	BOOL singleThreshold(int th);


	// Dither����
	BOOL dither(int Dn);

	// Ordered Dither����
	BOOL orderedDither(int Dn);

	// ��дGetDimension����
	CSize GetDimensions();

	// ��ʼ��Dither����
	BOOL initDitherMx(int n);

	// ��������
	~BinaryImg();

private:
	
};

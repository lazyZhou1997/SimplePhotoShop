#include "imgdib.h"
class GrayTrans: 
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
	// ���������Ĺ��캯��
	GrayTrans();

	// �������Ĺ��캯��
	GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	// ��������
	~GrayTrans();

	// RGBToHSI()����
	BOOL RGBToHSI();

	// RGBToYCbCr()����
	BOOL RGBToYCbCr();
};

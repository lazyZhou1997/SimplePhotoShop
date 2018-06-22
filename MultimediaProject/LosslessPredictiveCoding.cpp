#include "StdAfx.h"
#include "LosslessPredictiveCoding.h"

LosslessPredictiveCoding::LosslessPredictiveCoding()
{
	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��

	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0

	m_nBitCountOut = 0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0
}

LosslessPredictiveCoding::LosslessPredictiveCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{

	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��

	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0

	m_nBitCountOut = 0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0
}


LosslessPredictiveCoding::~LosslessPredictiveCoding()
{
	//�ͷ����ͼ��λͼ���ݻ�����
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}

	//�ͷ����ͼ����ɫ��
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
}

BOOL LosslessPredictiveCoding::xOneOrderLinearPrediction(double a){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	//�ͷžɵ����ͼ�񻺳���
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//���ͼ��λ��Ϊ����ͼ��λ��
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	
	//һ������Ԥ��ѹ������
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//Ԥ�����ֵ��Ԥ��ֵ

	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			if(j==0)
			{
				f=*(m_pImgData + i*lineByteOut + j);
				e=0;
			}
			else
			{
				f=(int)(a*(*(m_pImgData + i*lineByteOut + j-1)));
				e=*(m_pImgData + i*lineByteOut + j)-f;
				*(m_pImgDataOut + i*lineByteOut + j)=(int)(e-128)/2+128;

			}
		}
	}

	return TRUE;
}

BOOL LosslessPredictiveCoding::yOneOrderLinearPrediction(double a){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	//�ͷžɵ����ͼ�񻺳���
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//���ͼ��λ��Ϊ����ͼ��λ��
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	
	//һ������Ԥ��ѹ������
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//Ԥ�����ֵ��Ԥ��ֵ

	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			if(i==0)
			{
				f=*(m_pImgData + i*lineByteOut + j);
				e=0;
			}
			else
			{
				f=(int)(a*(*(m_pImgData + (i-1)*lineByteOut + j)));
				e=*(m_pImgData + i*lineByteOut + j)-f;
				*(m_pImgDataOut + i*lineByteOut + j)=(int)(e-128)/2+128;

			}
		}
	}

	return TRUE;
}

BOOL LosslessPredictiveCoding::twoOrderLinearPrediction(double a1,double a2){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	//�ͷžɵ����ͼ�񻺳���
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//���ͼ��λ��Ϊ����ͼ��λ��
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];

	//��������Ԥ��ѹ������
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//Ԥ�����ֵ��Ԥ��ֵ

	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			if(i==0 || j==0)
			{
				f=*(m_pImgData + i*lineByteOut + j);
				e=0;
			}
			else
			{
				f=(int)(a1**(m_pImgData + i*lineByteOut + j-1)+a2**(m_pImgData + (i-1)*lineByteOut + j));
				e=*(m_pImgData + i*lineByteOut + j)-f;
				*(m_pImgDataOut + i*lineByteOut + j)=(int)(e-256)/2+256;

			}
		}
	}

	return TRUE;
}


BOOL LosslessPredictiveCoding::threeOrderLinearPrediction(double a1,double a2,double a3){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	//�ͷžɵ����ͼ�񻺳���
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//���ͼ��λ��Ϊ����ͼ��λ��
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];

	//��������Ԥ��ѹ������
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//Ԥ�����ֵ��Ԥ��ֵ

	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			if(i==0 || j==0)
			{
				f=*(m_pImgData + i*lineByteOut + j);
				e=0;
			}
			else
			{
				f=(int)(a1**(m_pImgData + i*lineByteOut + j-1)+a2**(m_pImgData + (i-1)*lineByteOut + j)+a3**(m_pImgData + (i-1)*lineByteOut + j-1));
				e=*(m_pImgData + i*lineByteOut + j)-f;
				*(m_pImgDataOut + i*lineByteOut + j)=(int)(e-384)/2+384;

			}
		}
	}


	return TRUE;
}


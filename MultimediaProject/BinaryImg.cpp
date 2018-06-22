#include "stdafx.h"
#include "BinaryImg.h"
/***********************************************************************
* �������ƣ�
* BinaryImg()
*
*˵�����޲����Ĺ��캯������ʼ����Ա����
***********************************************************************/
BinaryImg::BinaryImg()
{
	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��

	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0

	m_nBitCountOut = 0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0

}

/***********************************************************************
* �������ƣ�
* BinaryImg()
*
*����������
*  CSize size -ͼ���С�����ߣ�
*  int nBitCount  -λ��
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ����ָ��
*
*����ֵ��
*   ��
*
*˵����������Ϊ�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��
*      ��λͼ���ݣ�����ImgCenterDib()�Ի����Ա��ʼ��������ʼ���������
*      ���ݳ�Ա
***********************************************************************/
BinaryImg::BinaryImg(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{

	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��

	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0

	m_nBitCountOut = 0;//���ͼ��λ��Ϊ0

	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0
}

/***********************************************************************
* �������ƣ�
*   ~BinaryImg()
*
*˵���������������ͷ���Դ
***********************************************************************/

BinaryImg::~BinaryImg()
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

/***********************************************************************
* �������ƣ�GetDimensions()
*  
* ����ֵ��
*     CSize���ͣ����ͼ��Ŀ����ͼ��ĸߣ�
*
* ˵������д�����GetDimensions()
***********************************************************************/
CSize BinaryImg::GetDimensions(){
	return CSize(m_imgWidthOut, m_imgHeightOut);
}

/***********************************************************************
* �������ƣ�singleThreshold(int th)
*
* ���������
*		int th - �û������ĵ���ֵ
*
* ����ֵ��
*     1Ϊ�ɹ���0Ϊʧ��
*
* ˵�����û���������ֵ����ͼ����е���ֵ��ֵ������
***********************************************************************/
BOOL BinaryImg::singleThreshold(int th){
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

	//���ͼ��λ���(8bit)
	//m_nBitCountOut = m_nBitCount;
	m_nBitCountOut = 1;


	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	//if (m_nColorTableLengthOut != 0){
	//	m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	//	memcpy(m_lpColorTableOut, m_lpColorTable,
	//		sizeof(RGBQUAD)*m_nColorTableLengthOut);
	//}

	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		m_lpColorTableOut[0].rgbBlue = 0;
		m_lpColorTableOut[0].rgbGreen = 0;
		m_lpColorTableOut[0].rgbRed = 0;
		m_lpColorTableOut[0].rgbReserved = 0;
		m_lpColorTableOut[1].rgbBlue = 255;
		m_lpColorTableOut[1].rgbGreen = 255;
		m_lpColorTableOut[1].rgbRed = 255;
		m_lpColorTableOut[1].rgbReserved = 0;
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	//int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	//int lineByteOut = (m_imgWidth*m_nBitCountOut + 3) / 4 * 4;
	int lineByteOut = ((m_imgWidthOut + 31) / 32) * 4;

	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//��ֵ������
	for (int i = 0; i < m_imgHeight; ++i){
		//for (int j = 0; j < m_imgWidth; ++j){
		for (int j = 0; j < lineByteOut;++j){
			//if (*(m_pImgData + i*lineByteOut + j)>th) *(m_pImgDataOut + i*lineByteOut + j) = 255;
			//if (*(m_pImgData + i*lineByte + j)>th) *(m_pImgDataOut + i*lineByte + j) = 1;
			//else *(m_pImgDataOut + i*lineByteOut + j) = 0;
			unsigned char temp_data = 0;
			for (int k = 0; k < 8; k++)
			{
				if (j * 8 + k < m_imgWidth)
				{
					int temp_value = 0;
					if(*(m_pImgData + i*lineByte + j*8+k)>th)
					{
						temp_value = 1 << (7 - k);
						temp_data += temp_value;
					}
				}
			}
			*(m_pImgDataOut + i*lineByteOut + j) = temp_data;
		}
	}
	return TRUE;
}

/***********************************************************************
* �������ƣ�initDitherMx(int n)
*
* ���������
*		int n - �û�������Dither�����С
*
* ����ֵ��
*     1Ϊ�ɹ���0Ϊʧ��
*
* ˵�����û�����Dither�����С������Dither����D
***********************************************************************/
BOOL BinaryImg::initDitherMx(int n){
	// �����С������2�ı���
	if (n % 2 != 0 || n<2)
		return FALSE;

	if (n == 2){
		D[0][0] = 0;
		D[0][1] = 2;
		D[1][0] = 3;
		D[1][1] = 1;
		return TRUE;
	}
	else{
		initDitherMx(n / 2);
		for (int i = 0; i<n / 2; i++){
			for (int j = 0; j<n / 2; j++){
				D[i][j] = 4 * D[i][j];
			}
		}
		for (int i = n / 2; i<n; i++){
			for (int j = 0; j<n / 2; j++){
				D[i][j] = D[i - n / 2][j] + 3 * U[i][j];
			}
		}
		for (int i = 0; i<n / 2; i++){
			for (int j = n / 2; j<n; j++){
				D[i][j] = D[i][j - n / 2] + 2 * U[i][j];
			}
		}
		for (int i = n / 2; i<n; i++){
			for (int j = n / 2; j<n; j++){
				D[i][j] = D[i - n / 2][j - n / 2] + U[i][j];
			}
		}
	}
	return TRUE;
}

/***********************************************************************
* �������ƣ�dither(int Dn)
*
* ���������
*		int Dn - �û�������Dither�����С
*
* ����ֵ��
*     1Ϊ�ɹ���0Ϊʧ��
*
* ˵�����û�����Dither�����С����ͼ�����Dither�任
***********************************************************************/
BOOL BinaryImg::dither(int Dn){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	// ֻ�����СΪ2�ı�����Dither����
	if (Dn%2!=0 || Dn<2)
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

	//���ͼ��λ���(8bit)
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ������Dn��
	m_imgWidthOut = m_imgWidth*Dn;
	m_imgHeightOut = m_imgHeight*Dn;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int lineByteOut = (m_imgWidthOut*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//Indexes
	int i = 0, j = 0, m = 0, n = 0, x = 0, y = 0, a = 0, b = 0;

	// ������ɫ
	double T = 256.0 / (Dn*Dn + 1);
	// ��ӳ��
	for (i = 0; i < m_imgHeight; ++i){
		for (j = 0; j < m_imgWidth; ++j){
			*(m_pImgData + i*lineByte + j) = (int)(*(m_pImgData + i*lineByte + j) / T);
		}
	}

	// U��D�����ʼ��
	for (int i = 0; i<Dn; i++){
		for (int j = 0; j<Dn; j++){
			U[i][j] = 1;
		}
	}
	for (int i = 0; i<Dn; i++){
		for (int j = 0; j<Dn; j++){
			D[i][j] = 0;
		}
	}

	// ���Dither����
	int error = initDitherMx(Dn);
	if (error == 0)
		return FALSE;

	// Dithering
	for (i = 0; i < m_imgHeight; ++i){
		for (j = 0; j < m_imgWidth; ++j){
			m = i*Dn;
			n = j*Dn;
			for (x=0; x < Dn; ++x){
				for (y=0; y < Dn; ++y){
					a = m + x;
					b = n + y;
					if (*(m_pImgData + i*lineByte + j)>D[x][y])
						*(m_pImgDataOut + a*lineByteOut + b) = 255;
					else
						*(m_pImgDataOut + a*lineByteOut + b) = 0;
				}
			}
		}
	}
	return TRUE;
}

BOOL BinaryImg::orderedDither(int Dn){
	// ֻ����Ҷ�
	if (m_nBitCount != 8)
		return FALSE;

	// ֻ�����СΪ2�ı�����Dither����
	if (Dn % 2 != 0 || Dn<2)
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

	//���ͼ��λ���(8bit)
	m_nBitCountOut = m_nBitCount;

	//������ɫ����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ�߲���
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//���ͼ��ÿ��������ռ���ֽ���
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int lineByteOut = (m_imgWidthOut*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//Indexes
	int i = 0, j = 0, m = 0, n = 0, x = 0, y = 0, a = 0, b = 0;

	// ������ɫ
	double T = 256.0 / (Dn*Dn + 1);
	// ��ӳ��
	for (i = 0; i < m_imgHeight; ++i){
		for (j = 0; j < m_imgWidth; ++j){
			*(m_pImgData + i*lineByte + j) = (int)(*(m_pImgData + i*lineByte + j) / T);
		}
	}

	// U��D�����ʼ��
	for (int i = 0; i<Dn; i++){
		for (int j = 0; j<Dn; j++){
			U[i][j] = 1;
		}
	}
	for (int i = 0; i<Dn; i++){
		for (int j = 0; j<Dn; j++){
			D[i][j] = 0;
		}
	}

	// ���Dither����
	int error = initDitherMx(Dn);
	if (error == 0)
		return FALSE;

	// Ordered dithering
	for (x = 0; x<m_imgHeight; x++){
		i = x%Dn;
		for (y = 0; y<lineByte; y++){
			j = y%Dn;
			if (*(m_pImgData + x*lineByte + y) - D[i][j]>0){
				*(m_pImgDataOut + x*lineByteOut + y) = 255;
			}
			else{
				*(m_pImgDataOut + x*lineByteOut + y) = 0;
			}
		}
	}
	return TRUE;
}
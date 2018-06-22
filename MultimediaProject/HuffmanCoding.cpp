#include "stdafx.h"
#include "HuffmanCoding.h"

/***********************************************************************
* �������ƣ�
* HuffmanCoding()
*
*˵�����޲����Ĺ��캯������ʼ����Ա����
***********************************************************************/
HuffmanCoding::HuffmanCoding()
{


}

/***********************************************************************
* �������ƣ�
* HuffmanCoding()
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
HuffmanCoding::HuffmanCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{
	dProba = new double[256];
}

/***********************************************************************
* �������ƣ�
*   ~HuffmanCoding()
*
*˵���������������ͷ���Դ
***********************************************************************/

HuffmanCoding::~HuffmanCoding()
{
	if (dProba != NULL){
		delete[] dProba;
		dProba = NULL;
	}
}

/***********************************************************************
* �������ƣ�coding()
*
*˵�������������뺯��
***********************************************************************/
BOOL HuffmanCoding::coding(){
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int i = 0, j = 0;
	// ����ֵ
	for ( i = 0; i < 256; i++)
	{
		dProba[i] = 0.0;
	}

	// ��������Ҷ�ֵ�ļ���
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{

			// ������1
			dProba[*(m_pImgData + lineByte * i + j)] += 1;
		}
	}

	int pixelSum = m_imgHeight*m_imgWidth;

	// ��������Ҷ�ֵ���ֵĸ���
	for (i = 0; i < 256; i++)
	{
		dProba[i] = (float)dProba[i] / pixelSum;
	}
	return TRUE;
}
#include "StdAfx.h"
#include "histogram.h"
#include "GrayTrans.h"
#include "math.h"

/***********************************************************************
* �������ƣ�
* Histogram()
*
*˵�����޲����Ĺ��캯������ʼ����Ա����
***********************************************************************/
Histogram::Histogram()
{
	//ֱ��ͼ������0
	for(int i=0;i<256;i++)
	{
    	m_histArray[i]=0;
		m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

/***********************************************************************
* �������ƣ�
* Histogram()
*
*����������
*  CSize size -ͼ���С�����ߣ�
*  int nBitCount  -ÿ������ռλ��
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
Histogram::Histogram(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImgDib(size, nBitCount, lpColorTable, pImgData)
{
	//ֱ��ͼ������0
	for(int i=0;i<256;i++)
	{
    	m_histArray[i]=0;
		m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

/***********************************************************************
* �������ƣ�
*   ~Histogram()

*
*˵���������������ͷ���Դ
***********************************************************************/
Histogram::~Histogram()
{
	//�ͷ����ͼ��λͼ���ݻ�����
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//�ͷ����ͼ����ɫ��
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}

/***********************************************************************
* �������ƣ�
* computeHistGray()
*
*˵�����Ҷ�ͼ��ͳ��ֱ��ͼ��m_histArray�д���˵�ǰͼ���ͳ������
***********************************************************************/
void Histogram::computeHistGray()
{
	//ֻ����Ҷ�ͼ��
	if(m_nBitCount!=8)
		return;

	//ѭ������
	int i,j;

	//ֱ��ͼ������0
	for(i=0;i<256;i++)
    	m_histArray[i]=0;

	//ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//�м����
	int temp;

	//ͳ�ƻҶ�ֱ��ͼ
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			temp=*(m_pImgData+i*lineByte+j);
		    m_histArray[temp]++;
		}
	}
}

/***********************************************************************
* �������ƣ�
* computeHistBrightness()
*
*˵������ɫͼ������ֱ��ͼ��m_histArray�д���˵�ǰͼ�������ͳ������
***********************************************************************/
void Histogram::computeHistBrightness()
{
	//��ɫͼ����Ч
	if(m_nBitCount!=24)
		return;

	//ѭ������
	int i,j;

	//ֱ��ͼ������0
	for(i=0;i<256;i++)
	{
    	m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

	//ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//�м����
	int tempY;
	int tempCb;
	int tempCr;

	//ͳ������ֱ��ͼ
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			tempY=0.11**(m_pImgData+i*lineByte+j*3+0)
				+0.59**(m_pImgData+i*lineByte+j*3+1)
				+0.30**(m_pImgData+i*lineByte+j*3+2)+0.5;

			tempCb=0.5**(m_pImgData+i*lineByte+j*3+0)
				+(-0.33)**(m_pImgData+i*lineByte+j*3+1)
				+(-0.17)**(m_pImgData+i*lineByte+j*3+2)+128+0.5;

			tempCr=(-0.08)**(m_pImgData+i*lineByte+j*3+0)
				+(-0.42)**(m_pImgData+i*lineByte+j*3+1)
				+0.5**(m_pImgData+i*lineByte+j*3+2)+128+0.5;

		    m_histArrayY[tempY]++;
			m_histArrayCb[tempCb]++;
			m_histArrayCr[tempCr]++;
		}
	}
}

/***********************************************************************
* �������ƣ�
* histogram()
*
*˵����ֱ��ͼ����
***********************************************************************/
void Histogram::histogram()
{
	// ����Ҷ�
	if(m_nBitCount==8)
	{
		//�ͷžɵ����ͼ�񻺳���
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}

		//���ͼ��ÿ����λ��������ͼ����ͬ
		m_nBitCountOut=m_nBitCount;
	
		//������ɫ����
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

		//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
		if(m_nColorTableLengthOut!=0){
    		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
			memcpy(m_lpColorTableOut,m_lpColorTable,
				sizeof(RGBQUAD)*m_nColorTableLengthOut);
		}

		//���ͼ��Ŀ��,������ͼ�����
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;

		//���ͼ��ÿ��������ռ���ֽ���
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;
		m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

		//ѭ������
		int i,j;

		//ӳ���
		double map[256];

		//�м����
		int sum,tmp;
	
		//ͳ�ƻҶ�ֱ��ͼ
		computeHistGray();
	
		//����ӳ���
		sum=0;
		for(i=0;i<256;i++){
			sum+=m_histArray[i];
			map[i]=(double)sum*255/(m_imgWidth*m_imgHeight)+0.5;	
		}
	
		//������ݸ�ֵ
		for(i=0;i<m_imgHeight;i++)
		{
			for(j=0;j<m_imgWidth;j++)
			{		
				tmp=*(m_pImgData+i*lineByteOut+j);
				*(m_pImgDataOut+i*lineByteOut+j)=(int)map[tmp];
			}
		}
	}

	// �����ɫ
	if(m_nBitCount==24)
	{
		//�ͷžɵ����ͼ�񻺳���
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}

		//���ͼ��ÿ����λ��������ͼ����ͬ
		m_nBitCountOut=m_nBitCount;
	
		//������ɫ����
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

		//������ɫ������ͼ�����ɫ�������ͼ����ɫ����ͬ
		if(m_nColorTableLengthOut!=0){
    		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
			memcpy(m_lpColorTableOut,m_lpColorTable,
				sizeof(RGBQUAD)*m_nColorTableLengthOut);
		}

		//���ͼ��Ŀ��,������ͼ�����
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;

		//���ͼ��ÿ��������ռ���ֽ���
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

		//�������ͼ��λͼ���ݻ�����
		m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

		//ѭ������
		int i,j;

		//ӳ���
		double map[256];

		//�м����
		int sum,tmp1,tmp2,tmp3;
	
		//ͳ�Ʋ�ɫͼ������ֱ��ͼ
		computeHistBrightness();
	
		//����ӳ���
		sum=0;
		for(i=0;i<256;i++){
			sum+=m_histArrayY[i];
			map[i]=(double)sum*255/(m_imgWidth*m_imgHeight)+0.5;	
		}
	
		//������ݸ�ֵ
		for(i=0;i<m_imgHeight;i++)
		{
			for(j=0;j<m_imgWidth;j++)
			{
				tmp1=*(m_pImgData+i*lineByteOut+j*3+0);
				tmp2=*(m_pImgData+i*lineByteOut+j*3+1);
				tmp3=*(m_pImgData+i*lineByteOut+j*3+2); 

				*(m_pImgDataOut+i*lineByteOut+j*3+0)=(int)map[tmp1];
				*(m_pImgDataOut+i*lineByteOut+j*3+1)=(int)map[tmp2];
				*(m_pImgDataOut+i*lineByteOut+j*3+2)=(int)map[tmp3];

			}
		}
	}

}
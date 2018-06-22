#include "StdAfx.h"
#include "LosslessPredictiveCoding.h"

LosslessPredictiveCoding::LosslessPredictiveCoding()
{
	m_pImgDataOut = NULL;//输出图像位图数据指针为空

	m_lpColorTableOut = NULL;//输出图像颜色表指针为空

	m_nColorTableLengthOut = 0;//输出图像颜色表长度为0

	m_nBitCountOut = 0;//输出图像每像素位数为0

	m_imgWidthOut = 0;//输出图像的宽为0

	m_imgHeightOut = 0;//输出图像的高为0
}

LosslessPredictiveCoding::LosslessPredictiveCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{

	m_pImgDataOut = NULL;//输出图像位图数据指针为空

	m_lpColorTableOut = NULL;//输出图像颜色表指针为空

	m_nColorTableLengthOut = 0;//输出图像颜色表长度为0

	m_nBitCountOut = 0;//输出图像每像素位数为0

	m_imgWidthOut = 0;//输出图像的宽为0

	m_imgHeightOut = 0;//输出图像的高为0
}


LosslessPredictiveCoding::~LosslessPredictiveCoding()
{
	//释放输出图像位图数据缓冲区
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}

	//释放输出图像颜色表
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
}

BOOL LosslessPredictiveCoding::xOneOrderLinearPrediction(double a){
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	//释放旧的输出图像缓冲区
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//输出图像位深为输入图像位深
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	
	//一阶线性预测压缩过程
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//预测误差值和预测值

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
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	//释放旧的输出图像缓冲区
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//输出图像位深为输入图像位深
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	
	//一阶线性预测压缩过程
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//预测误差值和预测值

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
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	//释放旧的输出图像缓冲区
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//输出图像位深为输入图像位深
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];

	//二阶线性预测压缩过程
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//预测误差值和预测值

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
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	//释放旧的输出图像缓冲区
	if (m_pImgDataOut != NULL){
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL){
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}

	//输出图像位深为输入图像位深
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];

	//三阶线性预测压缩过程
	int width = m_imgWidth;
	int height = m_imgHeight;
	int e,f;//预测误差值和预测值

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


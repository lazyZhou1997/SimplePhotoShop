#pragma once
#include "imgdib.h"
class LosslessPredictiveCoding :
	public ImgDib
{
	public:
	//输出图像每像素位数
	int m_nBitCountOut;

	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;

	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;

private:
	//输出图像的宽，像素为单位
	int m_imgWidthOut;

	//输出图像的高，像素为单位
	int m_imgHeightOut;

	//输出图像颜色表长度
	int m_nColorTableLengthOut;
	
public:
	LosslessPredictiveCoding();

	LosslessPredictiveCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//一阶线性预测
	BOOL xOneOrderLinearPrediction(double a);

	//一阶线性预测
	BOOL yOneOrderLinearPrediction(double a);

	//二阶线性预测
	BOOL twoOrderLinearPrediction(double a1,double a2);

	//三阶线性预测
	BOOL threeOrderLinearPrediction(double a1,double a2,double a3);

	~LosslessPredictiveCoding();
};


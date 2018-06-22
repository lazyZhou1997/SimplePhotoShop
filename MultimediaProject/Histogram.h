#pragma once
#include "ImgDib.h"
class Histogram
	:public ImgDib
{
public://直方图数组
	int m_histArray[256];
	int m_histArrayY[256];
	int m_histArrayCb[256];
	int m_histArrayCr[256];

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
	//不带参数的构造函数
	Histogram();

	//带参数的构造函数
	Histogram(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//析构函数
	~Histogram();

	//统计灰度图像的直方图
	void computeHistGray();

	//统计彩色图像亮度直方图
	void computeHistBrightness();

	//直方图均衡
	void histogram();
};


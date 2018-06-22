#include "ImgDib.h"

class BinaryImg :public ImgDib
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

	// Dither矩阵计算中间变量
	int D[100][100];
	int U[100][100];

public:
	// 不带参数的构造函数
	BinaryImg();
	// 不带参数的构造函数
	BinaryImg(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	// 单阈值二值化函数
	BOOL singleThreshold(int th);


	// Dither函数
	BOOL dither(int Dn);

	// Ordered Dither函数
	BOOL orderedDither(int Dn);

	// 重写GetDimension函数
	CSize GetDimensions();

	// 初始化Dither矩阵
	BOOL initDitherMx(int n);

	// 析构函数
	~BinaryImg();

private:
	
};

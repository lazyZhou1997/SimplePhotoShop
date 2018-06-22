#include "imgdib.h"
class GrayTrans: 
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
	// 不带参数的构造函数
	GrayTrans();

	// 带参数的构造函数
	GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	// 析构函数
	~GrayTrans();

	// RGBToHSI()函数
	BOOL RGBToHSI();

	// RGBToYCbCr()函数
	BOOL RGBToYCbCr();
};

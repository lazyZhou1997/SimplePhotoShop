#include "stdafx.h"
#include "HuffmanCoding.h"

/***********************************************************************
* 函数名称：
* HuffmanCoding()
*
*说明：无参数的构造函数，初始化成员变量
***********************************************************************/
HuffmanCoding::HuffmanCoding()
{


}

/***********************************************************************
* 函数名称：
* HuffmanCoding()
*
*函数参数：
*  CSize size -图像大小（宽、高）
*  int nBitCount  -位深
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据指针
*
*返回值：
*   无
*
*说明：本函数为带参数的构造函数，给定位图的大小、每像素位数、颜色表
*      及位图数据，调用ImgCenterDib()对基类成员初始化，并初始化派生类的
*      数据成员
***********************************************************************/
HuffmanCoding::HuffmanCoding(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{
	dProba = new double[256];
}

/***********************************************************************
* 函数名称：
*   ~HuffmanCoding()
*
*说明：析构函数，释放资源
***********************************************************************/

HuffmanCoding::~HuffmanCoding()
{
	if (dProba != NULL){
		delete[] dProba;
		dProba = NULL;
	}
}

/***********************************************************************
* 函数名称：coding()
*
*说明：霍夫曼编码函数
***********************************************************************/
BOOL HuffmanCoding::coding(){
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int i = 0, j = 0;
	// 赋零值
	for ( i = 0; i < 256; i++)
	{
		dProba[i] = 0.0;
	}

	// 计算各个灰度值的计数
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{

			// 计数加1
			dProba[*(m_pImgData + lineByte * i + j)] += 1;
		}
	}

	int pixelSum = m_imgHeight*m_imgWidth;

	// 计算各个灰度值出现的概率
	for (i = 0; i < 256; i++)
	{
		dProba[i] = (float)dProba[i] / pixelSum;
	}
	return TRUE;
}
#include "stdafx.h"
#include "BinaryImg.h"
/***********************************************************************
* 函数名称：
* BinaryImg()
*
*说明：无参数的构造函数，初始化成员变量
***********************************************************************/
BinaryImg::BinaryImg()
{
	m_pImgDataOut = NULL;//输出图像位图数据指针为空

	m_lpColorTableOut = NULL;//输出图像颜色表指针为空

	m_nColorTableLengthOut = 0;//输出图像颜色表长度为0

	m_nBitCountOut = 0;//输出图像每像素位数为0

	m_imgWidthOut = 0;//输出图像的宽为0

	m_imgHeightOut = 0;//输出图像的高为0

}

/***********************************************************************
* 函数名称：
* BinaryImg()
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
BinaryImg::BinaryImg(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
ImgDib(size, nBitCount, lpColorTable, pImgData)
{

	m_pImgDataOut = NULL;//输出图像位图数据指针为空

	m_lpColorTableOut = NULL;//输出图像颜色表指针为空

	m_nColorTableLengthOut = 0;//输出图像颜色表长度为0

	m_nBitCountOut = 0;//输出图像位深为0

	m_imgWidthOut = 0;//输出图像的宽为0

	m_imgHeightOut = 0;//输出图像的高为0
}

/***********************************************************************
* 函数名称：
*   ~BinaryImg()
*
*说明：析构函数，释放资源
***********************************************************************/

BinaryImg::~BinaryImg()
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

/***********************************************************************
* 函数名称：GetDimensions()
*  
* 返回值：
*     CSize类型（输出图像的宽，输出图像的高）
*
* 说明：重写父类的GetDimensions()
***********************************************************************/
CSize BinaryImg::GetDimensions(){
	return CSize(m_imgWidthOut, m_imgHeightOut);
}

/***********************************************************************
* 函数名称：singleThreshold(int th)
*
* 传入参数：
*		int th - 用户给定的单阈值
*
* 返回值：
*     1为成功，0为失败
*
* 说明：用户给定单阈值，对图像进行单阈值二值化处理
***********************************************************************/
BOOL BinaryImg::singleThreshold(int th){
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

	//输出图像位深不变(8bit)
	//m_nBitCountOut = m_nBitCount;
	m_nBitCountOut = 1;


	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
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

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	//int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	//int lineByteOut = (m_imgWidth*m_nBitCountOut + 3) / 4 * 4;
	int lineByteOut = ((m_imgWidthOut + 31) / 32) * 4;

	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//二值化过程
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
* 函数名称：initDitherMx(int n)
*
* 传入参数：
*		int n - 用户给定的Dither矩阵大小
*
* 返回值：
*     1为成功，0为失败
*
* 说明：用户给定Dither矩阵大小，生成Dither矩阵D
***********************************************************************/
BOOL BinaryImg::initDitherMx(int n){
	// 矩阵大小必须是2的倍数
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
* 函数名称：dither(int Dn)
*
* 传入参数：
*		int Dn - 用户给定的Dither矩阵大小
*
* 返回值：
*     1为成功，0为失败
*
* 说明：用户给定Dither矩阵大小，对图像进行Dither变换
***********************************************************************/
BOOL BinaryImg::dither(int Dn){
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	// 只处理大小为2的倍数的Dither矩阵
	if (Dn%2!=0 || Dn<2)
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

	//输出图像位深不变(8bit)
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高扩大Dn倍
	m_imgWidthOut = m_imgWidth*Dn;
	m_imgHeightOut = m_imgHeight*Dn;

	//输出图像每行像素所占的字节数
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int lineByteOut = (m_imgWidthOut*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//Indexes
	int i = 0, j = 0, m = 0, n = 0, x = 0, y = 0, a = 0, b = 0;

	// 均分颜色
	double T = 256.0 / (Dn*Dn + 1);
	// 重映射
	for (i = 0; i < m_imgHeight; ++i){
		for (j = 0; j < m_imgWidth; ++j){
			*(m_pImgData + i*lineByte + j) = (int)(*(m_pImgData + i*lineByte + j) / T);
		}
	}

	// U、D矩阵初始化
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

	// 获得Dither矩阵
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
	// 只处理灰度
	if (m_nBitCount != 8)
		return FALSE;

	// 只处理大小为2的倍数的Dither矩阵
	if (Dn % 2 != 0 || Dn<2)
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

	//输出图像位深不变(8bit)
	m_nBitCountOut = m_nBitCount;

	//计算颜色表长度
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);

	//若有颜色表，输入图像的颜色表与输出图像颜色表相同
	if (m_nColorTableLengthOut != 0){
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高不变
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;

	//输出图像每行像素所占的字节数
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	int lineByteOut = (m_imgWidthOut*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	//Indexes
	int i = 0, j = 0, m = 0, n = 0, x = 0, y = 0, a = 0, b = 0;

	// 均分颜色
	double T = 256.0 / (Dn*Dn + 1);
	// 重映射
	for (i = 0; i < m_imgHeight; ++i){
		for (j = 0; j < m_imgWidth; ++j){
			*(m_pImgData + i*lineByte + j) = (int)(*(m_pImgData + i*lineByte + j) / T);
		}
	}

	// U、D矩阵初始化
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

	// 获得Dither矩阵
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
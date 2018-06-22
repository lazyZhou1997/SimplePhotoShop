#include "stdafx.h"
#include "GrayTrans.h"
#include "math.h"

/***********************************************************************
* 函数名称：
* GrayTrans()
*
*说明：无参数的构造函数，初始化成员变量
***********************************************************************/
GrayTrans::GrayTrans()
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
* GrayTrans()
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
GrayTrans::GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
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
*   ~GrayTrans()
*
*说明：析构函数，释放资源
***********************************************************************/

GrayTrans::~GrayTrans()
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
* 函数名称：
*   RGBToHSI()
*
*说明：将RGB图像转为HSI模式图像
***********************************************************************/
BOOL GrayTrans::RGBToHSI(){
	//若灰度图像,则返回
	if(m_nBitCount==8) return TRUE;

	//释放旧的输出图像数据及颜色表缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//灰值化后,每像素位数为8比特
	m_nBitCountOut=8;

	//颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//申请颜色表缓冲区,生成灰度图像的颜色表
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//输入图像每像素字节数,彩色图像为3字节/像素
	int pixelByteIn=3;
	
	//输入图像每行像素所占字节数,必须是4的倍数
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//输出图像每行像素所占字节数,必须是4的倍数
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//申请输出图像位图数据缓冲区
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//循环变量,图像的坐标
	int i,j;

	//根据灰值化公式为输出图像赋值
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++)
			*(m_pImgDataOut+i*lineByteOut+j)=0.33**(m_pImgData+i*lineByteIn+j*pixelByteIn+0)
		        	+0.33**(m_pImgData+i*lineByteIn+j*pixelByteIn+1)
		        	+0.33**(m_pImgData+i*lineByteIn+j*pixelByteIn+2)+0.5;
	}

}

/***********************************************************************
* 函数名称：
*   RGBToYCbCr()
*
*说明：将RGB图像转为YCbCr模式图像
***********************************************************************/
BOOL GrayTrans::RGBToYCbCr(){
	//若灰度图像,则返回
	if(m_nBitCount==8) return TRUE;

	//释放旧的输出图像数据及颜色表缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//灰值化后,每像素位数为8比特
	m_nBitCountOut=8;

	//颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//申请颜色表缓冲区,生成灰度图像的颜色表
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//输入图像每像素字节数,彩色图像为3字节/像素
	int pixelByteIn=3;
	
	//输入图像每行像素所占字节数,必须是4的倍数
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//输出图像每行像素所占字节数,必须是4的倍数
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//申请输出图像位图数据缓冲区
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//循环变量,图像的坐标
	int i,j;

	//根据灰值化公式为输出图像赋值
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++)
			*(m_pImgDataOut+i*lineByteOut+j)=0.11**(m_pImgData+i*lineByteIn+j*pixelByteIn+0)
		        	+0.59**(m_pImgData+i*lineByteIn+j*pixelByteIn+1)
		        	+0.30**(m_pImgData+i*lineByteIn+j*pixelByteIn+2)+0.5;
	}

}

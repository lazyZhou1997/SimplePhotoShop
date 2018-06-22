#include "StdAfx.h"
#include "histogram.h"
#include "GrayTrans.h"
#include "math.h"

/***********************************************************************
* 函数名称：
* Histogram()
*
*说明：无参数的构造函数，初始化成员变量
***********************************************************************/
Histogram::Histogram()
{
	//直方图数组清0
	for(int i=0;i<256;i++)
	{
    	m_histArray[i]=0;
		m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

    m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}

/***********************************************************************
* 函数名称：
* Histogram()
*
*函数参数：
*  CSize size -图像大小（宽、高）
*  int nBitCount  -每像素所占位数
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
Histogram::Histogram(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImgDib(size, nBitCount, lpColorTable, pImgData)
{
	//直方图数组清0
	for(int i=0;i<256;i++)
	{
    	m_histArray[i]=0;
		m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

    m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}

/***********************************************************************
* 函数名称：
*   ~Histogram()

*
*说明：析构函数，释放资源
***********************************************************************/
Histogram::~Histogram()
{
	//释放输出图像位图数据缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//释放输出图像颜色表
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}

/***********************************************************************
* 函数名称：
* computeHistGray()
*
*说明：灰度图像统计直方图，m_histArray中存放了当前图像的统计数据
***********************************************************************/
void Histogram::computeHistGray()
{
	//只处理灰度图像
	if(m_nBitCount!=8)
		return;

	//循环变量
	int i,j;

	//直方图数组清0
	for(i=0;i<256;i++)
    	m_histArray[i]=0;

	//每行像素所占字节数
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//中间变量
	int temp;

	//统计灰度直方图
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			temp=*(m_pImgData+i*lineByte+j);
		    m_histArray[temp]++;
		}
	}
}

/***********************************************************************
* 函数名称：
* computeHistBrightness()
*
*说明：彩色图像亮度直方图，m_histArray中存放了当前图像的亮度统计数据
***********************************************************************/
void Histogram::computeHistBrightness()
{
	//彩色图像有效
	if(m_nBitCount!=24)
		return;

	//循环变量
	int i,j;

	//直方图数组清0
	for(i=0;i<256;i++)
	{
    	m_histArrayY[i]=0;
		m_histArrayCb[i]=0;
		m_histArrayCr[i]=0;
	}

	//每行像素所占字节数
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//中间变量
	int tempY;
	int tempCb;
	int tempCr;

	//统计亮度直方图
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
* 函数名称：
* histogram()
*
*说明：直方图均衡
***********************************************************************/
void Histogram::histogram()
{
	// 处理灰度
	if(m_nBitCount==8)
	{
		//释放旧的输出图像缓冲区
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}

		//输出图像每像素位数与输入图像相同
		m_nBitCountOut=m_nBitCount;
	
		//计算颜色表长度
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

		//若有颜色表，输入图像的颜色表与输出图像颜色表相同
		if(m_nColorTableLengthOut!=0){
    		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
			memcpy(m_lpColorTableOut,m_lpColorTable,
				sizeof(RGBQUAD)*m_nColorTableLengthOut);
		}

		//输出图像的宽高,与输入图像相等
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;

		//输出图像每行像素所占的字节数
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;
		m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

		//循环变量
		int i,j;

		//映射表
		double map[256];

		//中间变量
		int sum,tmp;
	
		//统计灰度直方图
		computeHistGray();
	
		//计算映射表
		sum=0;
		for(i=0;i<256;i++){
			sum+=m_histArray[i];
			map[i]=(double)sum*255/(m_imgWidth*m_imgHeight)+0.5;	
		}
	
		//输出数据赋值
		for(i=0;i<m_imgHeight;i++)
		{
			for(j=0;j<m_imgWidth;j++)
			{		
				tmp=*(m_pImgData+i*lineByteOut+j);
				*(m_pImgDataOut+i*lineByteOut+j)=(int)map[tmp];
			}
		}
	}

	// 处理彩色
	if(m_nBitCount==24)
	{
		//释放旧的输出图像缓冲区
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}

		//输出图像每像素位数与输入图像相同
		m_nBitCountOut=m_nBitCount;
	
		//计算颜色表长度
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

		//若有颜色表，输入图像的颜色表与输出图像颜色表相同
		if(m_nColorTableLengthOut!=0){
    		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
			memcpy(m_lpColorTableOut,m_lpColorTable,
				sizeof(RGBQUAD)*m_nColorTableLengthOut);
		}

		//输出图像的宽高,与输入图像相等
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;

		//输出图像每行像素所占的字节数
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

		//申请输出图像位图数据缓冲区
		m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

		//循环变量
		int i,j;

		//映射表
		double map[256];

		//中间变量
		int sum,tmp1,tmp2,tmp3;
	
		//统计彩色图像亮度直方图
		computeHistBrightness();
	
		//计算映射表
		sum=0;
		for(i=0;i<256;i++){
			sum+=m_histArrayY[i];
			map[i]=(double)sum*255/(m_imgWidth*m_imgHeight)+0.5;	
		}
	
		//输出数据赋值
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
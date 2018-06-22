
#ifndef _INSIDE_VISUAL_CPP_ImgDib
#define _INSIDE_VISUAL_CPP_ImgDib

//ImgDib类
class ImgDib
{
public:
	// 图像数据指针
	unsigned char * m_pImgData;

	// 图像颜色表指针
	LPRGBQUAD m_lpColorTable;

	//位深
	int m_nBitCount;


private:
	//指向DIB的指针: 包含BITMAPFILEHEADER，BITMAPINFOHEADER和颜色表
	LPBYTE m_lpDib;

	//逻辑调色板句柄
	HPALETTE m_hPalette;

	//颜色表长度（多少个表项）
	int m_nColorTableLength;

protected:
	//图像的宽，像素为单位
	int m_imgWidth;

	//图像的高，像素为单位
	int m_imgHeight;

	//图像信息头指针
	LPBITMAPINFOHEADER m_lpBmpInfoHead;

public:
	//不带参数的构造函数
	ImgDib();

	//带参数的构造函数
	ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);

	//析构函数
	~ImgDib();

	//获取DIB的尺寸（宽高）
	CSize GetDimensions();

	//DIB读函数
	BOOL Read(LPCTSTR lpszPathName);

	//DIB写函数
	BOOL Write(LPCTSTR lpszPathName);

	//显示DIB
	BOOL Draw(CDC* pDC, CPoint origin, CSize size);

	// 进行均匀量化
	BOOL UniformQuanlization(int cR);

	//进行改进版的均匀量化IGS
	BOOL IGSUniformQuanlization();

	// 进行DCT变换
	BOOL DCTTransfrom(int N, int M);

	// 进行DCT变换之后再DCT反变换,abandon决定要丢弃多少数据
	BOOL InverseDCTTransfrom(int N, int M, int abandon);

	//用新的数据替换DIB
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);

	//计算颜色表的长度
	int ComputeColorTabalLength(int nBitCount);

private:
	//创建逻辑调色板
	void MakePalette();

	//清理空间
	void Empty();
};
#endif // _INSIDE_VISUAL_CPP_ImgDib

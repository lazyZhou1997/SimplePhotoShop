
#include "stdafx.h"
#include "ImgDib.h"
#include "DCTTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************
* 函数名称：ImgDib()
* 说明：无参数的构造函数，对成员变量进行初始化
***********************************************************************/
ImgDib::ImgDib()
{
	m_lpDib = NULL;//初始化m_lpDib为空。

	m_lpColorTable = NULL;//颜色表指针为空

	m_pImgData = NULL;  // 位图数据指针为空

	m_lpBmpInfoHead = NULL; //  图像信息头指针为空

	m_hPalette = NULL;//调色板为空
}

/***********************************************************************
* 函数名称: ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
*	                              unsigned char *pImgData)
*
*函数参数：
*  CSize size -图像大小（包括宽、高）
*  int nBitCount  -位深
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据指针
*
*说明：本函数为带参数的构造函数，给定位图的大小、每像素位数、颜色表
*            及位图数据生成一个ImgDib类对象
***********************************************************************/
ImgDib::ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	//如果没有位图数据传入，不分配DIB内存
	if (pImgData == NULL){
		m_lpDib = NULL;
		m_lpColorTable = NULL;  // 颜色表
		m_pImgData = NULL;  // 图像数据
		m_lpBmpInfoHead = NULL; //  图像信息头
		m_hPalette = NULL;   // 调色板
	}
	else{//如果有位图数据传入

		m_imgWidth = size.cx;    // 图像的宽赋值
		m_imgHeight = size.cy;   // 图像的高赋值
		m_nBitCount = nBitCount; // 位深赋值

		// 计算颜色表长度
		m_nColorTableLength = ComputeColorTabalLength(nBitCount);

		// 将每行像素所占字节数扩展成4的倍数
		int lineByte = (m_imgWidth*nBitCount / 8 + 3) / 4 * 4;

		// 设置位图数据缓冲区
		int imgBufSize = m_imgHeight * lineByte;

		//为m_lpDib分配内存，生成DIB结构
		m_lpDib = new BYTE[sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength + imgBufSize];

		//填写BITMAPINFOHEADER结构
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;
		m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
		m_lpBmpInfoHead->biWidth = m_imgWidth;
		m_lpBmpInfoHead->biHeight = m_imgHeight;
		m_lpBmpInfoHead->biPlanes = 1;
		m_lpBmpInfoHead->biBitCount = m_nBitCount;
		m_lpBmpInfoHead->biCompression = BI_RGB;
		m_lpBmpInfoHead->biSizeImage = 0;
		m_lpBmpInfoHead->biXPelsPerMeter = 0;
		m_lpBmpInfoHead->biYPelsPerMeter = 0;
		m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
		m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;

		//调色板句柄初始化为空，有颜色表时，MakePalette()函数要生成新的调色板
		m_hPalette = NULL;
		//如果有颜色表，则将颜色表拷贝进DIB的颜色表位置
		if (m_nColorTableLength != 0){

			//m_lpColorTable指向DIB颜色表的起始位置：在位图头之后
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));

			//颜色表拷贝
			memcpy(m_lpColorTable, lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

			//创建逻辑调色板
			MakePalette();
		}

		//m_pImgData指向DIB位图数据起始位置：在位图头、调色板之后
		m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;

		//拷贝图像数据进DIB位图数据区
		memcpy(m_pImgData, pImgData, imgBufSize);
	}

}

/***********************************************************************
* 函数名称：  ~ImgDib()
*
*说明：析构函数，释放资源
***********************************************************************/
ImgDib::~ImgDib()
{
	//释放m_lpDib所指向的内存缓冲区
	if (m_lpDib != NULL)
		delete[] m_lpDib;

	//如果有调色板，释放调色板缓冲区
	if (m_hPalette != NULL)
		::DeleteObject(m_hPalette);
}



/***********************************************************************
* 函数名称：Draw()
*
*函数参数：
*  CDC* pDC  -设备环境指针
*  CPoint origin  -显示矩形区域的左上角
*  CSize size     -显示矩形区域的尺寸
*
*返回值：
*   0为失败,1为成功
*
*说明：给定设备环境指针，以及需要显示的矩形区域在设备环境中的位置
*           将m_lpDib所指向的DIB显示出来
***********************************************************************/
BOOL ImgDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	//旧的调色板句柄
	HPALETTE hOldPal = NULL;

	//如果DIB为空，则返回0
	if (m_lpDib == NULL) return FALSE;

	//如果DIB有调色板
	if (m_hPalette != NULL) {
		//将调色板选进设备环境中
		hOldPal = ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

		//实现调色板
		pDC->RealizePalette();
	}

	//设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);

	//将DIB在pDC所指向的设备上进行显示
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy,
		0, 0, m_lpBmpInfoHead->biWidth, m_lpBmpInfoHead->biHeight, m_pImgData,
		(LPBITMAPINFO)m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);

	//恢复旧的调色板
	if (hOldPal != NULL)
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);

	//函数返回
	return TRUE;
}



/***********************************************************************
* 函数名称：Read()
*
*函数参数：
*  LPCTSTR lpszPathName -图像名字及路径
*
*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像文件名及其路径，读取图像数据进内存生成DIB，
*           并存放在m_lpDib所指向的缓冲区
***********************************************************************/
BOOL ImgDib::Read(LPCTSTR lpszPathName)
{
	//读模式打开图像文件
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;

	BITMAPFILEHEADER bmfh;
	try {
		//清理空间
		Empty();

		//读取BITMAPFILEHEADER结构到变量bmfh中
		int nCount = file.Read((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//异常判断
		if (nCount != sizeof(BITMAPFILEHEADER)) {
			throw new CFileException;
		}
		if (bmfh.bfType != 0x4d42) {
			throw new CFileException;
		}

		//为m_lpDib分配空间，读取DIB进内存
		if (m_lpDib != NULL)
			delete[]m_lpDib;
		m_lpDib = new BYTE[file.GetLength() - sizeof(BITMAPFILEHEADER)];
		file.Read(m_lpDib, file.GetLength() - sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHead位置为m_lpDib起始位置
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//为成员变量赋值
		m_imgWidth = m_lpBmpInfoHead->biWidth;
		m_imgHeight = m_lpBmpInfoHead->biHeight;
		m_nBitCount = m_lpBmpInfoHead->biBitCount;

		//计算颜色表长度
		m_nColorTableLength =
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//如果有颜色表,则创建逻辑调色板
		m_hPalette = NULL;
		if (m_nColorTableLength != 0){
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
			MakePalette();
		}

		//m_pImgData指向DIB的位图数据起始位置
		m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;
	}
	catch (CFileException* pe) {
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}

	//函数返回
	return TRUE;
}

/***********************************************************************
* 函数名称：
* Write()
*
*函数参数：
*  LPCTSTR lpszPathName -指定图像名字及路径
*
*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像文件名及其路径，将m_lpDib指向的DIB存盘
***********************************************************************/
BOOL ImgDib::Write(LPCTSTR lpszPathName)
{
	//写模式打开文件
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate | CFile::modeReadWrite
		| CFile::shareExclusive))
		return FALSE;

	//填写文件头结构
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength;
	try {
		//文件头结构写进文件
		file.Write((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//文件信息头结构写进文件
		file.Write(m_lpBmpInfoHead, sizeof(BITMAPINFOHEADER));

		//如果有颜色表的话，颜色表写进文件
		if (m_nColorTableLength != 0)
			file.Write(m_lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

		//位图数据写进文件
		int imgBufSize = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4 * m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch (CFileException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}

	//函数返回
	return TRUE;
}


/***********************************************************************
* 函数名称：
* ReplaceDib()
*
*函数参数：
*  CSize size   -要替换的新图像尺寸
*  int nBitCount  -每像素的位数
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据的指针

*返回值：
*   无
*
*说明：图像的尺寸，每像素位数、颜色表、及位图数据，
*      替换m_lpDib所指向的现有的DIB
***********************************************************************/
void ImgDib::ReplaceDib(CSize size, int nBitCount,
	LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	//释放原DIB所占空间
	Empty();

	//成员变量赋值
	m_imgWidth = size.cx;
	m_imgHeight = size.cy;
	m_nBitCount = nBitCount;

	//计算颜色表的长度
	m_nColorTableLength = ComputeColorTabalLength(nBitCount);

	//每行像素所占字节数，扩展成4的倍数
	int lineByte = (m_imgWidth*nBitCount / 8 + 3) / 4 * 4;

	//位图数据的大小
	int imgBufSize = m_imgHeight*lineByte;

	//为m_lpDib重新分配空间，以存放新的DIB
	m_lpDib = new BYTE[sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength + imgBufSize];

	//填写位图信息头BITMAPINFOHEADER结构
	m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;
	m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBmpInfoHead->biWidth = m_imgWidth;
	m_lpBmpInfoHead->biHeight = m_imgHeight;
	m_lpBmpInfoHead->biPlanes = 1;
	m_lpBmpInfoHead->biBitCount = m_nBitCount;
	m_lpBmpInfoHead->biCompression = BI_RGB;
	m_lpBmpInfoHead->biSizeImage = 0;
	m_lpBmpInfoHead->biXPelsPerMeter = 0;
	m_lpBmpInfoHead->biYPelsPerMeter = 0;
	m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
	m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;

	//调色板置空
	m_hPalette = NULL;

	//如果有颜色表，则将颜色表拷贝至新生成的DIB，并创建逻辑调色板
	if (m_nColorTableLength != 0){
		m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
		memcpy(m_lpColorTable, lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);
		MakePalette();
	}

	//m_pImgData指向DIB的位图数据起始位置
	m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength;

	//将新位图数据拷贝至新的DIB中
	memcpy(m_pImgData, pImgData, imgBufSize);
}


/***********************************************************************
* 函数名称：ComputeColorTabalLength()
*
*函数参数：
*  int nBitCount -DIB每像素位数
*
*返回值：
*   颜色表的长度
*
*说明：给定每像素的比特数，计算出DIB颜色表的长度，颜色表长度
*           为2的nBitCount次幂，但是16/24/32位位图颜色表长度为0
***********************************************************************/
int ImgDib::ComputeColorTabalLength(int nBitCount)
{
	int colorTableLength;
	switch (nBitCount) {
	case 1:
		colorTableLength = 2;
		break;
	case 4:
		colorTableLength = 16;
		break;
	case 8:
		colorTableLength = 256;
		break;
	case 16:
	case 24:
	case 32:
		colorTableLength = 0;
		break;
	default:
		ASSERT(FALSE);
	}

	ASSERT((colorTableLength >= 0) && (colorTableLength <= 256));
	return colorTableLength;
}

/***********************************************************************
* 函数名称：MakePalette()
*
*说明：根据DIB的颜色表，生成一个逻辑调色板（m_hPalette），
*            该调色板在显示位图时将被选进设备环境中,24位彩色无调色板
***********************************************************************/
void ImgDib::MakePalette()
{
	//如果颜色表长度为0，则不创建逻辑调色板
	if (m_nColorTableLength == 0)
		return;

	//删除旧的逻辑调色板句柄
	if (m_hPalette != NULL) ::DeleteObject(m_hPalette);

	//申请空间，根据颜色表生成LOGPALETTE结构
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +
		m_nColorTableLength * sizeof(PALETTEENTRY)];
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorTableLength;
	LPRGBQUAD m_lpDibQuad = (LPRGBQUAD)m_lpColorTable;
	for (int i = 0; i < m_nColorTableLength; i++) {
		pLogPal->palPalEntry[i].peRed = m_lpDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = m_lpDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = m_lpDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		m_lpDibQuad++;
	}

	//创建逻辑调色板
	m_hPalette = ::CreatePalette(pLogPal);

	//释放空间
	delete pLogPal;

}



/***********************************************************************
* 函数名称：
* Empty()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：清理空间
***********************************************************************/
void ImgDib::Empty()
{
	//释放DIB内存缓冲区
	if (m_lpDib != NULL) {
		delete[] m_lpDib;
		m_lpDib = NULL;
		m_lpColorTable = NULL;
		m_pImgData = NULL;
		m_lpBmpInfoHead = NULL;
	}
	//释放逻辑调色板缓冲区
	if (m_hPalette != NULL){
		::DeleteObject(m_hPalette);
		m_hPalette = NULL;
	}
}



/***********************************************************************
* 函数名称：
* GetDimensions()
*
*函数参数：
*  无
*
*返回值：
*   图像的尺寸，用CSize类型表达
*
*说明：返回图像的宽和高
***********************************************************************/
CSize ImgDib::GetDimensions()
{
	if (m_lpDib == NULL) return CSize(0, 0);
	return CSize(m_imgWidth, m_imgHeight);
}

/***********************************************************************
* 函数名称：
* UniformQuanlization()
*
*函数参数：
*  int cR 进行均匀量化的压缩比
*
*返回值：
*   0为失败,1为成功
*
*说明：进行均匀量化
***********************************************************************/
BOOL ImgDib::UniformQuanlization(int cR)
{
	int reserveBit = 0; //保留的Bit位数
	int shiftBit = 0; //右移的位数
	unsigned char* imageData = this->m_pImgData; //图像数据
	long totalPix = this->m_imgHeight * this->m_imgWidth; //图像的总像素数

	//判断参数是否在范围内
	if (cR < 1 || cR > 4)
	{
		return FALSE;
	}

	// 如果不是8位深的图像，抛出异常
	if (8 != this->m_nBitCount)
	{
		return FALSE;
	}

	//计算保留的Bit位数
	reserveBit = 8 / cR;
	// 计算右移的位数
	shiftBit = 8 - reserveBit;

	//对每个像素点进行均匀量化，并且反量化
	for (long i = 0; i < totalPix; i++)
	{
		imageData[i] = (imageData[i] >> shiftBit) << shiftBit; // 先右移，再左移
	}

	return TRUE;
}

/***********************************************************************
* 函数名称：
* IGSUniformQuanlization()
*
*函数参数：
*  无
*
*返回值：
*   0为失败,1为成功
*
*说明：进行改进版的均匀量化IGS，压缩比默认为2
***********************************************************************/
BOOL ImgDib::IGSUniformQuanlization()
{
	unsigned char sum = 0; //相加之后的值
	unsigned char* imageData = this->m_pImgData; //图像数据
	long totalPix = this->m_imgHeight * this->m_imgWidth; //图像的总像素数

	//只能处理位深为8的图像
	if (this->m_nBitCount != 8)
	{
		return FALSE;
	}

	//对每个像素点进行均匀量化，并且反量化
	for (long i = 0; i < totalPix; i++)
	{
		// 当值为1111????时，sum应该为0
		if ((imageData[i] >> 4) == 15)
		{
			sum = 0;
		}

		// 进行IGS量化
		imageData[i] = imageData[i] + sum;
		sum = imageData[i] & (unsigned char)15;
		imageData[i] = imageData[i] & 240; //&11110000
	}

	return TRUE;
}

/***********************************************************************
* 函数名称：
* DCTTransfrom(int N, int M)
*
*函数参数：
*  int N 进行变换的方块的长度
*  int M 进行变化的方块的宽度
*
*返回值：
*   0为失败,1为成功
*
*说明：对图像按照分块进行DCT变换
***********************************************************************/
BOOL ImgDib::DCTTransfrom(int N, int M)
{
	unsigned char* imageData = this->m_pImgData; //图像数据
	// long totalPix = this->m_imgHeight * this->m_imgWidth; //图像的总像素数

	//输入的DCT矩阵
	double** inputDCT = new double*[N];
	// 输出的DCT矩阵
	double** outputDCT = new double*[N];
	//分配空间
	for (int i = 0; i < N; i++)
	{
		inputDCT[i] = new double[M];
		outputDCT[i] = new double[M];
	}

	int rowBlockNum = this->m_imgWidth / N; //水平方向上的块数
	int colBlockNum = this->m_imgHeight / M; //垂直方向上的块数
	int rowIndex; //对图像数据水平方向上的索引
	int colIndex; //对图像数据垂直方向上的索引

	//对每个区块进行DCT变化
	for (int i = 0; i <= rowBlockNum; i++)
	{
		for (int j = 0; j <= colBlockNum; j++)
		{
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //计算行索引
					colIndex = j * M + l; //计算列索引
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//拷贝过去
						inputDCT[k][l] = imageData[rowIndex * this->m_imgWidth + colIndex];
					}
					else
					{
						inputDCT[k][l] = 0;
					}
				}
			}

			//进行DCT变化
			DCT(inputDCT, outputDCT, N, M);


			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //计算行索引
					colIndex = j * M + l; //计算列索引
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//拷贝回来
						imageData[rowIndex * this->m_imgWidth + colIndex] = (unsigned char)outputDCT[k][l];
					}
				}
			}
		}
	}


	//释放资源
	for (int i = 0; i < N; i++)
	{
		delete[] inputDCT[i];
		delete[] outputDCT[i];
	}
	delete[] inputDCT;
	delete[] outputDCT;

	return true;
}

//Z型扫描状态变量
enum Choice
{
	rightTowards,
	//向移动
	rightUp,
	//向右上移动
	down,
	//向下移动
	leftDown //向左下移动
};


/***********************************************************************
* 函数名称：
* InverseDCTTransfrom(int N, int M, int abandon)
*
*函数参数：
*  int N 进行反变换的方块的长度
*  int M 进行反变换的方块的宽度
*
*返回值：
*   0为失败,1为成功
*
*说明：对图像按照分块进行DCT反变换
***********************************************************************/
BOOL ImgDib::InverseDCTTransfrom(int N, int M, int abandon)
{
	unsigned char* imageData = this->m_pImgData; //图像数据
												 // long totalPix = this->m_imgHeight * this->m_imgWidth; //图像的总像素数

												 //输入的反DCT矩阵
	double** inputDCT = new double*[N];
	// 输出的反DCT矩阵
	double** outputDCT = new double*[N];
	//分配空间
	for (int i = 0; i < N; i++)
	{
		inputDCT[i] = new double[M];
		outputDCT[i] = new double[M];
	}

	int rowBlockNum = this->m_imgWidth / N; //水平方向上的块数
	int colBlockNum = this->m_imgHeight / M; //垂直方向上的块数
	int rowIndex; //对图像数据水平方向上的索引
	int colIndex; //对图像数据垂直方向上的索引

				  //对每个区块进行反DCT变化
	for (int i = 0; i <= rowBlockNum; i++)
	{
		for (int j = 0; j <= colBlockNum; j++)
		{
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //计算行索引
					colIndex = j * M + l; //计算列索引

					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//拷贝过去
						inputDCT[k][l] = imageData[rowIndex * this->m_imgWidth + colIndex];
					}
					else
					{
						inputDCT[k][l] = 0;
					}
				}
			}

			//进行DCT变化
			DCT(inputDCT, outputDCT, N, M);

			///////////////////////////////////////////////////////////////////
			///////////////////////// 丢掉数据   //////////////////////////////
			///////////////////////////////////////////////////////////////////
			//计算要保留多少数据
			int reserveCount = floor(N * M * (1 - abandon / 100.0));

			int row = 0, col = 0;
			Choice choice = rightTowards;
			//row = n-1&&col = n-1的情况在while循环结束后处理，防止出现越界的情况
			while (row != N - 1 || col != M - 1)
			{
				//判断保留的数据是否足够
				if (reserveCount <= 0)
				{
					//保留的数据已经足够了，丢弃
					outputDCT[row][col] = 0;
				}
				else
				{
					reserveCount--;
				}

				switch (choice)
				{
				case rightTowards:
					col++;
					if (row == 0)
						choice = leftDown;
					else
						choice = rightUp;
					break;
				case rightUp:
					row--;
					col++;
					if (row == 0 && col != M - 1)
						choice = rightTowards;
					else if (col == M - 1)
						choice = down;
					else
						choice = rightUp;
					break;
				case down:
					row++;
					if (col == 0)
						choice = rightUp;
					else
						choice = leftDown;
					break;
				case leftDown:
					row++;
					col--;
					if (col == 0 && row != N - 1)
						choice = down;
					else if (row == N - 1)
						choice = rightTowards;
					else
						choice = leftDown;
					break;
				}
			}

			//进行反DCT变化
			IDCT(outputDCT, inputDCT, N, M);

			//读取反DCT变化结果
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //计算行索引
					colIndex = j * M + l; //计算列索引
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//拷贝回来
						imageData[rowIndex * this->m_imgWidth + colIndex] = (unsigned char)inputDCT[k][l];
						// imageData[rowIndex * this->m_imgWidth + colIndex] = 0;
					}
				}
			}
		}
	}


	//释放资源
	for (int i = 0; i < N; i++)
	{
		delete[] inputDCT[i];
		delete[] outputDCT[i];
	}
	delete[] inputDCT;
	delete[] outputDCT;

	return true;
}

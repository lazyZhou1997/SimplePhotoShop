
#include "stdafx.h"
#include "ImgDib.h"
#include "DCTTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************
* �������ƣ�ImgDib()
* ˵�����޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
***********************************************************************/
ImgDib::ImgDib()
{
	m_lpDib = NULL;//��ʼ��m_lpDibΪ�ա�

	m_lpColorTable = NULL;//��ɫ��ָ��Ϊ��

	m_pImgData = NULL;  // λͼ����ָ��Ϊ��

	m_lpBmpInfoHead = NULL; //  ͼ����Ϣͷָ��Ϊ��

	m_hPalette = NULL;//��ɫ��Ϊ��
}

/***********************************************************************
* ��������: ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
*	                              unsigned char *pImgData)
*
*����������
*  CSize size -ͼ���С���������ߣ�
*  int nBitCount  -λ��
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ����ָ��
*
*˵����������Ϊ�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��
*            ��λͼ��������һ��ImgDib�����
***********************************************************************/
ImgDib::ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	//���û��λͼ���ݴ��룬������DIB�ڴ�
	if (pImgData == NULL){
		m_lpDib = NULL;
		m_lpColorTable = NULL;  // ��ɫ��
		m_pImgData = NULL;  // ͼ������
		m_lpBmpInfoHead = NULL; //  ͼ����Ϣͷ
		m_hPalette = NULL;   // ��ɫ��
	}
	else{//�����λͼ���ݴ���

		m_imgWidth = size.cx;    // ͼ��Ŀ�ֵ
		m_imgHeight = size.cy;   // ͼ��ĸ߸�ֵ
		m_nBitCount = nBitCount; // λ�ֵ

		// ������ɫ����
		m_nColorTableLength = ComputeColorTabalLength(nBitCount);

		// ��ÿ��������ռ�ֽ�����չ��4�ı���
		int lineByte = (m_imgWidth*nBitCount / 8 + 3) / 4 * 4;

		// ����λͼ���ݻ�����
		int imgBufSize = m_imgHeight * lineByte;

		//Ϊm_lpDib�����ڴ棬����DIB�ṹ
		m_lpDib = new BYTE[sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength + imgBufSize];

		//��дBITMAPINFOHEADER�ṹ
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

		//��ɫ������ʼ��Ϊ�գ�����ɫ��ʱ��MakePalette()����Ҫ�����µĵ�ɫ��
		m_hPalette = NULL;
		//�������ɫ������ɫ������DIB����ɫ��λ��
		if (m_nColorTableLength != 0){

			//m_lpColorTableָ��DIB��ɫ�����ʼλ�ã���λͼͷ֮��
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));

			//��ɫ����
			memcpy(m_lpColorTable, lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

			//�����߼���ɫ��
			MakePalette();
		}

		//m_pImgDataָ��DIBλͼ������ʼλ�ã���λͼͷ����ɫ��֮��
		m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;

		//����ͼ�����ݽ�DIBλͼ������
		memcpy(m_pImgData, pImgData, imgBufSize);
	}

}

/***********************************************************************
* �������ƣ�  ~ImgDib()
*
*˵���������������ͷ���Դ
***********************************************************************/
ImgDib::~ImgDib()
{
	//�ͷ�m_lpDib��ָ����ڴ滺����
	if (m_lpDib != NULL)
		delete[] m_lpDib;

	//����е�ɫ�壬�ͷŵ�ɫ�建����
	if (m_hPalette != NULL)
		::DeleteObject(m_hPalette);
}



/***********************************************************************
* �������ƣ�Draw()
*
*����������
*  CDC* pDC  -�豸����ָ��
*  CPoint origin  -��ʾ������������Ͻ�
*  CSize size     -��ʾ��������ĳߴ�
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵���������豸����ָ�룬�Լ���Ҫ��ʾ�ľ����������豸�����е�λ��
*           ��m_lpDib��ָ���DIB��ʾ����
***********************************************************************/
BOOL ImgDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	//�ɵĵ�ɫ����
	HPALETTE hOldPal = NULL;

	//���DIBΪ�գ��򷵻�0
	if (m_lpDib == NULL) return FALSE;

	//���DIB�е�ɫ��
	if (m_hPalette != NULL) {
		//����ɫ��ѡ���豸������
		hOldPal = ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

		//ʵ�ֵ�ɫ��
		pDC->RealizePalette();
	}

	//����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);

	//��DIB��pDC��ָ����豸�Ͻ�����ʾ
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy,
		0, 0, m_lpBmpInfoHead->biWidth, m_lpBmpInfoHead->biHeight, m_pImgData,
		(LPBITMAPINFO)m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);

	//�ָ��ɵĵ�ɫ��
	if (hOldPal != NULL)
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);

	//��������
	return TRUE;
}



/***********************************************************************
* �������ƣ�Read()
*
*����������
*  LPCTSTR lpszPathName -ͼ�����ּ�·��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵��������һ��ͼ���ļ�������·������ȡͼ�����ݽ��ڴ�����DIB��
*           �������m_lpDib��ָ��Ļ�����
***********************************************************************/
BOOL ImgDib::Read(LPCTSTR lpszPathName)
{
	//��ģʽ��ͼ���ļ�
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;

	BITMAPFILEHEADER bmfh;
	try {
		//����ռ�
		Empty();

		//��ȡBITMAPFILEHEADER�ṹ������bmfh��
		int nCount = file.Read((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//�쳣�ж�
		if (nCount != sizeof(BITMAPFILEHEADER)) {
			throw new CFileException;
		}
		if (bmfh.bfType != 0x4d42) {
			throw new CFileException;
		}

		//Ϊm_lpDib����ռ䣬��ȡDIB���ڴ�
		if (m_lpDib != NULL)
			delete[]m_lpDib;
		m_lpDib = new BYTE[file.GetLength() - sizeof(BITMAPFILEHEADER)];
		file.Read(m_lpDib, file.GetLength() - sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHeadλ��Ϊm_lpDib��ʼλ��
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//Ϊ��Ա������ֵ
		m_imgWidth = m_lpBmpInfoHead->biWidth;
		m_imgHeight = m_lpBmpInfoHead->biHeight;
		m_nBitCount = m_lpBmpInfoHead->biBitCount;

		//������ɫ����
		m_nColorTableLength =
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//�������ɫ��,�򴴽��߼���ɫ��
		m_hPalette = NULL;
		if (m_nColorTableLength != 0){
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
			MakePalette();
		}

		//m_pImgDataָ��DIB��λͼ������ʼλ��
		m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;
	}
	catch (CFileException* pe) {
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}

	//��������
	return TRUE;
}

/***********************************************************************
* �������ƣ�
* Write()
*
*����������
*  LPCTSTR lpszPathName -ָ��ͼ�����ּ�·��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵��������һ��ͼ���ļ�������·������m_lpDibָ���DIB����
***********************************************************************/
BOOL ImgDib::Write(LPCTSTR lpszPathName)
{
	//дģʽ���ļ�
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate | CFile::modeReadWrite
		| CFile::shareExclusive))
		return FALSE;

	//��д�ļ�ͷ�ṹ
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength;
	try {
		//�ļ�ͷ�ṹд���ļ�
		file.Write((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//�ļ���Ϣͷ�ṹд���ļ�
		file.Write(m_lpBmpInfoHead, sizeof(BITMAPINFOHEADER));

		//�������ɫ��Ļ�����ɫ��д���ļ�
		if (m_nColorTableLength != 0)
			file.Write(m_lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

		//λͼ����д���ļ�
		int imgBufSize = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4 * m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch (CFileException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}

	//��������
	return TRUE;
}


/***********************************************************************
* �������ƣ�
* ReplaceDib()
*
*����������
*  CSize size   -Ҫ�滻����ͼ��ߴ�
*  int nBitCount  -ÿ���ص�λ��
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ���ݵ�ָ��

*����ֵ��
*   ��
*
*˵����ͼ��ĳߴ磬ÿ����λ������ɫ����λͼ���ݣ�
*      �滻m_lpDib��ָ������е�DIB
***********************************************************************/
void ImgDib::ReplaceDib(CSize size, int nBitCount,
	LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	//�ͷ�ԭDIB��ռ�ռ�
	Empty();

	//��Ա������ֵ
	m_imgWidth = size.cx;
	m_imgHeight = size.cy;
	m_nBitCount = nBitCount;

	//������ɫ��ĳ���
	m_nColorTableLength = ComputeColorTabalLength(nBitCount);

	//ÿ��������ռ�ֽ�������չ��4�ı���
	int lineByte = (m_imgWidth*nBitCount / 8 + 3) / 4 * 4;

	//λͼ���ݵĴ�С
	int imgBufSize = m_imgHeight*lineByte;

	//Ϊm_lpDib���·���ռ䣬�Դ���µ�DIB
	m_lpDib = new BYTE[sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength + imgBufSize];

	//��дλͼ��ϢͷBITMAPINFOHEADER�ṹ
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

	//��ɫ���ÿ�
	m_hPalette = NULL;

	//�������ɫ������ɫ�����������ɵ�DIB���������߼���ɫ��
	if (m_nColorTableLength != 0){
		m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
		memcpy(m_lpColorTable, lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);
		MakePalette();
	}

	//m_pImgDataָ��DIB��λͼ������ʼλ��
	m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * m_nColorTableLength;

	//����λͼ���ݿ������µ�DIB��
	memcpy(m_pImgData, pImgData, imgBufSize);
}


/***********************************************************************
* �������ƣ�ComputeColorTabalLength()
*
*����������
*  int nBitCount -DIBÿ����λ��
*
*����ֵ��
*   ��ɫ��ĳ���
*
*˵��������ÿ���صı������������DIB��ɫ��ĳ��ȣ���ɫ����
*           Ϊ2��nBitCount���ݣ�����16/24/32λλͼ��ɫ����Ϊ0
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
* �������ƣ�MakePalette()
*
*˵��������DIB����ɫ������һ���߼���ɫ�壨m_hPalette����
*            �õ�ɫ������ʾλͼʱ����ѡ���豸������,24λ��ɫ�޵�ɫ��
***********************************************************************/
void ImgDib::MakePalette()
{
	//�����ɫ����Ϊ0���򲻴����߼���ɫ��
	if (m_nColorTableLength == 0)
		return;

	//ɾ���ɵ��߼���ɫ����
	if (m_hPalette != NULL) ::DeleteObject(m_hPalette);

	//����ռ䣬������ɫ������LOGPALETTE�ṹ
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

	//�����߼���ɫ��
	m_hPalette = ::CreatePalette(pLogPal);

	//�ͷſռ�
	delete pLogPal;

}



/***********************************************************************
* �������ƣ�
* Empty()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ռ�
***********************************************************************/
void ImgDib::Empty()
{
	//�ͷ�DIB�ڴ滺����
	if (m_lpDib != NULL) {
		delete[] m_lpDib;
		m_lpDib = NULL;
		m_lpColorTable = NULL;
		m_pImgData = NULL;
		m_lpBmpInfoHead = NULL;
	}
	//�ͷ��߼���ɫ�建����
	if (m_hPalette != NULL){
		::DeleteObject(m_hPalette);
		m_hPalette = NULL;
	}
}



/***********************************************************************
* �������ƣ�
* GetDimensions()
*
*����������
*  ��
*
*����ֵ��
*   ͼ��ĳߴ磬��CSize���ͱ��
*
*˵��������ͼ��Ŀ�͸�
***********************************************************************/
CSize ImgDib::GetDimensions()
{
	if (m_lpDib == NULL) return CSize(0, 0);
	return CSize(m_imgWidth, m_imgHeight);
}

/***********************************************************************
* �������ƣ�
* UniformQuanlization()
*
*����������
*  int cR ���о���������ѹ����
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵�������о�������
***********************************************************************/
BOOL ImgDib::UniformQuanlization(int cR)
{
	int reserveBit = 0; //������Bitλ��
	int shiftBit = 0; //���Ƶ�λ��
	unsigned char* imageData = this->m_pImgData; //ͼ������
	long totalPix = this->m_imgHeight * this->m_imgWidth; //ͼ�����������

	//�жϲ����Ƿ��ڷ�Χ��
	if (cR < 1 || cR > 4)
	{
		return FALSE;
	}

	// �������8λ���ͼ���׳��쳣
	if (8 != this->m_nBitCount)
	{
		return FALSE;
	}

	//���㱣����Bitλ��
	reserveBit = 8 / cR;
	// �������Ƶ�λ��
	shiftBit = 8 - reserveBit;

	//��ÿ�����ص���о������������ҷ�����
	for (long i = 0; i < totalPix; i++)
	{
		imageData[i] = (imageData[i] >> shiftBit) << shiftBit; // �����ƣ�������
	}

	return TRUE;
}

/***********************************************************************
* �������ƣ�
* IGSUniformQuanlization()
*
*����������
*  ��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵�������иĽ���ľ�������IGS��ѹ����Ĭ��Ϊ2
***********************************************************************/
BOOL ImgDib::IGSUniformQuanlization()
{
	unsigned char sum = 0; //���֮���ֵ
	unsigned char* imageData = this->m_pImgData; //ͼ������
	long totalPix = this->m_imgHeight * this->m_imgWidth; //ͼ�����������

	//ֻ�ܴ���λ��Ϊ8��ͼ��
	if (this->m_nBitCount != 8)
	{
		return FALSE;
	}

	//��ÿ�����ص���о������������ҷ�����
	for (long i = 0; i < totalPix; i++)
	{
		// ��ֵΪ1111????ʱ��sumӦ��Ϊ0
		if ((imageData[i] >> 4) == 15)
		{
			sum = 0;
		}

		// ����IGS����
		imageData[i] = imageData[i] + sum;
		sum = imageData[i] & (unsigned char)15;
		imageData[i] = imageData[i] & 240; //&11110000
	}

	return TRUE;
}

/***********************************************************************
* �������ƣ�
* DCTTransfrom(int N, int M)
*
*����������
*  int N ���б任�ķ���ĳ���
*  int M ���б仯�ķ���Ŀ��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵������ͼ���շֿ����DCT�任
***********************************************************************/
BOOL ImgDib::DCTTransfrom(int N, int M)
{
	unsigned char* imageData = this->m_pImgData; //ͼ������
	// long totalPix = this->m_imgHeight * this->m_imgWidth; //ͼ�����������

	//�����DCT����
	double** inputDCT = new double*[N];
	// �����DCT����
	double** outputDCT = new double*[N];
	//����ռ�
	for (int i = 0; i < N; i++)
	{
		inputDCT[i] = new double[M];
		outputDCT[i] = new double[M];
	}

	int rowBlockNum = this->m_imgWidth / N; //ˮƽ�����ϵĿ���
	int colBlockNum = this->m_imgHeight / M; //��ֱ�����ϵĿ���
	int rowIndex; //��ͼ������ˮƽ�����ϵ�����
	int colIndex; //��ͼ�����ݴ�ֱ�����ϵ�����

	//��ÿ���������DCT�仯
	for (int i = 0; i <= rowBlockNum; i++)
	{
		for (int j = 0; j <= colBlockNum; j++)
		{
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //����������
					colIndex = j * M + l; //����������
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//������ȥ
						inputDCT[k][l] = imageData[rowIndex * this->m_imgWidth + colIndex];
					}
					else
					{
						inputDCT[k][l] = 0;
					}
				}
			}

			//����DCT�仯
			DCT(inputDCT, outputDCT, N, M);


			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //����������
					colIndex = j * M + l; //����������
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//��������
						imageData[rowIndex * this->m_imgWidth + colIndex] = (unsigned char)outputDCT[k][l];
					}
				}
			}
		}
	}


	//�ͷ���Դ
	for (int i = 0; i < N; i++)
	{
		delete[] inputDCT[i];
		delete[] outputDCT[i];
	}
	delete[] inputDCT;
	delete[] outputDCT;

	return true;
}

//Z��ɨ��״̬����
enum Choice
{
	rightTowards,
	//���ƶ�
	rightUp,
	//�������ƶ�
	down,
	//�����ƶ�
	leftDown //�������ƶ�
};


/***********************************************************************
* �������ƣ�
* InverseDCTTransfrom(int N, int M, int abandon)
*
*����������
*  int N ���з��任�ķ���ĳ���
*  int M ���з��任�ķ���Ŀ��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵������ͼ���շֿ����DCT���任
***********************************************************************/
BOOL ImgDib::InverseDCTTransfrom(int N, int M, int abandon)
{
	unsigned char* imageData = this->m_pImgData; //ͼ������
												 // long totalPix = this->m_imgHeight * this->m_imgWidth; //ͼ�����������

												 //����ķ�DCT����
	double** inputDCT = new double*[N];
	// ����ķ�DCT����
	double** outputDCT = new double*[N];
	//����ռ�
	for (int i = 0; i < N; i++)
	{
		inputDCT[i] = new double[M];
		outputDCT[i] = new double[M];
	}

	int rowBlockNum = this->m_imgWidth / N; //ˮƽ�����ϵĿ���
	int colBlockNum = this->m_imgHeight / M; //��ֱ�����ϵĿ���
	int rowIndex; //��ͼ������ˮƽ�����ϵ�����
	int colIndex; //��ͼ�����ݴ�ֱ�����ϵ�����

				  //��ÿ��������з�DCT�仯
	for (int i = 0; i <= rowBlockNum; i++)
	{
		for (int j = 0; j <= colBlockNum; j++)
		{
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //����������
					colIndex = j * M + l; //����������

					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//������ȥ
						inputDCT[k][l] = imageData[rowIndex * this->m_imgWidth + colIndex];
					}
					else
					{
						inputDCT[k][l] = 0;
					}
				}
			}

			//����DCT�仯
			DCT(inputDCT, outputDCT, N, M);

			///////////////////////////////////////////////////////////////////
			///////////////////////// ��������   //////////////////////////////
			///////////////////////////////////////////////////////////////////
			//����Ҫ������������
			int reserveCount = floor(N * M * (1 - abandon / 100.0));

			int row = 0, col = 0;
			Choice choice = rightTowards;
			//row = n-1&&col = n-1�������whileѭ������������ֹ����Խ������
			while (row != N - 1 || col != M - 1)
			{
				//�жϱ����������Ƿ��㹻
				if (reserveCount <= 0)
				{
					//�����������Ѿ��㹻�ˣ�����
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

			//���з�DCT�仯
			IDCT(outputDCT, inputDCT, N, M);

			//��ȡ��DCT�仯���
			for (int k = 0; k < N; ++k)
			{
				for (int l = 0; l < M; ++l)
				{
					rowIndex = i * N + k; //����������
					colIndex = j * M + l; //����������
					if (rowIndex < this->m_imgWidth && colIndex < this->m_imgHeight)
					{
						//��������
						imageData[rowIndex * this->m_imgWidth + colIndex] = (unsigned char)inputDCT[k][l];
						// imageData[rowIndex * this->m_imgWidth + colIndex] = 0;
					}
				}
			}
		}
	}


	//�ͷ���Դ
	for (int i = 0; i < N; i++)
	{
		delete[] inputDCT[i];
		delete[] outputDCT[i];
	}
	delete[] inputDCT;
	delete[] outputDCT;

	return true;
}
